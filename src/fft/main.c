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
    fftw_complex *out;
    fftw_plan p;

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
    p = fftw_plan_dft_r2c_1d(lines/2, array, out, FFTW_MEASURE);

    printf("\b\b\b\b (%i records)... ", (int) lines / 2);
    fflush(stdout);

    status = H5LTread_dataset_double(file_id,"/signal",array);
    status = H5Fclose(file_id);

    for(i = 0; i < lines / 2; i++) {
	array[i] = array[2*i + 1];
    }

    printf("Done\nStarting FFT... ");
    fflush(stdout);
    
    fftw_execute(p); //do the ffw

    printf("Done\nPrinting... ");
    fflush(stdout);

    //printing...
    FILE* f = fopen("fftw.txt", "w+");
    for(i = 0; i < floor(lines / 4 + 1); i++) {

        fprintf(f, "% f % f\n", out[i][0]  , out[i][1] );//frequency, measure of intensity
        
    }

    fftw_free(p);
    fftw_free(out);
    fftw_free(array);

    printf("Done\n--Finished--\n");
    
    return EXIT_SUCCESS;
}
