#pragma once

#include "quaternion.h"
#include "vector3d.h"
#include "matrix.h"






class MSCKF {
    public:
        // constructeur par défaut
        MSCKF();
        Matrix create_G_Matrix(const Quaternion& q);
        // destructeur
        ~MSCKF() = default;

    private:
        Quaternion quaternion;
        Vector3d bg;
        Vector3d vit;
        Vector3d ba;
        Vector3d pos;
};
