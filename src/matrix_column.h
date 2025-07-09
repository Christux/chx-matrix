#ifndef MATRIXCOLUMN_H
#define MATRIXCOLUMN_H

#include <Python.h>
#include "matrix.h"
#include "utils.h"

int Column_init(ColumnObject *self, PyObject *args, PyObject *kwds);

PyObject *Column_get(ColumnObject *self, PyObject *args, PyObject *kwds);

PyObject *Column_set(ColumnObject *self, PyObject *args, PyObject *kwds);

PyObject *Column_subscript(ColumnObject *self, PyObject *key);

int Column_ass_subscript(ColumnObject *self, PyObject *key, PyObject *value_obj);

inline static PyObject *create_column_from_matrix(MatrixObject *self, Py_ssize_t rows, Py_ssize_t stride_i, Py_ssize_t stride_j, Py_ssize_t offset)
{

    PyTypeObject *type = &ColumnType;

    ColumnObject *col = (ColumnObject *)type->tp_alloc(type, 0);
    if (!col)
        return NULL;

    Py_INCREF(self->data_obj);

    instanciate_matrix((MatrixObject *)col, rows, 1, stride_i, stride_j, offset, self->data_obj);

    return (PyObject *)col;
}

#endif