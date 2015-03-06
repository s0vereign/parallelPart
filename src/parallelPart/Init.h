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

void init(long double* t_start, long double *t_end, long double *dt,
            int *length, int *printEveryNthTimeStep, 
            long double ***vel_res, particle *p
) {
    //loop-variable for later use
    int i;
    
    //initialise length (from array length): number of particles
    *length = 10;
    *printEveryNthTimeStep = 100; //to compute more accurate, but avoid too large files
    
    *t_start = 0;//in seconds
    *t_end   = 1e-8;//in seconds
    *dt      = 1e-12;//in seconds

    //generator: generates random numbers, initialising using a seed (unix time)
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    //get the first standard distribution: mean, standart deviation
    //as the momentum is expected in eV: both quantities also in eV
    std::normal_distribution<long double> distribution1(0, 55);

    //get the second standard distribution
    //see above
    std::normal_distribution<long double> distribution2(10, 55);
    
    //allocate memory for each component of position
    p->x = (long double*) malloc(sizeof(long double) * (*length));
    p->y = (long double*) malloc(sizeof(long double) * (*length));
    p->z = (long double*) malloc(sizeof(long double) * (*length));

    //allocate memory for each component of momentum
    p->px = (long double*) malloc(sizeof(long double) * (*length));
    p->py = (long double*) malloc(sizeof(long double) * (*length));
    p->pz = (long double*) malloc(sizeof(long double) * (*length));
    
    //allocate memory for mass and charge
    p->q = (long double*) malloc(sizeof(long double) * (*length));
    p->m = (long double*) malloc(sizeof(long double) * (*length));
    
    //initialise each parameter for each particle
    for(i=0; i < (*length); i++) {

        //first (here 5) particle's velocity in x-direction is distributed by the first distribution
        //[px] = eV
        if(i < 5){

          p->px[i] = distribution1(generator);

        }
        //every else are distributed by the 2nd distribution
        else{

          p->px[i] = distribution2(generator);

        }

        //initialise everything else
        p->py[i] = 0; //in eV
        p->pz[i] = 2000;// in eV
        p->x[i]  = 0;//in m
        p->y[i]  = 0;//in m
        p->z[i]  = 0;//in m
        p->q[i] = -1;//in number of the elementary charge
        p->m[i] = 0.51e6;//in eV
    }
    
    /*
     * For parallel computation, there is no output during computation.
     * Instead, all results are saved in an array, which is large enough
     * to contain all velocities for all particles for all timestep,
     * which are saved (depend on printEveryNthTimeStep).
     * 
     * The array is 2-dimensional, so each dimension needs to get memory
     * allocated seperately. (*vel_res) is a pointer to an array, where
     * each entry is a pointer to another array, therefore it's two 
     * dimensional.
     * So allocate in a first step memory for the first dimension, and
     * allocate then memory for the other dimension.
     * 
     * Calculate the first dimension: number of timestep, where the
     * velocities are saved
    */
    int s =(int) (((*t_end) - (*t_start)) / (*dt) / (*printEveryNthTimeStep));
   
   //allocate memory for first dimension
    (*vel_res) =(long double**) malloc(sizeof(long double) * s);

    //allocate memory for the other dimesion
    for( i = 0; i < s; i++) {
        
        (*vel_res)[i] = (long double*) malloc(sizeof(long double) * (*length));
        
    }
}


#endif
