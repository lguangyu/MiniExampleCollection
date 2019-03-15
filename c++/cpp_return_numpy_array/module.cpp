extern "C"
{

#include <Python.h>
#define NPY_NO_DEPRECATED_API 14 /* suppres annoying warnings */
#include <numpy/ndarrayobject.h>

}; /* end of extern "C" */


PyObject* get_ndarray_2x3(void)
{
	/* shape of the array to create */
	int nd = 2;
	long int dim_s[2] = {2, 3};
	/* create ndarray */
	/* NPY_DOUBLE is an enum type */
	PyObject *arr = PyArray_ZEROS(nd, dim_s, NPY_DOUBLE, 0);
	/* write some data in */
	/* first get the data buffer */
	/* NOTE: arr->data may be deprecated in newer versions */
	double *data = reinterpret_cast< double* >
		(PyArray_DATA(reinterpret_cast< PyArrayObject* >(arr)));
	/* data buffer has 6 elements */
	data[0] = 1.5;
	data[1] = 1e20;
	data[2] = 1.0;
	data[3] = 2.0;
	data[4] = -10;
	data[5] = 100;
	return arr;
}


/* wrap functions */
PyObject* wrap_get_ndarray_2x3(PyObject* self, PyObject *no_arg)
{
	return get_ndarray_2x3();
}


/* python module interface */
extern "C"
{

static PyMethodDef module_meth[] = {
	{"get_ndarray_2x3", wrap_get_ndarray_2x3,
		METH_NOARGS, "get a 2-d array with size 2x3"},
	{NULL, NULL, 0, NULL},
};

#if (PY_MAJOR_VERSION >= 3)

static struct PyModuleDef module_def = {
	PyModuleDef_HEAD_INIT,
	"module", /* module name */
	NULL, /* module doc string, NULL safe */
	-1,
	module_meth,
};

PyMODINIT_FUNC PyInit_module(void)
{
	import_array();
	return PyModule_Create(&module_def);
}

#else
#	error NOT SUPPORT PYTHON 2.X
#endif /* PY_MAJOR_VERION >= 3 */

}; /* end of extern "C" */
