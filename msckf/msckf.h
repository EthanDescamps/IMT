#include "quaternion.h"




class MSCKF {
    public:
        // constructeur par défaut
        MSCKF();

    private:
        float pos;
        float vit;
        Quaternion quaternion;
        float bg;
        float ba;



};
