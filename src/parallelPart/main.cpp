#include <stdio.h>

#include "Init.h"
#include "Destruct.h"
#include "Compute.h"
#include "Params.h"
#include "Prints.h"

int main(int argc, char** argv) {

    MPI_Init(&argc, argv);
    
    int id, p;
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

//initialize the particles
    int len = 10;
    long double t_start, t_end, dt;
    particle p = init_1(len, id, p);
    init_params(&t_start, &t_end, &dt);
    //~ truncateFile();

//start the computation with p
    compute(t_start, t_end, dt,
        p.x,p.y,p.z,
        p.px,p.py,p.pz,
        p.m,p.q, len,
        id, p);

    destruct(p);
    
    MPI_Finalize();

    return EXIT_SUCCESS;
}
