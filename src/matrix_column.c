#include <Python.h>
#include "matrix_object.h"
#include "matrix_column.h"
#include "utils.h"

int Column_init(ColumnObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"length", NULL};
    Py_ssize_t length;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &length))
        return -1;

    return Matrix_init((MatrixObject *)self, Py_BuildValue("(nn)", length, 1), NULL);
}

PyObject *Column_get(ColumnObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"i", NULL};
    Py_ssize_t i;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &i))
        return NULL;

    return get((MatrixObject *)self, i, 0);
}

PyObject *Column_set(ColumnObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"i", "value", NULL};
    Py_ssize_t i;
    double value;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "nd", kwlist, &i, &value))
        return NULL;

    Py_INCREF(self);
    return set((MatrixObject *)self, i, 0, value);
}

PyObject *Column_subscript(ColumnObject *self, PyObject *key)
{

    if (PyLong_Check(key))
    {
        Py_ssize_t row = PyLong_AsSsize_t(key);
        return PyFloat_FromDouble(get_from_table((MatrixObject *)self, row, 0));
    }

    PyErr_SetString(PyExc_TypeError, "Invalid index for Row");
    return NULL;
}

int Column_ass_subscript(ColumnObject *self, PyObject *key, PyObject *value_obj)
{

    if (PyLong_Check(key))
    {
        Py_ssize_t i = PyLong_AsSsize_t(key);

        if (i < 0 || i >= ((MatrixObject *)self)->rows)
        {
            PyErr_SetString(PyExc_IndexError, "index out of range");
            return -1;
        }

        double value = PyFloat_AsDouble(value_obj);
        if (PyErr_Occurred())
            return -1;

        set_in_table((MatrixObject *)self, i, 0, value);
        return 0;
    }

    PyErr_SetString(PyExc_TypeError, "Invalid index for Row");
    return -1;
}

PyMethodDef Column_methods[] = {
    {"get", (PyCFunction)Column_get, METH_VARARGS | METH_KEYWORDS, "Get value at (i)"},
    {"set", (PyCFunction)Column_set, METH_VARARGS | METH_KEYWORDS, "Set value at (i)"},
    {NULL}};