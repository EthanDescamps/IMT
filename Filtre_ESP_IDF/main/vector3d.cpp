#include <cmath>
#include "vector3d.h"
//constructeur
Vector3d::Vector3d() : x(0.0),y(0.0),z(0.0){}
Vector3d::Vector3d(double x,double y, double z):x(x),y(y),z(z){}

double Vector3d::getX() const {
    return x;
}

double Vector3d::getY() const {
    return y;
}

double Vector3d::getZ() const {
    return z;
}


Vector3d Vector3d::minus(const Vector3d & other){
    return Vector3d(x-other.x,y-other.y,z - other.z);
}
Vector3d Vector3d::plus(const Vector3d & other){
    return Vector3d(x+other.x,y+other.y,z+other.z);
}
Vector3d Vector3d::oppose() const{
    return Vector3d(-x,-y,-z);
}


// méthode membre renvoyant la norme du vecteur courant
double Vector3d::norm() const {
    return std::sqrt(x*x + y*y + z*z);
}
//produit vectoriel
Vector3d Vector3d::cross(const Vector3d&a,const Vector3d&b){
    return Vector3d(a.y*b.z-a.z*b.y,b.x*a.z-a.x*b.z,a.x*b.y-b.x*a.y);
}

// setters
void Vector3d::setX(double a) { x = a; }
void Vector3d::setY(double a) { y = a; }
void Vector3d::setZ(double a) { z = a; }

// opérateurs : scalaire * vecteur et vecteur * scalaire
Vector3d operator*(double s, const Vector3d& v) {
    return Vector3d(v.getX() * s, v.getY() * s, v.getZ() * s);
}
Vector3d operator*(const Vector3d& v, double s) {
    return s * v;
}