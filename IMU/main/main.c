/*#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"

// --- PINS (Vérifiez votre câblage physique !) ---
#define I2C_MASTER_SDA_IO 42    // Reliez à la broche "D" du Pimoroni
#define I2C_MASTER_SCL_IO 41    // Reliez à la broche "C" du Pimoroni


// --- CONFIGURATION ---
#define I2C_MASTER_NUM 0
#define I2C_MASTER_FREQ_HZ 100000 // On reste lent (100kHz) pour la sécurité
#define ICM20948_ADDR 0x68        // Adresse fixe des modules Pimoroni
#define WHO_AM_I_REG 0x00

static const char *TAG = "PIMORONI_TEST";

void app_main(void)
{
    // 1. Config I2C
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);

    ESP_LOGI(TAG, "Test Pimoroni ICM20948 demarre...");

    while (1) {
        uint8_t data;
        
        // 2. Ecriture de l'adresse du registre qu'on veut lire
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (ICM20948_ADDR << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(cmd, WHO_AM_I_REG, true);
        i2c_master_stop(cmd);
        esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 100 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);

        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Etape 1 (Ecriture) Echouee: %s. Verifiez cablage D/C et Alim +/-", esp_err_to_name(ret));
        } else {
            // 3. Lecture de la valeur
            cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd, (ICM20948_ADDR << 1) | I2C_MASTER_READ, true);
            i2c_master_read_byte(cmd, &data, I2C_MASTER_LAST_NACK);
            i2c_master_stop(cmd);
            ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 100 / portTICK_PERIOD_MS);
            i2c_cmd_link_delete(cmd);

            if (ret == ESP_OK) {
                ESP_LOGI(TAG, "Reponse capteur: 0x%02X (Attendu: 0xEA)", data);
            } else {
                ESP_LOGE(TAG, "Etape 2 (Lecture) Echouee: %s", esp_err_to_name(ret));
            }
        }
        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}*/


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"

// --- CONFIGURATION PINOUT (VOTRE CONFIG ACTUELLE) ---
#define I2C_MASTER_SCL_IO           41    /*!< Pin GPIO pour SCL */
#define I2C_MASTER_SDA_IO           42    /*!< Pin GPIO pour SDA */

// --- CONFIGURATION I2C ---
#define I2C_MASTER_NUM              0
#define I2C_MASTER_FREQ_HZ          400000 
#define I2C_MASTER_TX_BUF_DISABLE   0
#define I2C_MASTER_RX_BUF_DISABLE   0
#define I2C_MASTER_TIMEOUT_MS       1000

// --- CONSTANTES ICM-20948 ---
#define ICM20948_ADDR               0x68  // Adresse du capteur
#define REG_WHO_AM_I                0x00
#define REG_PWR_MGMT_1              0x06  // Registre de gestion d'énergie
#define REG_ACCEL_XOUT_H            0x2D  // Début des données accéléromètre

// Sensibilité par défaut (Gamme ±2g et ±250dps)
#define ACCEL_SENSITIVITY           16384.0f // LSB/g
#define GYRO_SENSITIVITY            131.0f   // LSB/dps

static const char *TAG = "ICM_DATA";

// --- FONCTIONS I2C BAS NIVEAU ---

/**
 * @brief Initialisation du bus I2C
 */
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

/**
 * @brief Écrire un octet dans un registre
 */
static esp_err_t icm20948_write_byte(uint8_t reg_addr, uint8_t data)
{
    uint8_t write_buf[2] = {reg_addr, data};
    return i2c_master_write_to_device(I2C_MASTER_NUM, ICM20948_ADDR, write_buf, sizeof(write_buf), I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
}

/**
 * @brief Lire plusieurs octets à la suite (Burst Read)
 */
static esp_err_t icm20948_read_bytes(uint8_t reg_addr, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(I2C_MASTER_NUM, ICM20948_ADDR, &reg_addr, 1, data, len, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
}

// --- FONCTIONS LOGIQUE CAPTEUR ---

/**
 * @brief Réveille le capteur (sort du mode Sleep par défaut)
 */
static void icm20948_wake_up()
{
    // On écrit 0x01 dans PWR_MGMT_1 pour sortir du sommeil et choisir l'horloge auto
    esp_err_t ret = icm20948_write_byte(REG_PWR_MGMT_1, 0x01);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Capteur réveillé (PWR_MGMT_1 configuré).");
    } else {
        ESP_LOGE(TAG, "Erreur au réveil du capteur !");
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // Petite pause pour la stabilisation
}

void app_main(void)
{
    ESP_LOGI(TAG, "Démarrage...");
    ESP_ERROR_CHECK(i2c_master_init());

    // 1. Vérification WHO_AM_I (Toujours utile)
    uint8_t who_am_i = 0;
    icm20948_read_bytes(REG_WHO_AM_I, &who_am_i, 1);
    if (who_am_i != 0xEA) {
        ESP_LOGE(TAG, "Erreur ID Capteur: 0x%02X (Attendu: 0xEA)", who_am_i);
        // On continue quand même pour l'exemple, mais c'est mauvais signe
    } else {
        ESP_LOGI(TAG, "ICM-20948 détecté !");
    }

    // 2. Réveiller le capteur (CRITIQUE : sinon les données seront figées)
    icm20948_wake_up();

    // Buffer pour stocker les données brutes (Accel X,Y,Z + Gyro X,Y,Z)
    // 6 axes * 2 octets = 12 octets
    uint8_t raw_data[12];
    
    while (1) {
        // 3. Lire 12 octets d'un coup en partant du registre ACCEL_XOUT_H (0x2D)
        // L'ordre des registres est : Accel X H/L, Accel Y H/L, Accel Z H/L, Gyro X H/L...
        esp_err_t ret = icm20948_read_bytes(REG_ACCEL_XOUT_H, raw_data, 12);

        if (ret == ESP_OK) {
            // 4. Conversion des octets bruts en entiers signés 16 bits (Bit shifting)
            int16_t accel_x_raw = (int16_t)((raw_data[0] << 8) | raw_data[1]);
            int16_t accel_y_raw = (int16_t)((raw_data[2] << 8) | raw_data[3]);
            int16_t accel_z_raw = (int16_t)((raw_data[4] << 8) | raw_data[5]);

            int16_t gyro_x_raw = (int16_t)((raw_data[6] << 8) | raw_data[7]);
            int16_t gyro_y_raw = (int16_t)((raw_data[8] << 8) | raw_data[9]);
            int16_t gyro_z_raw = (int16_t)((raw_data[10] << 8) | raw_data[11]);

            // 5. Conversion en unités réelles (g et deg/s)
            float ax = accel_x_raw / ACCEL_SENSITIVITY;
            float ay = accel_y_raw / ACCEL_SENSITIVITY;
            float az = accel_z_raw / ACCEL_SENSITIVITY;

            float gx = gyro_x_raw / GYRO_SENSITIVITY;
            float gy = gyro_y_raw / GYRO_SENSITIVITY;
            float gz = gyro_z_raw / GYRO_SENSITIVITY;

            // Affichage propre
            printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", ax, ay, az, gx, gy, gz);
            fflush(stdout);
        } else {
            ESP_LOGE(TAG, "Erreur lecture I2C");
        }

        vTaskDelay(200 / portTICK_PERIOD_MS); // Mise à jour toutes les 200ms
    }
}