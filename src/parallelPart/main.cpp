#include <stdio.h>

#include "Init.h"
#include "Destruct.h"
#include "Compute.h"
#include "Params.h"
#include "Prints.h"





int main(int argc, char** argv) {

    //initialize the particles
      int len;
      
      if( argc == 2) {
          len = atoi(argv[1]);
      }
      else {
          len = 5;
      }
      
      long double t_start, t_end, dt;
      particle p = init_1(len);
      init_params(&t_start, &t_end, &dt);
      //~ truncateFile();

    //start the computation with p
      compute(t_start, t_end, dt,
              p.x,p.y,p.z,
              p.px,p.py,p.pz,
              p.m,p.q, len);


      destruct(p);

      return EXIT_SUCCESS;
}
