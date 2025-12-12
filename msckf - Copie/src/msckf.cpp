#include "msckf.h"
#include "types.h"
#include "vector3d.h"
#include "quaternion.h"
#include <cmath>


MSCKF::MSCKF() : quaternion(1,0,0,0), bg(0,0,0), vit(0,0,0), ba(0,0,0), pos(0,0,0) {}

// setters
void MSCKF::setPos(const Vector3d& p) { pos = p; }
void MSCKF::setVit(const Vector3d& v) { vit = v; }
void MSCKF::setQuaternion(const Quaternion& q) { quaternion = q; }
void MSCKF::setBg(const Vector3d& b_g) { bg = b_g; }
void MSCKF::setBa(const Vector3d& b_a) { ba = b_a; }

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

Matrix MSCKF::P0_init(){
    const float sigma_p_sq = std::pow(1e-4,2);
    const float sigma_v_sq = std::pow(0.01,2);
    const float sigma_theta_sq = std::pow(1e-4,2);
    const float sigma_bg_sq = std::pow(0.001,2);
    const float sigma_ba_sq = std::pow(0.005,2);
    Matrix P0(15,15);
    P0(1,1) = sigma_p_sq;
    P0(2,2) = sigma_p_sq;
    P0(3,3) = sigma_p_sq;
    P0(4,4) = sigma_v_sq;
    P0(5,5) = sigma_v_sq;
    P0(6,6) = sigma_v_sq;
    P0(7,7) = sigma_theta_sq;
    P0(8,8) = sigma_theta_sq;
    P0(9,9) = sigma_theta_sq;
    P0(10,10) = sigma_bg_sq;
    P0(11,11) = sigma_bg_sq;
    P0(12,12) = sigma_bg_sq;
    P0(13,13) = sigma_ba_sq;
    P0(14,14) = sigma_ba_sq;
    P0(15,15) = sigma_ba_sq;
    return P0;
}

MSCKF PredictState(const MSCKF& x_prev, const ImuMeasurement& u_k) {
    MSCKF x_pred ; 
    float dt = u_k.dt;
    Vector3d omega_corr;
    Vector3d acc_corr;

    // --- Correction des mesures brutes ---
    
        omega_corr.setX(u_k.gyro.getX() - x_prev.bg.getX());
        omega_corr.setY(u_k.gyro.getY() - x_prev.bg.getY());
        omega_corr.setZ(u_k.gyro.getZ() - x_prev.bg.getZ());
        
        acc_corr.setX(u_k.acc.getX() - x_prev.ba.getX());
        acc_corr.setY(u_k.acc.getY() - x_prev.ba.getY());
        acc_corr.setZ(u_k.acc.getZ() - x_prev.ba.getZ());


    
    // --- Propagation du quaternion d'orientation ---

    double norm_omega_corr = omega_corr.norm();
    
    
    // Calcul de l'angle de rotation nécessaire au calcul du quaternion
    double rot_angle = norm_omega_corr * dt;
    
    // Approximation quaternion delta_q
    Quaternion delta_q;

    if (rot_angle > 1e-6) {
        double sin_half_angle = std::sin(rot_angle / 2.0);
        
        delta_q.setW(std::cos(rot_angle / 2.0));
        delta_q.setX((omega_corr.getX() / norm_omega_corr ) * sin_half_angle);
        delta_q.setY((omega_corr.getY() / norm_omega_corr ) * sin_half_angle);
        delta_q.setZ((omega_corr.getZ() / norm_omega_corr ) * sin_half_angle);
    } else {
        // Approximation pour les angles très petits
        delta_q.setW(1.0);
        delta_q.setX(omega_corr.getX() * dt / 2.0);
        delta_q.setY(omega_corr.getY() * dt / 2.0);
        delta_q.setZ(omega_corr.getZ() * dt / 2.0);
    }
    delta_q = delta_q.normalized();
    
    // q_pred = q_prev * delta_q
    x_pred.setQuaternion(x_prev.quaternion * delta_q);
    x_pred.quaternion.normalize();
    



    // --- Propagation de la vitesse ---
    
    // Calcul de l'accélération dans le repère global
 // Matrice de rotation globale
    Matrix R_I = x_prev.quaternion.toRotationMatrix();
    Vector3d acc_global = multiplyRbyVector(R_I, acc_corr); // a_global = R * a_corrigee
    
    // Soustraction de la gravité (Repère Global ENU: gravité sur Z négatif)
    acc_global.setY(acc_global.getY()-G_NORM);

    // v_pred = v_prev + a_global * dt
    //x_pred.v[i] = x_prev.v[i] + acc_global[i] * dt;
    Vector3d vit_tmp = x_prev.vit;
    vit_tmp.plus(acc_global * dt);
    x_pred.setVit(vit_tmp);

    

    // --- Propagation de la position ---

    
        // p_pred = p_prev + v_prev * dt + 0.5 * a_global * dt^2
    Vector3d pos_tmp = x_prev.pos;
    pos_tmp.plus(acc_global*(dt*0.5*dt));
    x_pred.setPos(pos_tmp);
    
    // --- Propagation des biais modélisés comme constants ---
    x_pred.ba = x_prev.ba;
    x_pred.bg = x_prev.bg;
    return x_pred;
}