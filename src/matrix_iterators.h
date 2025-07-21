#ifndef MATRIXITERATORS_H
#define MATRIXITERATORS_H

#include <Python.h>
#include "matrix.h"

typedef struct {
    PyObject_HEAD
    MatrixObject *matrix;
    Py_ssize_t index;
} MatrixRowIter;

typedef struct {
    PyObject_HEAD
    MatrixObject *matrix;
    Py_ssize_t index;
} MatrixColumnIter;

PyObject *Matrix_iter_rows(MatrixObject *self, PyObject *Py_UNUSED(ignored));
PyObject *Matrix_iter_columns(MatrixObject *self, PyObject *Py_UNUSED(ignored));

#endif
