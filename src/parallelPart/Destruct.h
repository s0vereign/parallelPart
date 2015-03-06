#ifndef DESTRUCT_H
#define DESTRUCT_H

#include <stdlib.h>
#include "Init.h"

void destruct(particle p){

  free(p.x);
  free(p.y);
  free(p.z);
  free(p.px);
  free(p.py);
  free(p.pz);
  free(p.q);
  free(p.m);


}
#endif
