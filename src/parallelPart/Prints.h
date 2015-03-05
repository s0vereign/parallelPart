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






#endif
