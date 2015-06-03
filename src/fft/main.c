#include <fftw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <hdf5.h>
#include <hdf5_hl.h>

int main(int argc, char** argv) {

    if(argc != 2) {

        printf("Missing file!\n");
        return 1;
        
    }

    printf("Initialising... ");
    fflush(stdout);

    unsigned long long lines = 0;
    unsigned long long i;
    
    //memory for fft
    double* array;
    fftw_complex *out, *out2;
    fftw_plan p,z;

    //hdf5-stuff
    hid_t file_id;
    int d1[1];
    hsize_t dims[1];
    herr_t status;

    file_id = H5Fopen(argv[1], H5F_ACC_RDONLY, H5P_DEFAULT);
    status  = H5LTget_dataset_info(file_id,"/signal",dims,NULL,NULL);

    lines = dims[0];
    array = (double*) fftw_malloc(sizeof(double) * lines);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * floor(lines / 4 + 1));
    out2 = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * floor(lines/4 +1));
    p = fftw_plan_dft_r2c_1d(lines/2, array, out, FFTW_MEASURE);
    
    printf("\b\b\b\b (%i records)... ", (int) lines / 2);
    fflush(stdout);

    status = H5LTread_dataset_double(file_id,"/signal",array);
    status = H5Fclose(file_id);

    double* a2 =(double*) malloc(sizeof(double)*lines/2);
    for(i = 0; i < lines/2;i++){
	
	    a2[i] = array[2*i+1]; 		    
		    
		    
    }
   z = fftw_plan_dft_r2c_1d(lines/2,array,out2,FFTW_MEASURE);

    for(i = 0; i < lines / 2; i++) {
	array[i] = array[2*i + 1];
    }

    printf("Done\nStarting FFT... ");
    fflush(stdout);
    
    fftw_execute(p); //do the ffw
    fftw_execute(z);
    printf("Done\nPrinting... ");
    fflush(stdout);

    //printing...
    hid_t dataspace, dataset;
    file_id = H5Fcreate("fftw.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    hsize_t dim[2] = {(hsize_t) floor(lines/4), 2};
    dataspace = H5Screate_simple(2, dim, NULL);
    dataset = H5Dcreate(file_id, "/fft", H5T_NATIVE_DOUBLE, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(dataset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, out);
    //H5LTmake_dataset(file_id, "/fft", 2, dims, H5T_NATIVE_DOUBLE, out);
    H5Dclose(dataset);
    H5Sclose(dataspace);
    H5Fclose(file_id);
    
    file_id = H5Fcreate("discr.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    dataspace = H5Screate_simple(2,dim,NULL);
    dataset = H5Dcreate(file_id,"/data",H5T_NATIVE_DOUBLE,dataspace,H5P_DEFAULT,H5P_DEFAULT,H5P_DEFAULT);
    H5Dwrite(dataset,H5T_NATIVE_DOUBLE,H5S_ALL,H5S_ALL,H5P_DEFAULT,out2);
    H5Dclose(dataset);
    H5Sclose(dataspace);
    H5Fclose(file_id);
    
    /*
    FILE* f = fopen("fftw.txt", "w+");
    for(i = 0; i < floor(lines / 4 + 1); i++) {

        fprintf(f, "% f % f\n", out[i][0]  , out[i][1] );//frequency, measure of intensity
        
    }
*/




    fftw_free(p);
    fftw_free(out);
    fftw_free(array);
    fftw_free(out2);
    fftw_free(a2);
    fftw_free(z);
    printf("Done\n--Finished--\n");
        
    return EXIT_SUCCESS;
}
