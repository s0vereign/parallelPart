#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>

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

        for(i=0; i < length; i++) {
            
            p.px[i] = 1e5;
            
        }

        //Initialize the Mass & Charge

        p.q = (long double*)malloc(sizeof(long double)*length);
        
        for(i = 0; i < length; i++) {
            p.q[i] = -1;
        }
        
        p.m = (long double*)malloc(sizeof(long double)*length);
        
        for(i=0; i < length; i++) {
            p.m[i] = 0.5e6;
        }

        return p;

 }



void init_params(long double* t_start, long double* t_end, long double* dt){

   *t_start = 0;
   *t_end   = 1e-10;
   *dt      = 1e-13;
}
#endif
