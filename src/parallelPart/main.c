#include <stdio.h>
#include "Init.c"
#include "Destruct.c"
#include "Compute.c"
#include "Params.c"





void main() {






//initialize the particles
  int len = 1000;
  particle p = init_1(len);
  double s[3] = init_params();

//start the computation with p

  compute(s[0],s[1],s[2],
          p.x,p.y,p.z,
          p.px,p.py,p.pz
          p.m,p.q, len);



  destruct(p);






}
