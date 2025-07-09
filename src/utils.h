#ifndef UTILS_H
#define UTILS_H

#include <Python.h>
#include "matrix.h"

inline static double get_from_table(MatrixObject *self, Py_ssize_t i, Py_ssize_t j)
{
    return self->data_obj->data[i * self->stride_i + j * self->stride_j + self->offset];
}

inline static void set_in_table(MatrixObject *self, Py_ssize_t i, Py_ssize_t j, double value)
{
    self->data_obj->data[i * self->stride_i + j * self->stride_j + self->offset] = value;
}

inline static int instanciate_matrix(MatrixObject *self, Py_ssize_t rows, Py_ssize_t cols, Py_ssize_t stride_i, Py_ssize_t stride_j, Py_ssize_t offset, MatrixDataObject *data_obj)
{
    if (rows <= 0 || cols <= 0)
    {
        PyErr_SetString(PyExc_ValueError, "rows and cols must be > 0");
        return -1;
    }

    self->rows = rows;
    self->cols = cols;
    self->stride_i = stride_i;
    self->stride_j = stride_j;
    self->offset = offset;
    self->data_obj = data_obj;

    return 0;
}

inline static PyObject *get(MatrixObject *self, Py_ssize_t i, Py_ssize_t j)
{
    if (i < 0 || i >= self->rows || j < 0 || j >= self->cols)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    return PyFloat_FromDouble(get_from_table(self, i, j));
}

inline static PyObject *set(MatrixObject *self, Py_ssize_t i, Py_ssize_t j, double value)
{
    if (i < 0 || i >= self->rows || j < 0 || j >= self->cols)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    set_in_table(self, i, j, value);

    return (PyObject *)self;
}

#endif