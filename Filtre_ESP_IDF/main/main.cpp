#include <cstdio>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"

#include "matrix.h"
#include "quaternion.h"
#include "vector3d.h"
#include "msckf.h"
#include "types.h"

static const char *TAG = "IMU_MSCKF";

/* ========= CONFIG I2C ========= */
#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_SCL_IO     41
#define I2C_MASTER_SDA_IO     42
#define I2C_MASTER_FREQ_HZ    400000
#define ICM20948_ADDR         0x68

#define REG_WHO_AM_I          0x00
#define REG_PWR_MGMT_1        0x06
#define REG_ACCEL_XOUT_H      0x2D

#define ACCEL_SENSITIVITY     16384.0f
#define GYRO_SENSITIVITY      131.0f

/* ========= I2C LOW LEVEL ========= */

static esp_err_t i2c_master_init(void)
{
    i2c_config_t conf{};
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;

    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));
    return i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

static esp_err_t icm_write(uint8_t reg, uint8_t data)
{
    uint8_t buf[2] = {reg, data};
    return i2c_master_write_to_device(I2C_MASTER_NUM, ICM20948_ADDR,
                                      buf, 2, pdMS_TO_TICKS(100));
}

static esp_err_t icm_read(uint8_t reg, uint8_t *data, size_t len)
{
    return i2c_master_write_read_device(I2C_MASTER_NUM, ICM20948_ADDR,
                                        &reg, 1, data, len, pdMS_TO_TICKS(100));
}

static void icm_wakeup()
{
    icm_write(REG_PWR_MGMT_1, 0x01);
    vTaskDelay(pdMS_TO_TICKS(100));
}

/* ========= TÂCHE IMU ========= */

static void imu_task(void *arg)
{
    MSCKF *msckf = static_cast<MSCKF*>(arg);

    uint8_t raw[12];
    TickType_t last = xTaskGetTickCount();

    while (true) {
        TickType_t now = xTaskGetTickCount();
        float dt = (now - last) * portTICK_PERIOD_MS / 1000.0f;
        last = now;

        if (icm_read(REG_ACCEL_XOUT_H, raw, 12) == ESP_OK) {

            int16_t ax_r = (raw[0] << 8) | raw[1];
            int16_t ay_r = (raw[2] << 8) | raw[3];
            int16_t az_r = (raw[4] << 8) | raw[5];

            int16_t gx_r = (raw[6] << 8) | raw[7];
            int16_t gy_r = (raw[8] << 8) | raw[9];
            int16_t gz_r = (raw[10] << 8) | raw[11];

            ImuMeasurement u;
            u.dt = dt;

            // Remplissage avec Vector3d
            u.acc.setX(ax_r / ACCEL_SENSITIVITY);
            u.acc.setY(ay_r / ACCEL_SENSITIVITY);
            u.acc.setZ(az_r / ACCEL_SENSITIVITY);
            u.gyro.setX(gx_r / GYRO_SENSITIVITY);
            u.gyro.setY(gy_r / GYRO_SENSITIVITY);
            u.gyro.setZ(gz_r / GYRO_SENSITIVITY);

            /* ===== ICI TU APPELLES TON MSCKF ===== */
            // msckf->predict(u);
            // msckf->update(...);

            printf("ACC: [%.2f, %.2f, %.2f] | GYRO: [%.2f, %.2f, %.2f]\n",
       u.acc.getX(), u.acc.getY(), u.acc.getZ(),
       u.gyro.getX(), u.gyro.getY(), u.gyro.getZ());

        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}


/* ========= APP_MAIN UNIQUE ========= */

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "Init I2C");
    ESP_ERROR_CHECK(i2c_master_init());

    uint8_t who = 0;
    icm_read(REG_WHO_AM_I, &who, 1);
    ESP_LOGI(TAG, "WHO_AM_I = 0x%02X", who);

    icm_wakeup();

    static MSCKF msckf;  // persistant, safe

    xTaskCreatePinnedToCore(
        imu_task,
        "imu_task",
        8192,
        &msckf,
        5,
        nullptr,
        1
    );
}
