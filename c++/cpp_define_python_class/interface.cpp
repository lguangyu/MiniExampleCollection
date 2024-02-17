#include "interface.hpp"


namespace foo_interface
{
	/* methods def */
	static const char* meth_get_hundred_docstr = "return interger 100";
	static const char* meth_get_bar_docstr = "get member string bar";
	static const char* meth_set_bar_docstr = "set member string bar";
	static const char* meth_get_a_docstr = "get member interger a";
	static const char* meth_set_a_docstr = "set member interger a";
	static PyMethodDef methods_def[] = {
		{"get_hundred", methwrap_get_hundred, METH_NOARGS, meth_get_hundred_docstr},
		{"get_bar", methwrap_get_bar, METH_NOARGS, meth_get_bar_docstr},
		{"set_bar", methwrap_set_bar, METH_VARARGS, meth_set_bar_docstr},
		{"get_a", methwrap_get_a, METH_NOARGS, meth_get_a_docstr},
		{"set_a", methwrap_set_a, METH_VARARGS, meth_set_a_docstr},
		{NULL, NULL, 0, NULL},
	};

	/* members def */
	static const char* member_bar_docstr = "a member string";
	static const char* member_a_docstr = "a member integer";
	static PyMemberDef members_def[] = {
		{"bar", T_OBJECT_EX, offsetof(FooObj, bar), 0, (char*)member_bar_docstr},
		{"a", T_INT, offsetof(FooObj, a), 0, (char*)member_a_docstr},
		{NULL, 0, 0, 0, NULL},
	};

	/* type object def  */
	static const char* class_name = "foo.Foo";
	static const char* class_docstr = "Foo class";
	static PyTypeObject FooType = {
		/* head, must be PyObject_VAR_HEAD */
		PyVarObject_HEAD_INIT(NULL, 0)
		/* class basics */
		class_name,						/* class name */
		sizeof(FooObj),					/* tp_basicsize */
		0,								/* tp_itemsize */
		/* basic methods */
		(destructor)tp_dealloc,			/* tp_dealloc, release member PyObject */
		0,								/* tp_vectorcall_offset, 3.7+ */
		NULL,							/* tp_getattr, deprecated */
		NULL,							/* tp_setattr, deprecated */
		NULL,							/* tp_as_async, PyAsyncMethods* */
		NULL,							/* tp_repr */
		/* standard magic methods */
		NULL,							/* tp_as_number, PyNumberMethods* */
		NULL,							/* tp_as_sequence, PySequenceMethods* */
		NULL,							/* tp_as_mapping, PyMappingMethods* */
		NULL,							/* tp_hash, i.e. self.__hash__() */
		NULL,							/* tp_call, i.e. self.__call__() */
		(reprfunc)NULL,					/* tp_str, i.e. self.__str__() */
		(getattrofunc)PyObject_GenericGetAttr, /* tp_getattro, i.e. self.__getattr__() */
		(setattrofunc)PyObject_GenericSetAttr, /* tp_setattro, i.e. self.__setattr__()*/
		NULL,							/* tp_as_buffer, PyBufferProcs* */
		Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags, unsigned long */
		class_docstr,					/* tp_doc, docstring */
		(traverseproc)tp_traverse,		/* tp_traverse, traverse through members */
		(inquiry)NULL,					/* tp_clear, delete members */
		(richcmpfunc)NULL,				/* tp_richcompare, rich-comparison */
		0,								/* tp_weaklistoffset, Py_ssize_t, weak ref enabler */
		NULL,							/* tp_iter, i.e. self.__iter__() */
		NULL,							/* tp_iternext, i.e. self.__next__() */
		/*(PyMethodDef*)*/methods_def,	/* tp_methods, methods def struct */
		/*(PyMemberDef*)*/members_def,	/* tp_members, members def struct */
		(PyGetSetDef*)NULL,				/* tp_getset, array-like access */
		NULL,							/* tp_base, struct _typeobject*, base type */
		NULL,							/* tp_dict, i.e. self.__dict__() */
		(descrgetfunc)NULL,				/* tp_descr_get */
		(descrsetfunc)NULL,				/* tp_descr_set */
		0,								/* tp_dictoffset */
		(initproc)tp_init,				/* tp_init i.e. self.__init___() */
		(allocfunc)NULL,				/* tp_alloc */
		(newfunc)tp_new,				/* tp_new, i.e. cls.__new__() */
		(freefunc)NULL,					/* tp_free */
		(inquiry)NULL,					/* tp_is_gc, gc-related */
		NULL,							/* tp_bases */
		NULL,							/* tp_mro, i.e. self.mro(), method resolution order */
		NULL,							/* tp_cache */
		NULL,							/* tp_subclasses */
		NULL,							/* tp_weaklist */
		NULL,							/* tp_del, i.e. self.__del__() */
		0,								/* tp_version_tag, unsigned int */
		(destructor)NULL,				/* tp_finalize */
		NULL,							/* tp_vectorcall, 3.7+ */
	};

