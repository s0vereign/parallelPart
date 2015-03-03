#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>

typedef struct part{

  double *x,*y,*z,
         *px,*py,*pz,
         *q,*m;


} particle;


particle init_1(int length){


       particle  p;

        //Initialize the Positions
        p.x = (double*)malloc(sizeof(double)*length);
        p.y = (double*)malloc(sizeof(double)*length);
        p.z = (double*)malloc(sizeof(double)*length);

        //Initialize the Momentum
        p.px = (double*)malloc(sizeof(double)*length);
        p.py = (double*)malloc(sizeof(double)*length);
        p.pz = (double*)malloc(sizeof(double)*length);

        //Initialize the Mass & Charge

        p.q = (double*)malloc(sizeof(double)*length);
        p.m = (double*)malloc(sizeof(double)*length);

        return p;

 }



void init_params(double* t_start, double* t_end, double* dt){

   *t_start = 0;
   *t_end   = 0;
   *dt      = 0;
}
#endif
