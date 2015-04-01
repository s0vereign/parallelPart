#include <fftw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

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
    int i;
    char buf[250], ret[50];
    snprintf(buf, 250, "wc -l %s", argv[1]);
    FILE *pipe = popen(buf, "r");
    fgets(ret, 50, pipe);
    sscanf(ret, "%i", &lines);
    pclose(pipe);

    printf("%u\nInitialising FFT... ", lines);
    fflush(stdout);

    //memory for fft
    double* array;
    fftw_complex *out;
    fftw_plan p;

    
    array = (double*) fftw_malloc(sizeof(double) * lines);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * floor(lines / 2 + 1));

    p = fftw_plan_dft_r2c_1d(lines, array, out, FFTW_MEASURE);


    //read file
    FILE *f = fopen(argv[1], "r");
    for(i = 0; i < lines; i++) {

        fscanf(f, "%lf\n", &array[i]);
        
    }
    fclose(f);

    printf("Done\nStarting FFT... ");
    fflush(stdout);
    
    fftw_execute(p); //do the ffw
    
    printf("Done\nConverting... ");

    //fft done here. as a measure of the intensity: add the components sqared (i.e. Im^2 + Re^2). no root as very time consuming. Re-use input-array
    //~ for(i = 0; i < lines; i++) {
//~ 
        //~ array[i] = out[i][0] * out[i][0] + out[i][1] * out[i][1];
        //~ 
    //~ }

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
    
    return EXIT_SUCCESS;
}