	/* add type to module */
	static const char* class_raw_name = "Foo";
}; /* end of namespace Foo */


namespace foo_module
{
	static const char* name = "foo";
	static const char* docstr = "this is docstr of module 'foo'";

	static PyMethodDef methods[] = {
		{NULL, NULL, 0, NULL},
	};

	static struct PyModuleDef module_def = {
		PyModuleDef_HEAD_INIT,
		name, /* module name */
		docstr, /* module doc string, NULL safe */
		-1,
		methods,
	};
}; /* end of namespace foo_module */


namespace foo_interface
{
	/* methods */
	static int tp_init(FooObj* self, PyObject* args, PyObject* kwargs)
	{
		/* parse args */
		PyObject* bar;
		static char* kwlist[] = {"bar", "a", NULL};
		if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|", kwlist,
			&bar, &self->a))
			return -1;
		/* set value to member vars */
		PyObject* old_bar = self->bar;
		Py_XINCREF(bar);
		self->bar = bar;
		Py_XDECREF(old_bar);
		return 0;
	}


	static PyObject* tp_new(PyTypeObject* type, PyObject* args, PyObject* kwargs)
	{
		FooObj* self = (FooObj*)type->tp_alloc(type, 0);
		if (self == NULL)
			return NULL;
		self->bar = Py_None;
		Py_INCREF(Py_None);
		self->a = 0;
		return (PyObject*)self;
	}


	static int tp_traverse(FooObj* self, visitproc visit, void* arg)
	{
		Py_VISIT(self->bar);
		return 0;
	}


	static void tp_dealloc(FooObj* self)
	{
		Py_XDECREF(self->bar);
		Py_TYPE(self)->tp_free((PyObject*)self);
	}


	static PyObject* methwrap_get_hundred(PyObject* self, PyObject* args)
	{
		return Py_BuildValue("i", 100);
	}


	static PyObject* methwrap_get_bar(PyObject* self, PyObject* args)
	{
		return ((FooObj*)self)->bar;
	}


	static PyObject* methwrap_set_bar(PyObject* self, PyObject* args)
	{
		PyObject* bar;
		if (PyArg_ParseTuple(args, "O", &bar))
		{
			PyObject* old_bar = ((FooObj*)self)->bar;
			Py_XINCREF(bar);
			((FooObj*)self)->bar = bar;
			Py_XDECREF(old_bar);
		}
		Py_RETURN_NONE;
	}


	static PyObject* methwrap_get_a(PyObject* self, PyObject* args)
	{
		return Py_BuildValue("i", ((FooObj*)self)->a);
	}


	static PyObject* methwrap_set_a(PyObject* self, PyObject* args)
	{
		PyArg_ParseTuple(args, "i", &((FooObj*)self)->a);
		Py_RETURN_NONE;
	}


	/* add type to module */
	int add_to_module(PyObject *module)
	{
		if (PyType_Ready(&FooType))
			return -1;
		Py_INCREF(&FooType);
		if (PyModule_AddObject(module, class_raw_name, (PyObject*)&FooType))
		{
			Py_DECREF(&FooType);
			return -1;
		}
		return 0;
	}
}; /* end of namespace foo */


/* python module init */
PyMODINIT_FUNC PyInit_foo(void)
{
	PyObject *m;
	m = PyModule_Create(&foo_module::module_def);
	if (foo_interface::add_to_module(m))
		return NULL;
	return m;
}
