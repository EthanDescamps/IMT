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

        double getX() const;
        double getY() const;
        double getZ() const;
        void setX(double a);
        void setY(double a);
        void setZ(double a);

        //méthodes
        Vector3d minus(const Vector3d & other);
        Vector3d plus(const Vector3d & other);
        Vector3d oppose() const;
        Vector3d cross(const Vector3d & a, const Vector3d & b);
        double norm() const;
};
 
// multiplication scalaire * vecteur et vecteur * scalaire
Vector3d operator*(double s, const Vector3d& v);
Vector3d operator*(const Vector3d& v, double s);