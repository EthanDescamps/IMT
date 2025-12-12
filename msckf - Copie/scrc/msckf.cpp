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

Matrix MSCKF::create_F_Matrix(const Quaternion& q, const Vector3d& a, const Vector3d& w) {
    // Extraction des composantes des vecteurs
    double a_x, a_y, a_z;
    double w_x, w_y, w_z;
    a_x=a.getX(); a_y=a.getY(); a_z=a.getZ();
    w_x=w.getX(); w_y=w.getY(); w_z=w.getZ();
    // Créations des matrices nécessaires à la construction de F
    Matrix R_I = q.toRotationMatrix();
    Matrix Ax(3,3);
    Ax(1,1) = 0; Ax(1,2) = -a_z; Ax(1,3) = a_y;
    Ax(2,1) = a_z; Ax(2,2) = 0; Ax(2,3) = -a_x;
    Ax(3,1) = -a_y; Ax(3,2) = a_x; Ax(3,3) = 0;
    Matrix wx(3,3);
    wx(1,1) = 0; wx(1,2) = -w_z; wx(1,3) = w_y;
    wx(2,1) = w_z; wx(2,2) = 0; wx(2,3) = -w_x;
    wx(3,1) = -w_y; wx(3,2) = w_x; wx(3,3) = 0;
    Matrix AxR = Ax * R_I;
    // Construction de la matrice F, définie par blocs
    Matrix F(15);
    F.Fill(0.0);
    for (unsigned i =1; i <16; i++){
        if (i>=1 && i<=3){
            for (unsigned j=1; j<=3; j++){
                F(i,j)= -wx(i,j);
            };
            F(i,i+3)= -1;
            }
        else if (i>=7 && i<=9){
            for (unsigned j=1; j<=3; j++){
                F(i,j) = -AxR(i-6,j);
                F(i,j+9) = -R_I(i-6,j);
            }           
        }
        else if (i>=13 && i<=15){
            F(i,i-6)= 1;
        }
    }
    return F;
}