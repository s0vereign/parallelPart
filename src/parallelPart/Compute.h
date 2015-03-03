#ifndef COMPUTE_H
#define COMPUTE_H

#include <math.h>
#include <stdio.h>

#include "Params.h"
#include "Prints.h"

double computeGamma(double px, double py, double pz, double m) {
    return sqrt(1 + (px*px + py*py + pz*pz) / (m*m));
}

double computeVi(double pi, double gamma, double m) {
    //v_i = p_i * c / (gamma * m)
    return 300000000 * pi / (gamma * m);
}

void computeFb(
    double vx, double vy, double vz,
    double x, double y, double z,
    double* Fx, double *Fy, double *Fz,
    double t
) {
    //F_i,b = e_ikl * v_k * b_l
    *Fx = vy * Bz(x, y, z, t) - vz * By(x, y, z, t);
    *Fy = vz * Bx(x, y, z, t) - vx * Bz(x, y, z, t);
    *Fz = vx * By(x, y, z, t) - vy * Bx(x, y, z, t);
}


void computeLorentz(
    double q,
    double x, double y, double z,
    double *Fx, double *Fy, double *Fz,
    double t
) {
    *Fx = q * ( Ex(x, y, z, t) + *Fx);
    *Fy = q * ( Ey(x, y, z, t) + *Fy);
    *Fz = q * ( Ez(x, y, z, t) + *Fz);
}

void computeNewImpulse(
    double dt,
    double *px, double *py, double *pz,
    double Fx, double Fy, double Fz
) {
    *px = *px + Fx * dt;
    *py = *py + Fy * dt;
    *pz = *pz + Fz * dt;
}

double computeNewPosition(
    double dt,
    double *x, double *y, double *z,
    double px, double py, double pz,
    double Fx, double Fy, double Fz,
    double gamma, double m
) {    
    *x += 300000000 * px / gamma / m * dt + 1 / 2 * dt*dt * Fx * 300000000 * 300000000 / gamma / m ;
    *y += 300000000 * py / gamma / m * dt + 1 / 2 * dt*dt * Fy * 300000000 * 300000000 / gamma / m ;
    *z += 300000000 * pz / gamma / m * dt + 1 / 2 * dt*dt * Fz * 300000000 * 300000000 / gamma / m ;
}

void compute(
    double t_start, double t_end, double dt,
    double x[], double y[], double z[],
    double px[], double py[], double pz[],
    double m[], double q[],
    int len
) {

    double t;
    int i;
    for( t = t_start; t < t_end - dt; t += dt) {
        
        for(i = 0; i < len; i++) {
            
            double  gamma = computeGamma(px[i], py[i], pz[i], m[i]),
            
                    vx = computeVi(px[i], gamma, m[i]),
                    vy = computeVi(pz[i], gamma, m[i]),
                    vz = computeVi(py[i], gamma, m[i]),
                
                    Fx, Fy, Fz;
                    
            computeFb(vx, vy, vz, x[i], y[i], z[i], &Fx, &Fy, &Fz, t);
            computeLorentz(q[i], x[i], y[i], z[i], &Fx, &Fy, &Fz, t);
            
            computeNewImpulse(dt, &px[i], &py[i], &pz[i], Fx, Fy, Fz);
            computeNewPosition(dt, &x[i], &y[i], &z[i], px[i], py[i], pz[i], Fx, Fy, Fz, gamma, m[i]);
            
        }
        
        print(t, x, y, z, px, py, pz, len);
    }
}
#endif
