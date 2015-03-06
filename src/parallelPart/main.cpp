#include <stdio.h>
#include <omp.h>

#include "Init.h"
#include "Destruct.h"
#include "Compute.h"
#include "Params.h"
#include "Prints.h"
//#include "Parsearg.h"

int main(int argc, char** argv) {

    printf("Initialising...\n");
    printf("Using %i Threads\n", omp_get_num_procs());
//initialize the particles
    int len = 3,
        printEveryNthTimeStep = 100;
  //  getConfiguration(argc,argv);
    long double t_start, t_end, dt;
    long double **vel_res;
    particle p = init_1(len);
    init_params(&t_start, &t_end, &dt);
    init_vel_res(len,t_start,t_end,dt, printEveryNthTimeStep, &vel_res);
    truncateFile();

    printf("Computing...\n");
//start the computation with p
    compute(t_start, t_end, dt,
        p.x,p.y,p.z,
        p.px,p.py,p.pz,
        p.m,p.q, len,
        printEveryNthTimeStep, &vel_res);


    printf("Printing...\n");
    print_array(t_start, t_end, dt, len, printEveryNthTimeStep, &vel_res);

    destruct(len, t_start, t_end, dt, printEveryNthTimeStep, p, &vel_res);



    return EXIT_SUCCESS;
}
