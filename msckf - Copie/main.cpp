// main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "quaternion.h"
#include "vector3d.h"
#include "msckf.h"
#include "types.h"

struct ImuSample {
    double time;
    Quaternion q;   // orientation
    Vector3d   w;   // angular velocity
    Vector3d   a;   // linear acceleration
};

int main() {
    std::ifstream file("imu0.csv");
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir imu0.csv\n";
        return 1;
    }

    std::string line;

    // 1) sauter l'en-tête
    if (!std::getline(file, line)) {
        std::cerr << "Fichier vide\n";
        return 1;
    }

    std::vector<ImuSample> data;
    data.reserve(100000);

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string field;

        ImuSample s;
        double qx=0, qy=0, qz=0, qw=1;
        double wx=0, wy=0, wz=0;
        double ax=0, ay=0, az=0;
        int col = 0;

        // Colonnes selon l'en-tête du CSV
        // 0 : Time
        // 5-8 : orientation.x,y,z,w
        // 18-20 : angular_velocity.x,y,z
        // 31-33 : linear_acceleration.x,y,z

        while (std::getline(ss, field, ',')) {
            if (field.empty()) { ++col; continue; }

            switch (col) {
                case 0:  s.time = std::stod(field); break;
                case 5:  qx     = std::stod(field); break;
                case 6:  qy     = std::stod(field); break;
                case 7:  qz     = std::stod(field); break;
                case 8:  qw     = std::stod(field); break;
                case 18: wx     = std::stod(field); break;
                case 19: wy     = std::stod(field); break;
                case 20: wz     = std::stod(field); break;
                case 31: ax     = std::stod(field); break;
                case 32: ay     = std::stod(field); break;
                case 33: az     = std::stod(field); break;
                default: break;
            }
            ++col;
        }

        s.q = Quaternion(qw, qx, qy, qz);     // adapte à ton constructeur
        s.w = Vector3d(wx, wy, wz);
        s.a = Vector3d(ax, ay, az);

        data.push_back(s);
    }

    file.close();

    std::cout << "Nombre d'échantillons IMU lus : " << data.size() << "\n";

    if (!data.empty()) {
        const auto &s = data.front();
        std::cout << "Premier échantillon : t=" << s.time << "\n";
        std::cout << "  q = (" << s.q.w << ", "
                              << s.q.x << ", "
                              << s.q.y << ", "
                              << s.q.z << ")\n";
        std::cout << "  w = (" << s.w.getX() << ", " << s.w.getY() << ", " << s.w.getZ() << ")\n";
        std::cout << "  a = (" << s.a.getX() << ", " << s.a.getY() << ", " << s.a.getZ() << ")\n";
    }

    // Initialisation du filtre avec le premier échantillon
    MSCKF filter;
    MSCKF state = filter; // état courant
    if (!data.empty()) {
        const auto &s0 = data.front();
        state.setQuaternion(s0.q);
        state.setPos(Vector3d(0,0,0));
        state.setVit(Vector3d(0,0,0));
        state.setBg(Vector3d(0,0,0));
        state.setBa(Vector3d(0,0,0));
    }

    // matrice de covariance initiale
    Matrix P_prev = filter.P0_init();

    // Boucle de propagation sur les mesures IMU
    for (size_t i = 1; i < data.size(); ++i) {
        double dt = data[i].time - data[i-1].time;
        if (dt <= 0) dt = 0.01; // valeur de secours

        ImuMeasurement u;
        u.dt = static_cast<float>(dt);
        u.acc = data[i].a;
        u.gyro = data[i].w;

        // prédiction d'état
        state = filter.PredictState(state, u);

        // prédiction de la covariance
        P_prev = filter.PredictCovariance(P_prev, state, u);

        // affichage périodique
        if (i % 100 == 0) {
            std::cout << "t=" << data[i].time
                      << " q=(" << state.quaternion.getW() << ","
                      << state.quaternion.getX() << ","
                      << state.quaternion.getY() << ","
                      << state.quaternion.getZ() << ")"
                      << " pos=(" << state.pos.getX() << "," << state.pos.getY() << "," << state.pos.getZ() << ")\n";
        }
    }

    std::cout << "Traitement termine. Dernier echantillon traite: " << data.size() << "\n";
    return 0;
}
