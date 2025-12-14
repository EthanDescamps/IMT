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

    MSCKF state_v  = MSCKF();

    cout << state_v.pos.getX() << ", " << state_v.pos.getY() << ", " << state_v.pos.getZ() << endl;

    cout << "--- Fin du calcul ---" << endl;
    
    // Sur un microcontrôleur, le main ne "retourne" pas 0. 
    // On supprime "return 0;"
}