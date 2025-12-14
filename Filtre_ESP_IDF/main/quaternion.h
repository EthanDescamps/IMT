#pragma once
#include "matrix.h"
#include <array>

class Quaternion {
public:
    double w, x, y, z;

    // Constructeurs
    Quaternion(); // identité (1,0,0,0)
    Quaternion(double w, double x, double y, double z);

    double getW() const;
    double getX() const;
    double getY() const;
    double getZ() const;

    Quaternion operator*(const Quaternion& q) const;
    Matrix toRotationMatrix() const;
    Quaternion normalized() const;
    void normalize();
    double norm() const;
    void setW(double w);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    Quaternion multiplyQuaternions(const Quaternion& q1, const Quaternion& q2);
};