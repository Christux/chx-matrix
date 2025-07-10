#ifndef MATRIXROW_H
#define MATRIXROW_H

#include <Python.h>
#include "matrix.h"
#include "utils.h"

int Row_init(RowObject *self, PyObject *args, PyObject *kwds);

PyObject *Row_get(RowObject *self, PyObject *args, PyObject *kwds);

PyObject *Row_set(RowObject *self, PyObject *args, PyObject *kwds);

PyObject *Row_subscript(RowObject *self, PyObject *key);

int Row_ass_subscript(RowObject *self, PyObject *key, PyObject *value_obj);

inline static PyObject *create_row_from_matrix(MatrixObject *self, Py_ssize_t cols, Py_ssize_t stride_i, Py_ssize_t stride_j, Py_ssize_t offset)
{
    PyTypeObject *type = &RowType;

    RowObject *row = (RowObject *)type->tp_alloc(type, 0);
    if (!row)
        return NULL;

    Py_INCREF(self->data_obj);

    instanciate_matrix((MatrixObject *)row, 1, cols, stride_i, stride_j, offset, self->data_obj);

    return (PyObject *)row;
}

#endif