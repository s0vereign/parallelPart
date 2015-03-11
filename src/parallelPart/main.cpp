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

//Initilize OpenMPI

    MPI_Init(&argc,&argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank (comm,&id);
    MPI_Comm_size(comm,&processors);





//initialize the particles
    int len = 1000;

  //  getConfiguration(argc,argv);
    long double t_start, t_end, dt;
    particle p = init_1(len);
    init_params(&t_start, &t_end, &dt);
    init_file(&t_start,&t_end,&dt,&len);
    //~ truncateFile();

//start the computation with p
    compute(t_start, t_end, dt,
        p.x,p.y,p.z,
        p.px,p.py,p.pz,
        p.m,p.q, len,
        id, processors);

    destruct();


    destruct(p);



    return EXIT_SUCCESS;
}
