#ifndef INIT_H
#define INIT_H

#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <chrono>
#include <hdf5.h>
#include "Globals.h"
#include "hdf5_hl.h"








typedef struct part{

  long double *x,*y,*z,
         *px,*py,*pz,
         *q,*m;


} particle;





particle init_1(int length){

        //generatur set up
       unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
       std::default_random_engine generator (seed);

        //get the first standard distribution
       std::normal_distribution<long double> distribution1(0, 55);

       //get the second standard distribution
       std::normal_distribution<long double> distribution2(10, 55);

       particle  p;
       int i;
       /*
       int  len = MAX ( ceil(length / processors) * ((int) processors -1 != id), floor(length / processors) * ((int) processors - 1 == id)),
            lowerBound = ceil(len / processors) * id,
            upperBound = MIN(ceil(len / processors) * (id + 1), len);
        */


        //Initialize the Positions
        p.x = (long double*)malloc(sizeof(long double)*length );
        p.y = (long double*)malloc(sizeof(long double)*length);
        p.z = (long double*)malloc(sizeof(long double)*length);

        //Initialize the Momentum
        p.px = (long double*)malloc(sizeof(long double)*length);
        p.py = (long double*)malloc(sizeof(long double)*length);
        p.pz = (long double*)malloc(sizeof(long double)*length);

        for(int i = 0; i < length; i++) {

            if(i < 5){

              p.px[i] = distribution1(generator);


            }
            else{

              p.px[i] = distribution2(generator);


            }

            p.py[i] = 0;
            p.pz[i] = 1e5;
            p.x[i]  = 10;
            p.y[i]  = 10;
            p.z[i]  = 10;
        }

        //Initialize the Mass & Charge

        p.q = (long double*)malloc(sizeof(long double)*length);

        for(int i = 0; i < length; i++) {
            p.q[i] = -1;
        }

        p.m = (long double*)malloc(sizeof(long double)*length);

        for(int i = 0; i < length; i++) {
            p.m[i] = 0.5e6;
        }

        return p;

 }

void init_params(long double* t_start, long double* t_end, long double* dt){

   *t_start = 0;
   *t_end   = 1e-10;
   *dt      = 1e-11;
}




void init_file(long double *t_start, long double *t_end,long double *dt, int *length){



      /*

      Init routine to initialize a HDF5 file!


      */

      int k =(int) ((*t_end-*t_start)/ *dt + 1);


      hsize_t dims[1];
      hid_t file,dataset,dataspace;
      herr_t status;



      file = H5Fcreate(FILENAME, H5F_ACC_TRUNC,H5P_DEFAULT,H5P_DEFAULT);
      dims[0] = 3*(*length)*k;
      dataspace = H5Screate_simple(1,dims,NULL);
      dataset = H5Dcreate2(file,GROUPNAME,H5T_NATIVE_DOUBLE,dataspace,H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
      status = H5Dclose(dataset);
      status = H5Sclose(dataspace);
      status = H5Fclose(file);
      printf("File Created!\n");

}


void initMem(int k, int len, double *t1){

      t1 = (double*) malloc(sizeof(double)*3*k*len);




}






#endif
