#include <Python.h>
#include <frameobject.h>
#include <pystate.h>

PyObject *
set_class(PyObject *self, PyObject *args)
{
    PyObject *obj;
    PyTypeObject *cls;

    if (!PyArg_UnpackTuple(args, "set_class", 2, 2, &obj, &cls))
        return NULL;

    obj->ob_type = cls;
    Py_RETURN_NONE;
}

PyObject *
read_memory_in(PyObject *self, PyObject *args)
{
    PyObject *address_object;
    if (!PyArg_UnpackTuple(args, "read_memory_in", 1, 1, &address_object))
        return NULL;

    void *address = PyLong_AsVoidPtr(address_object);
    return PyLong_FromUnsignedLong(*((unsigned char *)address));
}

PyObject *
write_memory_in(PyObject *self, PyObject *args)
{
    PyObject *address_object;
    PyObject *new_data_object;
    if (!PyArg_UnpackTuple(args, "write_memory_in", 2, 2, &address_object, &new_data_object))
        return NULL;

    unsigned char *address =
        (unsigned char *)PyLong_AsVoidPtr(address_object);
    unsigned char new_data =
        (unsigned char)PyLong_AsUnsignedLong(new_data_object);

    *address = new_data;
    Py_RETURN_NONE;
}

PyObject *
run_frame(PyObject *self, PyObject *args)
{
    PyThreadState *current_state = PyThreadState_Get();
    PyFrameObject *f;
    if (!PyArg_UnpackTuple(args, "run_frame", 1, 1, &f))
        return NULL;
    current_state->frame = f;
    f->f_back = f;
    return PyEval_EvalFrame(f);
}

PyObject *
get_flags(PyObject *self, PyObject *args)
{
    PyTypeObject *cls;
    if (!PyArg_UnpackTuple(args, "get_flags", 1, 1, &cls))
        return NULL;

    return PyLong_FromUnsignedLong(cls->tp_flags);
}

PyObject *
set_flags(PyObject *self, PyObject *args)
{
    PyTypeObject *cls;
    PyLongObject *flags_object;

    if (!PyArg_UnpackTuple(args, "set_flags", 2, 2, &cls, &flags_object))
        return NULL;

    unsigned long flags = PyLong_AsUnsignedLong(flags_object);
    cls->tp_flags = flags;
    Py_RETURN_NONE;
}

PyObject *
fetch_dict(PyObject *self, PyObject *args)
{
    PyTypeObject *type;
    PyObject *dictobject;
    if (!PyArg_UnpackTuple(args, "fetch_dict", 1, 1, &type))
        return NULL;
    dictobject = type->tp_dict;
    Py_INCREF(dictobject);
    return dictobject;
}

static PyMethodDef HackyMethods[] = {
    {"set_class", set_class,
     METH_VARARGS, "Sets type."},
    {"get_flags", get_flags,
     METH_VARARGS, "Get type`s flags."},
    {"read_memory_in", read_memory_in,
     METH_VARARGS, "Get type`s flags."},
    {"write_memory_in", write_memory_in,
     METH_VARARGS, "Get type`s flags."},
    {"set_flags", set_flags,
     METH_VARARGS, "Set type`s flags."},
    {"run_frame", run_frame,
     METH_VARARGS, "Evals frame."},
    {"fetch_dict", fetch_dict,
     METH_VARARGS, "Returns actual type`s dictionary."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef hackymodule = {
    PyModuleDef_HEAD_INIT,
    "hacky", /* name of module */
    0,       /* module documentation, may be NULL */
    0,       /* size of per-interpreter state of the module,
           or -1 if the module keeps state in global variables. */
    HackyMethods};

PyMODINIT_FUNC
PyInit_hacky(void)
{
    return PyModule_Create(&hackymodule);
}
