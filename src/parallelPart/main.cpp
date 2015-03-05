#include <stdio.h>
#include <mpi.h>
#include "Init.h"
#include "Destruct.h"
#include "Compute.h"
#include "Params.h"
#include "Prints.h"
//#include "Parsearg.h"

int main(int argc, char** argv) {


    int id, processors;

//initialize the particles
    int len = 3;
  //  getConfiguration(argc,argv);
    long double t_start, t_end, dt;
    long double **vel_res;
    particle p = init_1(len);
    init_params(&t_start, &t_end, &dt);
    init_vel_res(len,t_start,t_end,dt,&vel_res);
    truncateFile();

//start the computation with p
    compute(t_start, t_end, dt,
        p.x,p.y,p.z,
        p.px,p.py,p.pz,
        p.m,p.q, len,
        id, processors);




    destruct(p);



    return EXIT_SUCCESS;
}
