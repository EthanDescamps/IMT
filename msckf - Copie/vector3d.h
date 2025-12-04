#pragma once

#include <cmath>

class Vector3d {
    private:
        double x;
        double y;
        double z;
    public :
        //Constructeur
        Vector3d();
        Vector3d(double x,double y,double z);

        //méthodes
        Vector3d minus(const Vector3d & other);
        Vector3d plus(const Vector3d & other);
        Vector3d oppose() const;
        double dot(const Vector3d& a, const Vector3d& b);
        Vector3d cross(const Vector3d & a, const Vector3d & b);
};