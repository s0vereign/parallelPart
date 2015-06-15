#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

#include <stdlib.h>
#include <stdio.h>

#include <hdf5.h>
#include <hdf5_hl.h>

#include <unistd.h>

#include "parallel_quicksort.h"

//Doc: https://docs.python.org/3.1/c-api/structures.html#PyMethodDef

static int parse_args(PyObject *args, const char** filename, int* serial, double* interval_length, int *interval_count)
{
    if (!PyArg_ParseTuple(args, "s|idi", filename, &serial, &interval_length, &interval_count)) {
        PyErr_SetString(PyExc_ValueError, "Couldn't parse arguments.");
        return -1;
	}
	
	return 0;
}

static int readFile(char** filename, double **array, int* lines) {
	
	//hdf5-stuff
    hid_t file_id;
    //~ int d1[1];
    hsize_t dims[1];
    //~ herr_t status;

	if( access(*filename, F_OK) ) {
		PyErr_SetString(PyExc_FileNotFoundError, "File not found");
		return -1;
	}
	if( access(*filename, R_OK) ) {
		PyErr_SetString(PyExc_PermissionError, "File reading permission denied!");
		return -1;
	}

    file_id = H5Fopen(*filename, H5F_ACC_RDONLY, H5P_DEFAULT);
    
    if(file_id < 0) {
		PyErr_SetString(PyExc_IOError, "File Could not be opened");
		return -1;
	}
    
    H5LTget_dataset_info(file_id,"/signal",dims,NULL,NULL);

    *lines = (int) dims[0];
    *array = (double*) malloc(sizeof(double) * (*lines));

    H5LTread_dataset_double(file_id,"/signal",*array);
    H5Fclose(file_id);
    
    return 0;
}

static int insertInIntervals(double* data, int len, double length, int count, int** result) {
	*result = (int*) malloc(sizeof(int) * count);
	
	int k = 0,
		j;
	
	for(int i = 0; i < count; i++) {	
		j = k;
		while(j < len && data[j] < (i + 1) * length / count) { j++; }
		
		(*result)[i] = j - k;
		k = j;
	}
	
	return 0;
}

static PyObject *process(PyObject *self, PyObject *args) {
	
	const char* filename;//reserve memory?
	int serial = 1000;
	double length = 2 * M_PI;
	int count = 1000;
	int return_code;
	
	return_code = parse_args(args, &filename, &serial, &length, &count);
	if( return_code < 0 ) {
		return NULL;
	}

	double* array;
	int lines;
	return_code = readFile(&filename, &array, &lines);
	if( return_code < 0) {
		return NULL;
	}
	
	printf("Sorting\n");
	quick_sort(array, lines, serial);
	
	printf("Seperating\n");
	int* result;
	insertInIntervals(array, lines, length, count, &result);
	free(array);
	
	//generate numpy-array
	int nd = 1; //1 dimension
	npy_intp dims[nd];
	dims[0] = count;
	
	PyObject* numpylist = PyArray_New(&PyArray_Type, nd, dims, NPY_INT, NULL, result, 0, NPY_ARRAY_C_CONTIGUOUS | NPY_ARRAY_WRITEABLE, NULL);
	
	if( numpylist == NULL ) {
		return NULL;
	}
	PyArray_ENABLEFLAGS(numpylist, NPY_ARRAY_OWNDATA);
	
	return numpylist;
}

static struct PyMethodDef PyInit_process_distribution_methods[] = {{
   "process",
   process,
   METH_VARARGS,
   "actual function doing the stuff"
}};

//Doc: https://docs.python.org/3.1/c-api/module.html#PyModuleDef
static PyModuleDef PyInit_process_distribution_module = { 
	PyModuleDef_HEAD_INIT,
    "read_sort",
    "Reads H5-File with specific format and sorts the content",
    -1,
    PyInit_process_distribution_methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC
PyInit_process_distribution(void)
{
	PyObject* m = PyModule_Create(&PyInit_process_distribution_module);
	if( m == NULL) {
		return NULL;
	}
	
	import_array()
	
	return m;
}
