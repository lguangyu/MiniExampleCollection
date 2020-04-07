#include "Python.h"
#include <ctime>
#include <iostream>
#include <csignal>
#include <exception>


namespace custom_singal
{

static volatile std::sig_atomic_t sigint_set;
static struct sigaction old_act;

void custom_signal_handler(int sig)
{
	sigint_set = 1;
	return;
}

void init_with_custom_sigint_handler(void)
{
	/* preserve old signal handler */
	sigaction(SIGINT, NULL, &old_act);
	/* install custom */
	std::signal(SIGINT, custom_signal_handler);
	/* reset the flag to zero */
	sigint_set = 0;
	return;
}

void restore_python_sigint_handler(void)
{
	std::signal(SIGINT, old_act.sa_handler);
	return;
}

};


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

PyObject* loop_wait_custom_handler(PyObject* self, PyObject* args)
{
	::custom_singal::init_with_custom_sigint_handler();

	unsigned duration_sec;
	if (PyArg_ParseTuple(args, "I", &duration_sec) == 0)
		return NULL;

	const std::clock_t start = clock();
	const std::clock_t duration_clocks = duration_sec * CLOCKS_PER_SEC;
		while (clock() < (start + duration_clocks))
			if (::custom_singal::sigint_set)
			{
				::custom_singal::restore_python_sigint_handler();
				PyErr_SetInterrupt();
				PyErr_CheckSignals();
				return NULL;
			}
	Py_RETURN_NONE;
}

extern "C"
{

static PyMethodDef foo_meth_def[] = {
	{"wait_for_enter", wait_for_enter, METH_NOARGS, NULL},
	{"posix_sleep", posix_sleep, METH_VARARGS, NULL},
	{"loop_wait", loop_wait, METH_VARARGS, NULL},
	{"loop_wait_custom_handler", loop_wait_custom_handler, METH_VARARGS, NULL},
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
