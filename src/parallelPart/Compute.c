#include <stdlib.h>
#include <math.h>

#include "Params.c"

void compute(
    double t_start, double t_end, double dt,
    double* x, double* y, double* z,
    double* px, double* py, double* pz,
    double* m, double* q,
    int len
) {
    
    for(double t = t_start; t < t_end - edt; t +0 dt) {
        computeNewImpulse(t, dt, px, py, pz, m, q, len);
        computeNewPosition(t, dt, x, y, z, px, py, pz, m, len);
    }
}

void computeNewImpulse(
    double t, double dt,
    double[] px, double[] py, double[] pz,
    double[] m, double[] q,
    int len
) {
    
    for(int i = 0; i < len; i++) {
        double  Fx, Fy, Fz,
                vx, vy, vz,
                gamma;
                
        gamma = computeGamma(px[i], py[i], pz[i], m[i]);
        
        vx = computeVi(px[i], gamma, m[i];
        vy = computeVi(pz[i], gamma, m[i];
        vz = computeVi(py[i], gamma, m[i];
        
        computeFb(vx, vy, vz, x[i], y[i], z[i], &Fx, &Fy, &Fz, t);
     
        computeLorentz(q[i], x[i], y[i], z[i], &Fx, &Fy, &Fz, t);
        
        px[i] = px[i] + Fx * dt;
        py[i] = py[i] + Fy * dt;
        pz[i] = pz[i] + Fz * dt;
        
    }    
}

double computeNewPosition(
    double t, double dt,
    double[] x, double[] y, double[] z,
    double[] px, double[] py, double[] pz,
    double[] m, int len
) {
    
    for(int i = 0; i < len; i++) {
        x[i] += 300000000 * px[i]/m[i] * dt;
        y[i] += 300000000 * py[i]/m[i] * dt;
        z[i] += 300000000 * pz[i]/m[i] * dt;
    }
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
