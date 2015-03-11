#ifndef SAVE_H
#define SAVE_H


#include "Globals.h"
#include <hdf5.h>


void save(double ****pos){


    herr_t status;
    hid_t  file_id, dataset_id;

    file_id = H5Fopen(FILENAME, H5F_ACC_RDWR, H5P_DEFAULT);
    dataset_id = H5Dopen2(file_id, GROUPNAME, H5P_DEFAULT);
    status = H5Dwrite(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT,
                     *pos);

    status = H5Dclose(dataset_id);
    status = H5Fclose(file_id);





}



#endif
