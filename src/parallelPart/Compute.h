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
    //energy-saving!
  //  long double valueP = sqrt( (*px) * (*px) + (*py) * (*py) + (*pz) * (*pz)),
              /*  ePx = *px / valueP, //unit vector in impulse direction
                ePy = *py / valueP,
                ePz = *pz / valueP,

                fPx = (Fx * ePx + Fy * ePy + Fz * ePz) * ePx, // force parallel to impulse
                fPy = (Fx * ePx + Fy * ePy + Fz * ePz) * ePy,
                fPz = (Fx * ePx + Fy * ePy + Fz * ePz) * ePz,

                fSx = Fx - fPx, //force vertical to impulse
                fSy = Fy - fPy,
                fSz = Fz - fPz,

                px1 = *px + 3e8 * fPx * dt, //impulse part 1: parallel force part
                py1 = *py + 3e8 * fPy * dt,
                pz1 = *pz + 3e8 * fPz * dt,

                px2 = px1 + 3e8 * fSx * dt, //impulse part 2: whole impulse without energy saving
                py2 = py1 + 3e8 * fSy * dt,
                pz2 = pz1 + 3e8 * fSz * dt;*/

    *px = *px + 3e8 * Fx * dt;
    *py = *py + 3e8 * Fy * dt;
    *pz = *pz + 3e8 * Fz * dt;


    /*
    *px = px2 / sqrt(px2*px2 + py2*py2 + pz2*pz2) * sqrt(px1*px1 + py1*py1 + pz1*pz1); //resulting impulse
    *py = py2 / sqrt(px2*px2 + py2*py2 + pz2*pz2) * sqrt(px1*px1 + py1*py1 + pz1*pz1);
    *pz = pz2 / sqrt(px2*px2 + py2*py2 + pz2*pz2) * sqrt(px1*px1 + py1*py1 + pz1*pz1);

    */

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

            //printf("Forces Fx: %Lf, Position x: %Lf \n",Fx,x[i]);

            computeNewPosition(dt, &x[i], &y[i], &z[i], px[i], py[i], pz[i], Fx, Fy, Fz, gamma, m[i]);
            computeNewImpulse(dt, &px[i], &py[i], &pz[i], Fx, Fy, Fz);

        }

        print(t, x, y, z, px, py, pz, len);
    }
}
#endif
