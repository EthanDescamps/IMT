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

std::array<std::array<double,3>,3> Quaternion::toRotationMatrix() const {
    Quaternion q = this->normalized();
    double ww = q.w*q.w, xx = q.x*q.x, yy = q.y*q.y, zz = q.z*q.z;
    double wx = q.w*q.x, wy = q.w*q.y, wz = q.w*q.z;
    double xy = q.x*q.y, xz = q.x*q.z, yz = q.y*q.z;

    return {{
        { 1.0 - 2.0*(yy + zz),     2.0*(xy - wz),         2.0*(xz + wy) },
        {     2.0*(xy + wz),   1.0 - 2.0*(xx + zz),       2.0*(yz - wx) },
        {     2.0*(xz - wy),       2.0*(yz + wx),     1.0 - 2.0*(xx + yy) }
    }};
}