#include "matrix.h"
#include "quaternion.h"
#include "vector3d.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    int a_x;
    int a_y;
    int a_z;
    int w_x;
    int w_y;
    int w_z;

    matrix<double> R_I(3,3); // à modifier

    Matrix G(15,12);
    for(int ligne = 1;ligne<16;ligne++){
        for(int colonne = 1;colonne<13;colonne++){
            G(ligne,colonne) = 0;
        }
    }
    
    cout << G << endl;

    Matrix Ax(3,3);
    Ax(1,1) = 0; Ax(1,2) = -a_z; Ax(1,3) = a_y;
    Ax(2,1) = a_z; Ax(2,2) = 0; Ax(2,3) = -a_x;
    Ax(3,1) = -a_y; Ax(3,2) = a_x; Ax(3,3) = 0;

    Matrix wx(3,3);
    wx(1,1) = 0; wx(1,2) = -w_z; wx(1,3) = w_y;
    wx(2,1) = w_z; wx(2,2) = 0; wx(2,3) = -w_x;
    wx(3,1) = -w_y; wx(3,2) = w_x; wx(3,3) = 0;

    Matrix zeros(3,3);
    for(int ligne = 1;ligne<4;ligne++){
        for(int colonne = 1;colonne<4;colonne++){
            zeros(ligne,colonne) = 0;
        }
    }

    Matrix eye(3,3);
    for(int ligne = 1;ligne<4;ligne++){
        for(int colonne = 1;colonne<4;colonne++){
            if (ligne == colonne){
                eye(ligne,colonne) = 1;
            } else {
                eye(ligne,colonne) = 0;
            }
        }
    }

    // Construction de la matrice F, défini par blocs
    Matrix F(15,15);
    for(int ligne = 1;ligne<6;ligne++){
        for(int colonne = 1;colonne<6;colonne++){
            if (ligne == 1 && colonne == 1) {
                for(int i=1;i<4;i++){
                    for(int j=1;j<4;j++){
                        F(i,j) = -wx(i,j);
                    }
                }
            } else if (ligne == 1 && colonne == 2) {
                for(int i=1;i<4;i++){
                    for(int j=1;j<4;j++){
                        F(i,j+3) = -eye(i,j);
                    }
                }
            } else if (ligne == 3 && colonne == 1) {
                for(int i=1;i<4;i++){
                    for(int j=1;j<4;j++){
                        F(i+6,j) = (-R_I * Ax)[i,j];
                    }
                }
            } else if (ligne == 3 && colonne == 4) {
                for(int i=1;i<4;i++){
                    for(int j=1;j<4;j++){
                        F(i+6,j+9) = -R_I[i,j];
                    }
                }
            } else if (ligne == 5 && colonne == 4) {
                for(int i=1;i<4;i++){
                    for(int j=1;j<4;j++){
                        F(i+12,j+9) = -eye(i,j);
                    }
                }
            } else {
                for(int i=1;i<4;i++){
                    for(int j=1;j<4;j++){
                        F(i+(ligne-1)*3,j+(colonne-1)*3) = zeros(i,j);
                    }
                }
            }
    }
    cout << F << endl;
    return 0;
}