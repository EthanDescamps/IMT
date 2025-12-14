#include "matrix.h"
#include "quaternion.h"
#include "vector3d.h"
#include "msckf.h"
#include <iostream>
// Inclure freertos pour éviter que le watchdog ne tue la tâche si le calcul est long (optionnel mais recommandé)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

using namespace std;

extern "C" void app_main(void) {
    // Optionnel : petite pause pour laisser le port série s'initialiser
    vTaskDelay(pdMS_TO_TICKS(1000));

    cout << "--- Demarrage MSCKF ESP32 ---" << endl;

    Vector3d a = Vector3d();
    Vector3d w = Vector3d();

    // matrice de rotation identité par défaut
    Quaternion q = Quaternion();
    Matrix Ri = q.toRotationMatrix();
    cout << "Matrice de Rotation (Ri):" << endl;
    cout << Ri << endl;

    MSCKF msckf;
    Matrix G = msckf.create_G_Matrix(q); //
    
    Matrix F = msckf.create_F_Matrix(q, a, w); //
    cout << "Matrice F:" << endl;
    cout << F << endl; 

    cout << "--- Fin du calcul ---" << endl;
    
    // Sur un microcontrôleur, le main ne "retourne" pas 0. 
    // On supprime "return 0;"
}