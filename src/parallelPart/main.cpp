#include <stdio.h>
#include <omp.h>

#include "Init.h"
#include "Destruct.h"
#include "Compute.h"
#include "Params.h"
#include "Prints.h"

int main(int argc, char** argv) {

    printf("Using %i Threads\n", omp_get_num_procs());
    printf("Initialising...\n");
       
    long double t_start, t_end, dt;
    long double **vel_res;
    int len, printEveryNthTimeStep;
    particle p;
    
    init(&t_start, &t_end, &dt, &len, &printEveryNthTimeStep, &vel_res, &p);
    
    truncateFile();

    printf("Computing...\n");
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
