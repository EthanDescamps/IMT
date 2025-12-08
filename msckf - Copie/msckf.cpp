#include "msckf.h"


MSCKF::MSCKF()
: quaternion(), bg(), vit(), ba(), pos() {}

Matrix create_G_Matrix(const Quaternion& q) {
    Matrix R_I = q.toRotationMatrix();
    Matrix G(15,12);
    G.fill();
    for (unsigned i =1; i <16; i++){
        if (i>=1 && i<=3){
            G(i,i)= -1;
        }
        else if (i>=4 && i<=6){
            G(i,i)= 1;
        }
        else if (i>=7 && i<=9){
            for (unsigned j=7; j<=9; j++){
                G(i,j) = R_I(i-6,j-6);
            }
        }
        else if (i>=10 && i<=12){
            G(i,i)= 1;
        }
        G(i,i) = 1;
    }
    return G;
}

