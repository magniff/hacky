#include <Python.h>


static PyObject*
set_class(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyObject *cls;

    if (!PyArg_UnpackTuple(args, "set_class", 2, 2, &obj, &cls))
        return NULL;

    obj->ob_type = cls;
    return obj;
}


PyLongObject *
get_flags(PyObject *self, PyObject *args)
{
    PyTypeObject *cls;

    if (!PyArg_UnpackTuple(args, "get_flags", 1, 1, &cls))
        return NULL;

    return PyLong_FromUnsignedLong(cls->tp_flags);
}


PyTypeObject *
set_flags(PyObject *self, PyObject *args)
{
    PyTypeObject *cls;
    PyLongObject *flags_object;

    if (!PyArg_UnpackTuple(args, "set_flags", 2, 2, &cls, &flags_object))
        return NULL;

    unsigned long flags = PyLong_AsUnsignedLong(flags_object);
    cls->tp_flags = flags;
    return cls;
}


static PyMethodDef HackyMethods[] = {
    {
        "set_class",  set_class,
        METH_VARARGS, "Sets type."
    },
    {
        "get_flags",  get_flags,
        METH_VARARGS, "Get type`s flags."
    },
    {
        "set_flags",  set_flags,
        METH_VARARGS, "Set type`s flags."
    },
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


static struct PyModuleDef hackymodule = {
    PyModuleDef_HEAD_INIT,
    "hacky",  /* name of module */
    0,  /* module documentation, may be NULL */
   -1,  /* size of per-interpreter state of the module,
           or -1 if the module keeps state in global variables. */
   HackyMethods
};


PyMODINIT_FUNC
PyInit_hacky(void)
{
    return PyModule_Create(&hackymodule);
}
