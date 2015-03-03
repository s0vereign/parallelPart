#ifndef COMPUTE_H
#define COMPUTE_H

#include <math.h>
#include <stdio.h>

#include "Params.h"
#include "Prints.h"

long double computeGamma(long double px, long double py, long double pz, long double m) {
    return sqrt(1 + (px*px + py*py + pz*pz) / (m*m));
}

long double computeVi(long double pi, long double gamma, long double m) {
    //v_i = p_i * c / (gamma * m)
    return 3e8 * pi / (gamma * m);
}

void computeFb(
    long double vx, long double vy, long double vz,
    long double x, long double y, long double z,
    long double* Fx, long double *Fy, long double *Fz,
    long double t
) {
    //F_i,b = e_ikl * v_k * b_l
    *Fx = vy * Bz(x, y, z, t) - vz * By(x, y, z, t);
    *Fy = vz * Bx(x, y, z, t) - vx * Bz(x, y, z, t);
    *Fz = vx * By(x, y, z, t) - vy * Bx(x, y, z, t);
    
    //~ printf("Kraft:  %25.20Lf %25.20Lf %25.20Lf\t", -vz * By(x, y, z, t), (long double) 0.0, vx * By(x, y, z, t));
}


void computeLorentz(
    long double q,
    long double x, long double y, long double z,
    long double *Fx, long double *Fy, long double *Fz,
    long double t
) {
    *Fx = q * ( Ex(x, y, z, t) + *Fx);
    *Fy = q * ( Ey(x, y, z, t) + *Fy);
    *Fz = q * ( Ez(x, y, z, t) + *Fz);
}

void computeNewImpulse(
    long double dt,
    long double *px, long double *py, long double *pz,
    long double Fx, long double Fy, long double Fz
) {
    //~ printf("Kraft2: %25.20Lf %25.20Lf %25.20Lf\n", Fx, Fy, Fz);
    *px = *px + 3e8 * Fx * dt;
    *py = *py + 3e8 * Fy * dt;
    *pz = *pz + 3e8 * Fz * dt;
    //~ printf("Impuls: %25.20Lf %25.20Lf %25.20Lf\n", *px, *py, *pz);
}

long double computeNewPosition(
    long double dt,
    long double *x, long double *y, long double *z,
    long double px, long double py, long double pz,
    long double Fx, long double Fy, long double Fz,
    long double gamma, long double m
) {    
    *x += 3e8 * px / gamma / m * dt + 1 / 2 * dt*dt * Fx * 3e8 * 3e8 / gamma / m ;
    *y += 3e8 * py / gamma / m * dt + 1 / 2 * dt*dt * Fy * 3e8 * 3e8 / gamma / m ;
    *z += 3e8 * pz / gamma / m * dt + 1 / 2 * dt*dt * Fz * 3e8 * 3e8 / gamma / m ;
}

void compute(
    long double t_start, long double t_end, long double dt,
    long double x[], long double y[], long double z[],
    long double px[], long double py[], long double pz[],
    long double m[], long double q[],
    int len
) {

    long double t;
    int i;
    for( t = t_start; t < t_end - dt; t += dt) {
        
        for(i = 0; i < len; i++) {
            
            long double  gamma = computeGamma(px[i], py[i], pz[i], m[i]),
            
                    vx = computeVi(px[i], gamma, m[i]),
                    vy = computeVi(py[i], gamma, m[i]),
                    vz = computeVi(pz[i], gamma, m[i]),
                
                    Fx, Fy, Fz;
                    
            computeFb(vx, vy, vz, x[i], y[i], z[i], &Fx, &Fy, &Fz, t);
            computeLorentz(q[i], x[i], y[i], z[i], &Fx, &Fy, &Fz, t);
            
            //~ printf("Kraft:  %f %f %f\n", Fx, Fy, Fz);
            //~ printf("Impuls: %25.20Lf %25.20Lf %25.20Lf\n", vx, vy, vz);
            
            computeNewPosition(dt, &x[i], &y[i], &z[i], px[i], py[i], pz[i], Fx, Fy, Fz, gamma, m[i]);
            computeNewImpulse(dt, &px[i], &py[i], &pz[i], Fx, Fy, Fz);
            
        }
        
        print(t, x, y, z, px, py, pz, len);
    }
}
#endif
