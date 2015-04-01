#ifndef INIT_H
#define INIT_H


#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <random>

#include <cmath>

#ifndef SOL
#define SOL 299792458
#endif
#ifndef ELEMENTARY_CHARGE
#define ELEMENTARY_CHARGE (1.602176565e-19)
#endif

typedef struct part{

  long double *x,*y,*z,
         *px,*py,*pz,
         *q,*m;


} particle;

void init(long double* t_start, long double *t_end, long double *dt,
            long double *beamspeed, long double *circumference,
            int *length,
            long double **times, particle *p
) {
    //loop-variable for later use
    int i;

    //initialise length (from array length): number of particles
    *length = 8;
    
    *t_start = 0;//in seconds
    *t_end   = 7.7e-04;//in seconds
    *dt      = 1e-9;//in seconds
    
    *beamspeed = 0.467 * SOL;
    *circumference = 108.5;//m

    //generator: generates random numbers, initialising using a seed (unix time)
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    //get the first standard distribution: mean, standart deviation
    //as the momentum is expected in eV: both quantities also in eV
    /*
     * Gaussian: E_total = E_beam + E_bucket. E_bucket = 0 for the syn-
     * cronous particle. as the energie in the bucket here is distributed,
     * the mean is 0 and the standard deviation is equal to the deviation
     * of the energie, whereas delta E / E = beta**2 * delta p / p with
     * delta p / p = 1e-5. E = 122 MeV/u, 12C3+ are considered
     */
    std::normal_distribution<long double> distribution(0, 0.000003192822960000000e6);
    
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

        //initialise everything else
        p->px[i] = 0;
        p->py[i] = 0; //in eV
        p->pz[i] = 0;// in eV
        p->x[i]  = 0;//in m
        p->y[i]  = 0;//in m
        p->z[i]  = 0;//in m
        p->q[i] = 3;//in number of the elementary charge
        p->m[i] = 11177.928732e6;//in eV
        
        long double dist = distribution(generator);
        p->x[i] = std::sqrt(2 * std::abs( dist ) / ( std::abs( p->q[i] ) * 0.025165280916119262)) * ( dist > 0 ? 1 : -1);
        printf("x = %Le\n", p->x[i]);
        
    }

    int s =(int) ceil(((*t_end) - (*t_start)) * (*beamspeed) / (*circumference) + 3) * (*length);

    (*times) =(long double*) malloc(sizeof(long double) * s);
}


#endif
