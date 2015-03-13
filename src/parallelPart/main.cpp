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
    long double beamspeed, circumference;
    long double **times;
    int len, printEveryNthTimeStep;
    particle p;
<<<<<<< HEAD

    init(&t_start, &t_end, &dt, &len, &printEveryNthTimeStep, &vel_res, &p);

=======
    
    init(&t_start, &t_end, &dt, 
        &beamspeed, &circumference,
        &len, &printEveryNthTimeStep,
        &times,
        &p
    );
    
>>>>>>> 16b3736c1397217a08e73ece5dec8f37665adee5
    truncateFile();

    printf("Computing...\n");
    compute(t_start, t_end, dt,
        p.x,p.y,p.z,
        p.px,p.py,p.pz,
        p.m,p.q, len,
        printEveryNthTimeStep, &times,
        beamspeed, circumference
    );


    printf("Printing...\n");

    destruct(len, t_start, t_end, dt, printEveryNthTimeStep, p, &times);



    return EXIT_SUCCESS;
}
