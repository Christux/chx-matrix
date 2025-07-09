#ifndef MATRIXOBJECT_H
#define MATRIXOBJECT_H

#include <Python.h>
#include "matrix.h"
#include "utils.h"

void MatrixData_dealloc(MatrixDataObject *self);

int Matrix_init(MatrixObject *self, PyObject *args, PyObject *kwds);

void Matrix_dealloc(MatrixObject *self);

inline static PyObject *create_from_matrix(MatrixObject *self, Py_ssize_t rows, Py_ssize_t cols, Py_ssize_t stride_i, Py_ssize_t stride_j, Py_ssize_t offset)
{

    PyTypeObject *type = Py_TYPE(self);

    MatrixObject *matrix = (MatrixObject *)type->tp_alloc(type, 0);
    if (!matrix)
        return NULL;

    Py_INCREF(self->data_obj);

    instanciate_matrix(matrix, rows, cols, stride_i, stride_j, offset, self->data_obj);

    return (PyObject *)matrix;
}

#endif