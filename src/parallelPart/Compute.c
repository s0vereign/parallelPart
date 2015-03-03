#include <math.h>

#include "Params.c"

void compute(
    double t_start, double t_end, double dt,
    double* x, double* y, double* z,
    double* px, double* py, double* pz,
    double* m, double* q,
    int len
) {

    for(double t = t_start; t < t_end - dt; t += dt) {
        for(int i = 0; i < len; i++) {
            computeNewImpulse(t, dt, px[i], py[i], pz[i], m[i], q[i]);
            computeNewPosition(t, dt, x[i], y[i], z[i], px[i], py[i], pz[i], m[i]);
        }
    }
}

void computeNewImpulse(
    double t, double dt,
    double[] px, double[] py, double[] pz,
    double[] m, double[] q
) {

    double  Fx, Fy, Fz,
            vx, vy, vz,
            gamma;

    gamma = computeGamma(px, py, pz, m);

    vx = computeVi(px, gamma, m;
    vy = computeVi(pz, gamma, m;
    vz = computeVi(py, gamma, m;

    computeFb(vx, vy, vz, x, y, z, &Fx, &Fy, &Fz, t);

    computeLorentz(q, x, y, z, &Fx, &Fy, &Fz, t);

    px = px + Fx * dt;
    py = py + Fy * dt;
    pz = pz + Fz * dt;
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

double computeGamma(double px, double py, double pz, double m) {
    return sqrt(1 + (px*px + py*py + pz*p) / (m*m));
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
    *Fx = vy * Bz(t, x, y, z) - vz * By(t, x, y, z);
    *Fy = vz * Bx(t, x, y, z) - vx * Bz(t, x, y, z);
    *Fz = vx * By(t, x, y, z) - vy * Bx(t, x, y, z);
}


void computeLorentz(
    double q,
    double x, double y, double z,
    double *Fx, double *Fy, double *Fz,
    double t
) {
    *Fx = q * ( Ex(t, x, y, z) + *Fx);
    *Fy = q * ( Ey(t, x, y, z) + *Fy);
    *Fz = q * ( Eu(t, x, y, z) + *Fz);
}
