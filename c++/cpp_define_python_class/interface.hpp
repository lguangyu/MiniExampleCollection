#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include <Python.h>
#include <structmember.h>


namespace foo_interface
{
	/* struct of Foo instance */
	struct FooObj
	{
		PyObject_HEAD
		PyObject* bar;
		int a;
	};

	/* basic methods */
	static int tp_init(FooObj* self, PyObject* args, PyObject* kwargs);
	static PyObject* tp_new(PyTypeObject* type, PyObject* args, PyObject* kwargs);
	static int tp_traverse(FooObj* self, visitproc visit, void* arg);
	static void tp_dealloc(FooObj* self);

	/* extended methods */
	static PyObject* methwrap_get_hundred(PyObject* self, PyObject* args);
	static PyObject* methwrap_get_bar(PyObject* self, PyObject* args);
	static PyObject* methwrap_set_bar(PyObject* self, PyObject* args);
	static PyObject* methwrap_get_a(PyObject* self, PyObject* args);
	static PyObject* methwrap_set_a(PyObject* self, PyObject* args);

	int add_to_module(PyObject *module);
}; /* end of namespace Foo */


/* python module init */
extern "C"
{

PyMODINIT_FUNC PyInit_foo(void);

}; /* end of extern "C" */

#endif /* __INTERFACE_HPP__ */
