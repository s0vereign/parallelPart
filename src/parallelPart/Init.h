#ifndef INIT_H
#define INIT_H


#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include <math.h>

typedef struct part{

  long double *x,*y,*z,
         *px,*py,*pz,
         *q,*m;


} particle;



void init(int *count, int *resolution,
          long double *t_start, long double *t_end,long double *dt,
          long double ***vel_res,particle *p){



            /*
              At first we'll have to initialize:
              - count: The number of particles
              - resolution: So that not every timestep has to be written,
                            resolution will output you the resolution-th
                            timestep. For instance if resolution=100;
                            only every 100-th Timestep will be written in
                            results.txt

              - t_start: starting time (of the Simulation) in seconds!
              - t_end  : end time (of the Simulation) in seconds!
              - dt: timestep width in seconds!

              - vel_res: Saves the velocity of each particle at each
                         choosen timestep (given by resolution).
              - p: This will initialize all relevant particle properties!

            */

            *count  = 100;
            *resolution = 100;

            *t_start = 0;
            *t_end = 1e-8;
            *dt  = 1e-11;





            /*
            This loop will initialize the initial conditions
            of the partciles.

            - m: The mass of the particles in eV/c²
            - q: The charge of the paricles in Number of
                 elementary charges! For instance for an electron
                 this would be -1
            - px: The impuse in x direction, which will be distributed
                  by a Gaussian
            - x,y,z: Coordiantes of the Particles!



            */


            //Initialize the mean value and the width of the Gaussians!

            long double mean1=100;
            long double mean2=100;
            long double width1=100;
            long double width2=100;

            //get the first standard distribution
             unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
             std::default_random_engine generator (seed);
             std::normal_distribution<long double> distribution1(mean1, width2);

             //get the second standard distribution

             std::normal_distribution<long double> distribution2(mean2, width2);


             //Allocate Memory for position!
             p->x = (long double*)malloc(sizeof(long double)* *count);
             p->y = (long double*)malloc(sizeof(long double)* *count);
             p->z = (long double*)malloc(sizeof(long double)* *count);

             //Allocate Memory for the Momentum,Charge,Mass
             p->px = (long double*)malloc(sizeof(long double)* *count);
             p->py = (long double*)malloc(sizeof(long double)* *count);
             p->pz = (long double*)malloc(sizeof(long double)* *count);
             p->q = (long double*)malloc(sizeof(long double)* *count);
             p->m = (long double*)malloc(sizeof(long double)* *count);


            for(int i = 0 ; i < *count ; i++){


              /*
                 Loop to initialize the all the location

              */

              if(i < *count/2){

                p->px[i] = distribution1(generator);

              }
              else{

                p->px[i] = distribution2(generator);

              }

              p->pz[i] = 0;
              p->py[i] = 0;
              p->x[i]  = 0;
              p->y[i]  = 0;
              p->m[i] =  11;
              p->z[i]  = 0;
              p->q[i] =  1;




            }




            //Initialize the Velocity result Memory!
            int s =(int) ((t_end-t_start)/(*dt *(*resolution))),
                 i;

            (*vel_res) =(long double**) malloc(sizeof(long double) * s);

             for( i = 0; i < s; i++) {

                 (*vel_res)[i] = (long double*) malloc(sizeof(long double) *  *count);

             }









}

/*
particle init_1(int  * *count){

      //get the first standard distribution
       unsigned seed = std::chrono::system_clock::now().time_since_epoch(). * *count();
       std::default_random_engine generator (seed);
       std::normal_distribution<long double> distribution1(0, 55);

       //get the second standard distribution

       std::normal_distribution<long double> distribution2(10, 55);

       particle  p;
       int i;



        //Initialize the Positions
        p.x = (long double*)malloc(sizeof(long double)* * *count);
        p.y = (long double*)malloc(sizeof(long double)* * *count);
        p.z = (long double*)malloc(sizeof(long double)* * *count);

        //Initialize the Momentum
        p.px = (long double*)malloc(sizeof(long double)* * *count);
        p.py = (long double*)malloc(sizeof(long double)* * *count);
        p.pz = (long double*)malloc(sizeof(long double)* * *count);





        for(i=0; i <  * *count; i++) {

            if(i < 5){

              p.px[i] = distribution1(generator);
              printf("%Lf \n",p.px[i]);


            }
            else{


              p.px[i] = distribution2(generator);
              printf("%Lf \n",p.px[i]);



            }

            p.py[i] = 0;
            p.pz[i] = 2000;
            p.x[i]  = 0;
            p.y[i]  = 0;
            p.z[i]  = 0;
        }

        //Initialize the Mass & Charge

        p.q = (long double*)malloc(sizeof(long double)* * *count);

        for(i = 0; i <  * *count; i++) {
            p.q[i] = -1;
            p.q[i] = -1;
        }

        p.m = (long double*)malloc(sizeof(long double)* * *count);

        for(i=0; i <  * *count; i++) {
            p.m[i] = 0.51e6;
        }

        /*
        for(i=0; i <  * *count; i++) {

            p.px[i] = sqrt((20e6+p.m[i])*(20e6+p.m[i]) + p.m[i] * p.m[i]);
            p.py[i] = 0;
            p.pz[i] = 0;

            p.x[i] = 0;
            p.y[i] = 0;
            p.z[i] = 0;
        }


        return p;

 }

      */

/*

void init_params(long double* t_start, long double* t_end, long double* dt){

   *t_start = 0;

   *t_end   = 1e-6;
   *dt      = 1e-11;

}


void init_vel_res(int  * *count, long double t_start,
                  long double t_end, long double dt,
                  long double*** vel_res
){

   int s =(int) ((t_end-t_start)/dt),
        i;
   (*vel_res) =(long double**) malloc(sizeof(long double) * s);

    for( i = 0; i < s; i++) {

        (*vel_res)[i] = (long double*) malloc(sizeof(long double) *  * *count);

    }

}




*/



#endif
