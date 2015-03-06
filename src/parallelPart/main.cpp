#include <stdio.h>
#include <omp.h>

#include "Init.h"
#include "Destruct.h"
#include "Compute.h"
#include "Params.h"
#include "Prints.h"
//#include "Parsearg.h"

int main(int argc, char** argv){




    printf("Initialising...\n");
    printf("Using %i Threads\n", omp_get_num_procs());

//initialize the particles

    int count; //Number of Particles

    int res; //Resolution of Data-Output: Every res-th timestep will be written
    long double t_start, t_end, dt;
    long double **vel_res;//Velocity results
    particle p;



    init(&count,&res,&t_start,&t_end,&dt, &vel_res,&p);


    truncateFile();

    printf("Computing...\n");
//start the computation with p
    compute(t_start, t_end, dt,
        p.x,p.y,p.z,
        p.px,p.py,p.pz,
        p.m,p.q,
        count, &vel_res,res);


    printf("Printing...\n");
    print_array(t_start, t_end, dt, count,res, &vel_res);

    destruct(p);



    return EXIT_SUCCESS;
}
