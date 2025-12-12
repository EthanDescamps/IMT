#pragma once

#include "quaternion.h"
#include "vector3d.h"
#include "matrix.h"






class MSCKF {
    public:
        // constructeur par défaut
        MSCKF();
        Matrix create_G_Matrix(const Quaternion& q);
        Matrix create_F_Matrix(const Quaternion& q, const Vector3d& a, const Vector3d& w);
        Matrix P0_init();
        // destructeur
        ~MSCKF() = default;

    // attributs
    Vector3d pos;
    Vector3d vit;
    Quaternion quaternion;
    Vector3d bg;
    Vector3d ba;

    // setters
    void setPos(const Vector3d& p);
    void setVit(const Vector3d& v);
    void setQuaternion(const Quaternion& q);
    void setBg(const Vector3d& b_g);
    void setBa(const Vector3d& b_a);
};
