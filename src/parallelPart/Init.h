#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>

#include <math.h>

typedef struct part{

  long double *x,*y,*z,
         *px,*py,*pz,
         *q,*m;


} particle;


particle init_1(int length){


       particle  p;
       int i;

        //Initialize the Positions
        p.x = (long double*)malloc(sizeof(long double)*length);
        p.y = (long double*)malloc(sizeof(long double)*length);
        p.z = (long double*)malloc(sizeof(long double)*length);

        //Initialize the Momentum
        p.px = (long double*)malloc(sizeof(long double)*length);
        p.py = (long double*)malloc(sizeof(long double)*length);
        p.pz = (long double*)malloc(sizeof(long double)*length);

        //Initialize the Mass & Charge

        p.q = (long double*)malloc(sizeof(long double)*length);

        for(i = 0; i < length; i++) {
            p.q[i] = -1;
        }

        p.m = (long double*)malloc(sizeof(long double)*length);

        for(i=0; i < length; i++) {
            p.m[i] = 0.51e6;
        }
        
        
        for(i=0; i < length; i++) {

            p.px[i] = sqrt((20e6+p.m[i])*(20e6+p.m[i]) + p.m[i] * p.m[i]);
            p.py[i] = 0;
            p.pz[i] = 0;
            
            p.x[i] = 0;
            p.y[i] = 0;
            p.z[i] = 0;
        }

        return p;

 }



void init_params(long double* t_start, long double* t_end, long double* dt){

   *t_start = 0;
   *t_end   = 1e-8;
   *dt      = 1e-14;
}
#endif
