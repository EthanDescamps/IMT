#pragma once
#include "vector3d.h"
const float G_NORM = 9.81;
struct ImuMeasurement {
    float dt;
    Vector3d acc;
    Vector3d gyro;
};