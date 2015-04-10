#include <fftw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <hdf5.h>
#include <hdf5_hl.h>
#define DT 1e-10

int main(int argc, char** argv) {

    if(argc != 2) {

        printf("Missing file!\n");
        return 1;
        
    }

    printf("Counting lines... ");
    fflush(stdout);

    //first: let count lines
    unsigned int lines = 0;
    FILE *f = fopen(argv[1], "r");
    fread(&lines, sizeof(int), 1, f);
    
    
    int i;
    printf("%u\nInitialising FFT... ", lines);
    fflush(stdout);

    //memory for fft
    double* array;
    fftw_complex *out;
    fftw_plan p;

    long double* tmp = (long double*) malloc(sizeof(long double) * lines);
    array = (double*) fftw_malloc(sizeof(double) * lines);

    fread(tmp, sizeof(long double), lines, f);
    fclose(f);

    hid_t file_id;
    int d1[1];
    hsize_t dims[1];
    herr_t status;

    file_id = H5Fopen(argv[1], H5F_ACC_RDONLY, H5P_DEFAULT);
    status  = H5LTget_dataset_info(file_id,"/signal",dims,NULL,NULL);
    double* data = (double*) malloc(sizeof(double)*((int)dims[0]));
    status = H5LTread_dataset_double(file_id,"/signal",data);
    status = H5Fclose(file_id);

    printf("File read! \n");



    for(i = 0 ; i < (int)dims[0];i++){

	printf("data:%e \n",data[i]);


    }
/*





        
        
        
    
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * floor(lines / 2 + 1));

    p = fftw_plan_dft_r2c_1d(lines, array, out, FFTW_MEASURE);


    printf("Done\nStarting FFT... ");
    fflush(stdout);
    
    fftw_execute(p); //do the ffw

    printf("Done\nPrinting... ");
    fflush(stdout);

    //printing...
    f = fopen("fftw.txt", "w+");
    for(i = 0; i < floor(lines / 2 + 1); i++) {

        fprintf(f, "%f %f\n", floor(out[i][0]   +.5), floor(out[i][1]  +.5));//frequency, measure of intensity
        
    }

    fftw_free(p);
    fftw_free(out);
    fftw_free(array);

    printf("Done\n--Finished--\n");
    
    return EXIT_SUCCESS;*/
}
