#include "msckf.h"


MSCKF::MSCKF() : quaternion(1,0,0,0), bg(0,0,0), vit(0,0,0), ba(0,0,0), pos(0,0,0) {}

Matrix MSCKF::create_G_Matrix(const Quaternion& q) {
    Matrix R_I = q.toRotationMatrix();
    Matrix G(15,12);
    G.Fill(0.0);
    for (unsigned i =1; i <13; i++){
        if (i>=1 && i<=3){
            G(i,i)= -1;
        }
        else if (i>=4 && i<=6){
            G(i,i)= 1;
        }
        else if (i>=7 && i<=9){
            for (unsigned j=7; j<=9; j++){
                G(i,j) = -R_I(i-6,j-6);
            }
        }
        else if (i>=10 && i<=12){
            G(i,i)= 1;
        }
        
    }
    return G;
}

