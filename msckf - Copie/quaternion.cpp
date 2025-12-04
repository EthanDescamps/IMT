#include "quaternion.h"
#include <cmath>

Quaternion::Quaternion() : w(1.0), x(0.0), y(0.0), z(0.0) {}
Quaternion::Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}

Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(
        w*q.w - x*q.x - y*q.y - z*q.z,
        w*q.x + x*q.w + y*q.z - z*q.y,
        w*q.y - x*q.z + y*q.w + z*q.x,
        w*q.z + x*q.y - y*q.x + z*q.w
    );
}

double Quaternion::norm() const {
    return std::sqrt(w*w + x*x + y*y + z*z);
}

void Quaternion::normalize() {
    double n = norm();
    if (n == 0.0) { w = 1.0; x = y = z = 0.0; return; }
    w /= n; x /= n; y /= n; z /= n;
}

Quaternion Quaternion::normalized() const {
    Quaternion q(*this);
    q.normalize();
    return q;
}

Matrix Quaternion::toRotationMatrix() const {
    Matrix R(3, 3);
    R(1, 1) = 1 - 2 * (y * y + z * z);
    R(1, 2) = 2 * (x * y - z * w);
    R(1, 3) = 2 * (x * z + y * w);
    R(2, 1) = 2 * (x * y + z * w);
    R(2, 2) = 1 - 2 * (x * x + z * z);
    R(2, 3) = 2 * (y * z - x * w);
    R(3, 1) = 2 * (x * z - y * w);
    R(3, 2) = 2 * (y * z + x * w);
    R(3, 3) = 1 - 2 * (x * x + y * y);
    return R;
}
