#ifndef DESTRUCT_H
#define DESTRUCT_H

#include <stdlib.h>
#include "Init.h"

void destruct(
    int len,
    long double t_start, long double t_end, long double dt,
    int printEveryNthTimeStep,
    particle p, long double ***vel_res
) {

    free(p.x);
    free(p.y);
    free(p.z);
    free(p.px);
    free(p.py);
    free(p.pz);
    free(p.q);
    free(p.m);

    int s =(int) ((t_end-t_start)/dt / printEveryNthTimeStep),
        i;

    for( i = 0; i < s; i++) {
        
        free((*vel_res)[i]);
        
    }
    
    free(*vel_res);

}
#endif
