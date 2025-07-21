#ifndef MATRIXMETHODS_H
#define MATRIXMETHODS_H

#include <Python.h>
#include "matrix.h"

PyObject *Matrix_subscript(MatrixObject *self, PyObject *key);
int Matrix_ass_subscript(MatrixObject *self, PyObject *key, PyObject *value_obj);
PyObject *Matrix_str(MatrixObject *self);

#endif