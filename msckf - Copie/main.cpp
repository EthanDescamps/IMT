#include "matrix.h"
#include "quaternion.h"
#include "vector3d.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv){
    Matrix G(15,12);
    for(int ligne = 1;ligne<16;ligne++){
        for(int colonne = 1;colonne<13;colonne++){
            G(ligne,colonne) = 0;
        }
    }
    
    cout << G << endl;
    return 0;
}