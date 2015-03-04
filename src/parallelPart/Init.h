#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <chrono>

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef struct part{

  long double *x,*y,*z,
         *px,*py,*pz,
         *q,*m;


} particle;

particle init_1(int length, int id, int processors){

        //generatur set up
       unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
       std::default_random_engine generator (seed);

        //get the first standard distribution
       std::normal_distribution<long double> distribution1(0, 55);

       //get the second standard distribution
       std::normal_distribution<long double> distribution2(10, 55);

       particle  p;
       int i;

       int  len = MAX ( ceil(length / processors) * ((int) processors -1 != id), floor(length / processors) * ((int) processors - 1 == id)),
            lowerBound = ceil(len / processors) * id,
            upperBound = min(ceil(len / processors) * (id + 1), len);

        //Initialize the Positions
        p.x = (long double*)malloc(sizeof(long double)*len );
        p.y = (long double*)malloc(sizeof(long double)*len);
        p.z = (long double*)malloc(sizeof(long double)*len);

        //Initialize the Momentum
        p.px = (long double*)malloc(sizeof(long double)*len);
        p.py = (long double*)malloc(sizeof(long double)*len);
        p.pz = (long double*)malloc(sizeof(long double)*len);

        for(i = lowerBound; i < upperBound; i++) {

            if(i < 5){

              p.px[i] = distribution1(generator);
              printf("%Lf \n",p.px[i]);

            }
            else{

              p.px[i] = distribution2(generator);
              printf("%Lf \n",p.px[i]);

            }

            p.py[i] = 0;
            p.pz[i] = 0.5;
            p.x[i]  = 0;
            p.y[i]  = 0;
            p.z[i]  = 0;
        }

        //Initialize the Mass & Charge

        p.q = (long double*)malloc(sizeof(long double)*len);

        for(i = lowerBound; i < upperBound; i++) {
            p.q[i] = -1;
        }

        p.m = (long double*)malloc(sizeof(long double)*len);

        for(i=lowerBound; i < upperBound; i++) {
            p.m[i] = 0.5e6;
        }

        return p;

 }

void init_params(long double* t_start, long double* t_end, long double* dt){

   *t_start = 0;
   *t_end   = 8e-7;
   *dt      = 1e-11;
}
#endif
