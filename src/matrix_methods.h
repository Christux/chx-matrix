#ifndef MATRIXMETHODS_H
#define MATRIXMETHODS_H

#include <Python.h>
#include "matrix.h"

PyObject *Matrix_get(MatrixObject *self, PyObject *args, PyObject *kwds);
PyObject *Matrix_subscript(MatrixObject *self, PyObject *key);
PyObject *Matrix_set(MatrixObject *self, PyObject *args, PyObject *kwds);
int Matrix_ass_subscript(MatrixObject *self, PyObject *key, PyObject *value_obj);
PyObject *Matrix_setAll(MatrixObject *self, PyObject *args, PyObject *kwds);
PyObject *Matrix_transpose(MatrixObject *self, PyObject *Py_UNUSED(ignored));
PyObject *Matrix_copy(MatrixObject *self, PyObject *Py_UNUSED(ignored));
PyObject *Matrix_get_sub_matrix(MatrixObject *self, PyObject *args, PyObject *kwds);
PyObject *Matrix_str(MatrixObject *self);

#endif