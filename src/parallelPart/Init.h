#ifndef INIT_H
#define INIT_H


#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <random>

typedef struct part{

  long double *x,*y,*z,
         *px,*py,*pz,
         *q,*m;


} particle;


particle init_1(int length){

      //get the first standard distribution
       unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
       std::default_random_engine generator (seed);
       std::normal_distribution<long double> distribution1(0, 55);

       //get the second standard distribution

       std::normal_distribution<long double> distribution2(10, 55);


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
   *t_end   = 8e-6;
   *dt      = 1e-10;
}
#endif
