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

void print(long double t,
    long double x[], long double y[], long double z[],
    long double px[], long double py[], long double pz[],
    int len
) {
    //copy for each time-step the position data for all particle in one row
    //and put this row into the output file
    //2 buffer neccessary (for lazy people): one small buffer for position data
    //for one particle (buf), a 2nd for the position data of all particle (buffer)
    FILE *f = fopen("results.txt", "a+");

    int i;
    char buf[BUF];
    char *buffer = (char*) malloc(sizeof(char) * len * BUF);
    strcpy(buffer, ""); //neccessary for using strcat - it expects a '\0' for concat
    
    for(i = 0; i < len; i++) {
        snprintf(buf, 100, "%014.10Lf %014.10Lf %014.10Lf ", x[i], y[i], z[i]);
        strcat(buffer, buf);
    }
    
    strcat(buffer, "\n");
    fwrite( buffer, sizeof(char), strlen(buffer), f);

    free(buffer);
    fclose(f);
}

#endif
