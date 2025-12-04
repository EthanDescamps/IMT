#pragma once
#include "matrix.h"
#include <array>

class Quaternion {
public:
    double w, x, y, z;

    // Constructeurs
    Quaternion(); // identité (1,0,0,0)
    Quaternion(double w, double x, double y, double z);

    Quaternion operator*(const Quaternion& q) const;
    Matrix toRotationMatrix() const;
    Quaternion normalized() const;
    void normalize();
    double norm() const;
};