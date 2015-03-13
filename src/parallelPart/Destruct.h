#ifndef DESTRUCT_H
#define DESTRUCT_H

#include <stdlib.h>
#include "Init.h"

void destruct(
    int len,
    long double t_start, long double t_end, long double dt,
    long double beamspeed, long double circumference,
    particle p, long double ***times
) {

    free(p.x);
    free(p.y);
    free(p.z);
    free(p.px);
    free(p.py);
    free(p.pz);
    free(p.q);
    free(p.m);

    int s =(int) ceil(((t_end) - (t_start)) * (beamspeed) / (circumference) + 3),
        i;

    for( i = 0; i < s; i++) {
        
        free((*times)[i]);
        
    }
    
    free(*times);

}
#endif
