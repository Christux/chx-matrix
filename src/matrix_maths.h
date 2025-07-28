#ifndef MATRIXMATHS_H
#define MATRIXMATHS_H

#include <Python.h>
#include "matrix.h"

PyObject *Matrix_scale(MatrixObject *self, PyObject *args, PyObject *kwds);
PyObject *Matrix_add(MatrixObject *self, PyObject *args, PyObject *kwds);
PyObject *Matrix_substract(MatrixObject *self, PyObject *args, PyObject *kwds);
PyObject *Matrix_multiply(MatrixObject *self, PyObject *args, PyObject *kwds);

#endif