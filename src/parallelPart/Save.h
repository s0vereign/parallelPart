#ifndef SAVE_H
#define SAVE_H

#include <hdf5_hl.h>
#include "Globals.h"
#include <hdf5.h>


void save(double **pos,int k,int len){



    hid_t       file_id;
    hsize_t     dims[1]={(hsize_t)k*len*3};
    herr_t      status;

    file_id = H5Fcreate (FILENAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    status = H5LTmake_dataset(file_id,"/dset",1,dims,H5T_NATIVE_DOUBLE,*pos);
    status = H5Fclose (file_id);






}



#endif
