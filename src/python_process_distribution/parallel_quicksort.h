#ifndef PARALLEL_QUICKSORT
#define PARALLEL_QUICKSORT

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//from http://www.oracle.com/technetwork/server-storage/solarisstudio/documentation/oss-openmp-30-wp-183987.pdf

int partition (int p, int r, double *data)
{
	double x = data[p];
	int k = p;
	int l = r + 1;
	double t;

	do
		k++;
	while ((data[k] <= x) && (k < r));
	do
		l--;
	while (data[l] > x);
	
	while (k < l) {
		t = data[k];
		data[k] = data[l];
		data[l] = t;
		do
			k++;
		while (data[k] <= x);
		do
			l--;
		while (data[l] > x);
	}
	t = data[p];
	data[p] = data[l];
	data[l] = t;
	return l;
}

void seq_quick_sort (int p, int r, double *data)
{
	if (p < r) {
		int q = partition (p, r, data);
		seq_quick_sort (p, q - 1, data);
		seq_quick_sort (q + 1, r, data);
	}
}
void rec_quick_sort (int p, int r, double *data, int low_limit)
{
	if (p < r) {
		if ((r - p) < low_limit) {
			seq_quick_sort (p, r, data);
		}
		else {
			int q = partition (p, r, data);
			#pragma omp task firstprivate(data, low_limit, r, q)
				rec_quick_sort (p, q - 1, data, low_limit);
			#pragma omp task firstprivate(data, low_limit, r, q)
				rec_quick_sort (q + 1, r, data, low_limit);
		}
	}
}

void quick_sort (double *data, int n, int low_limit)
{
#pragma omp parallel
{
	#pragma omp single nowait
		rec_quick_sort (0, n - 1, data, low_limit);
}
}

/*

int	main (int argc, char *argv[])
{
	int i, n, low_limit;
	float *data;
	
	if (argc != 3) {
		printf ("a.out num_elems low_limit\n");
		return 1;
	}
	
	n = atoi(argv[1]);
	low_limit = atoi(argv[2]);
	*
	* Generate the array.
	*
	data = (float *)malloc (sizeof (float) * n);
	#pragma omp parallel for default(none) shared(data, n) private(i)
	for ( i=0; i<n; i++ ) {
		data[i] = 1.1 * rand() * 5000 / RAND_MAX;
	}
	
	printf ("\nSorting %d numbers using OpenMP tasks...\n\n", n);
	
	struct timespec start, end;
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	par_quick_sort (n - 1, &data[0], low_limit);
	
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	printf("Sorting lasts for %d.%d seconds.\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
	
	printf ("Done\n");
	validate_sort (n, &data[0]);
	
	free (data);
	return 0;
}
* */

#endif
