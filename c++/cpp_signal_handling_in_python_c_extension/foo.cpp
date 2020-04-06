#include "Python.h"
#include <iostream>
#include <ctime>


PyObject* wait_for_enter(PyObject* self, PyObject* no_arg)
{
	std::cin.ignore();
	Py_RETURN_NONE;
}

PyObject* posix_sleep(PyObject* self, PyObject* args)
{
	unsigned duration_sec;
	if (PyArg_ParseTuple(args, "I", &duration_sec) == 0)
		return NULL;
	sleep(duration_sec);
	Py_RETURN_NONE;
}

PyObject* loop_wait(PyObject* self, PyObject* args)
{
	unsigned duration_sec;
	if (PyArg_ParseTuple(args, "I", &duration_sec) == 0)
		return NULL;

	const std::clock_t start = clock();
	const std::clock_t duration_clocks = duration_sec * CLOCKS_PER_SEC;
	while (clock() < (start + duration_clocks))
		if (PyErr_CheckSignals())
			return NULL;
	Py_RETURN_NONE;
}

extern "C"
{

static PyMethodDef foo_meth_def[] = {
	{"wait_for_enter", wait_for_enter, METH_NOARGS, NULL},
	{"posix_sleep", posix_sleep, METH_VARARGS, NULL},
	{"loop_wait", loop_wait, METH_VARARGS, NULL},
	{NULL, NULL, 0, NULL},
};

static struct PyModuleDef foo_module_def = {
	PyModuleDef_HEAD_INIT,
	"foo",
	NULL,
	-1,
	foo_meth_def
};


/* python module init */
PyMODINIT_FUNC PyInit_foo(void)
{
	PyObject *m;
	m = PyModule_Create(&foo_module_def);
	return m;
}

};
