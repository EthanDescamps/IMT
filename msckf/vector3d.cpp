#include <cmath>
#include "vector3d.h"
//constructeur
Vector3d::Vector3d() : x(0.0),y(0.0),z(0.0){}
Vector3d::Vector3d(double x,double y, double z):x(x),y(y),z(z){}
Vector3d Vector3d::minus(const Vector3d & other){
    return Vector3d(x-other.x,y-other.y,z - other.z);
}
Vector3d Vector3d::plus(const Vector3d & other){
    return Vector3d(x+other.x,y+other.y,z+other.z);
}
Vector3d Vector3d::oppose() const{
    return Vector3d(-x,-y,-z);
}
//produit scalaire
double Vector3d::dot(const Vector3d&a,const Vector3d&b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
//produit vectoriel
Vector3d Vector3d::cross(const Vector3d&a,const Vector3d&b){
    return Vector3d(a.y*b.z-a.z*b.y,b.x*a.z-a.x*b.z,a.x*b.y-b.x*a.y);
}