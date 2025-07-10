#include <Python.h>
#include "matrix_object.h"
#include "matrix_row.h"
#include "utils.h"

int Row_init(RowObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"length", NULL};
    Py_ssize_t length;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &length))
        return -1;

    return Matrix_init((MatrixObject *)self, Py_BuildValue("(nn)", 1, length), NULL);
}

PyObject *Row_get(RowObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"i", NULL};
    Py_ssize_t i;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &i))
        return NULL;

    return get((MatrixObject *)self, 0, i);
}

PyObject *Row_set(RowObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"i", "value", NULL};
    Py_ssize_t i;
    double value;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "nd", kwlist, &i, &value))
        return NULL;

    Py_INCREF(self);
    return set((MatrixObject *)self, 0, i, value);
}

PyObject *Row_subscript(RowObject *self, PyObject *key)
{

    if (PyLong_Check(key))
    {
        Py_ssize_t col = PyLong_AsSsize_t(key);
        return PyFloat_FromDouble(get_from_table((MatrixObject *)self, 0, col));
    }

    // if (PySlice_Check(key)) {
    //     Py_ssize_t start, stop, step;
    //     if (PySlice_Unpack(key, &start, &stop, &step) < 0)
    //         return NULL;

    //     if (PySlice_AdjustIndices(((MatrixObject *)self)->cols, &start, &stop, step) < 0)
    //         return NULL;

    //     // Crée une nouvelle ligne contenant les colonnes start:stop
    //     return slice_row((MatrixObject *)self, start, stop, step);  // à définir
    // }

    PyErr_SetString(PyExc_TypeError, "Invalid index for Row");
    return NULL;
}

int Row_ass_subscript(RowObject *self, PyObject *key, PyObject *value_obj)
{

    if (PyLong_Check(key))
    {
        Py_ssize_t j = PyLong_AsSsize_t(key);

        if (j < 0 || j >= ((MatrixObject *)self)->cols)
        {
            PyErr_SetString(PyExc_IndexError, "index out of range");
            return -1;
        }

        double value = PyFloat_AsDouble(value_obj);
        if (PyErr_Occurred())
            return -1;

        set_in_table((MatrixObject *)self, 0, j, value);
        return 0;
    }

    PyErr_SetString(PyExc_TypeError, "Invalid index for Row");
    return -1;
}

PyMethodDef Row_methods[] = {
    {"get", (PyCFunction)Row_get, METH_VARARGS | METH_KEYWORDS, "Get value at (i)"},
    {"set", (PyCFunction)Row_set, METH_VARARGS | METH_KEYWORDS, "Set value at (i)"},
    {NULL}};
