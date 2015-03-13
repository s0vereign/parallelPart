#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 100

void truncateFile() {
    FILE *f = fopen("results.txt", "w+");
    fclose(f);
}

//not used
void print(long double t,
    long double x[], long double y[], long double z[],
    long double px[], long double py[], long double pz[],
    int len
) {
    FILE *f = fopen("results.txt", "a+");

    int i;
    char buf[BUF];
    char *buffer = (char*) malloc(sizeof(char) * len * BUF);
    strcpy(buffer, "");
    for(i = 0; i < len; i++) {
        snprintf(buf, 100, "%014.10Lf %014.10Lf %014.10Lf ", x[i], y[i], z[i]);
        strcat(buffer, buf);
    }
    strcat(buffer, "\n");
    fwrite( buffer, sizeof(char), strlen(buffer), f);

    free(buffer);
    fclose(f);
}

void print_array(   long double t_start, long double t_end, long double dt,
                    int length, int printEveryNthTimeStep,
                    long double ***result
) {

    FILE *f = fopen("results.txt", "a+");

    int i,j;
    long double t;
    char buf[BUF];
    char *buffer = (char*) malloc(sizeof(char) * length * BUF);

    for( t = t_start,j = 0; t < t_end - dt; t += printEveryNthTimeStep * dt, j++)  {

        strcpy(buffer, "");

        for(i = 0; i < length; i++) {

            snprintf(buf, 100, "%014.10Lf ", (*result)[j][i]);
            strcat(buffer, buf);

        }

        strcat(buffer, "\n");
        fwrite( buffer, sizeof(char), strlen(buffer), f);
    }

    free(buffer);
    fclose(f);

}

void truncate_signals(){

    FILE *f = fopen("signals.txt", "w+");
    printf("signals.txt created \n");
    fclose(f);

}



void print_signal(long double ***sign, int length, int k){


    FILE *f = fopen("signals.txt", "a+");
    char buf[BUF];
    char *buffer = (char*) malloc(sizeof(char) * length * BUF);
    strcpy(buffer, "");

    for(int j = 0 ; j < k ; j++){

        for(int i = 0 ; i < length; i++){

            snprintf(buf, 100, " %014.10Lf", (*sign)[j][i]);
            strcat(buffer,buf);

        }
        strcat(buffer, "\n");

    }
    fwrite(buffer, sizeof(char),strlen(buffer),f);

    free(buffer);
    fclose(f);



}







#endif
