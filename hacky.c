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


static PyMethodDef HackyMethods[] = {
    {"set_class",  set_class, METH_VARARGS,
     "Execute a shell command"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


static struct PyModuleDef hackymodule = {
   PyModuleDef_HEAD_INIT,
   "hacky",   /* name of module */
   0, /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   HackyMethods
};


PyMODINIT_FUNC
PyInit_hacky(void)
{
    PyObject *m;
    return PyModule_Create(&hackymodule);
}

