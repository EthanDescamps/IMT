#include "matrix.h"
#include "quaternion.h"
#include "vector3d.h"
#include "msckf.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    Vector3d a = Vector3d();
    Vector3d w = Vector3d();

    // matrice de rotation identité par défaut (évite l'utilisation de mémoire non initialisée)
    Quaternion q = Quaternion();
    MSCKF msckf;
    Matrix G = msckf.create_G_Matrix(q);
    
    Matrix F = msckf.create_F_Matrix(q,a,w);
    cout << F << endl; 
    



    return 0;
}