#ifndef COMPUTE_H
#define COMPUTE_H

#include <math.h>

#include "Params.h"

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
    double *Fx, double *Fy, double *Fz,
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
    double t, double dt,
    double *px, double *py, double *pz,
    double x, double y, double z,
    double m, double q
) {

    double  Fx, Fy, Fz,
            vx, vy, vz,
            gamma;

    gamma = computeGamma(*px, *py, *pz, m);

    vx = computeVi(*px, gamma, m);
    vy = computeVi(*pz, gamma, m);
    vz = computeVi(*py, gamma, m);

    computeFb(vx, vy, vz, x, y, z, &Fx, &Fy, &Fz, t);

    computeLorentz(q, x, y, z, &Fx, &Fy, &Fz, t);

    *px = *px + Fx * dt;
    *py = *py + Fy * dt;
    *pz = *pz + Fz * dt;
}

double computeNewPosition(
    double t, double dt,
    double x, double y, double z,
    double px, double py, double pz,
    double m
) {
    x += 300000000 * px / m * dt;
    y += 300000000 * py / m * dt;
    z += 300000000 * pz / m * dt;
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

            computeNewImpulse(t, dt, &px[i], &py[i], &pz[i], x[i], y[i], z[i], m[i], q[i]);
            computeNewPosition(t, dt, x[i], y[i], z[i], px[i], py[i], pz[i], m[i]);

        }

    }
}
#endif
