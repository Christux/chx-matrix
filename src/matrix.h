#ifndef MATRIX_H
#define MATRIX_H

#include <Python.h>

typedef struct {
    PyObject_HEAD
    double *data;
    Py_ssize_t size;
} MatrixDataObject;

typedef struct {
    PyObject_HEAD
    Py_ssize_t rows;
    Py_ssize_t cols;
    Py_ssize_t stride_i;
    Py_ssize_t stride_j;
    Py_ssize_t offset;
    MatrixDataObject *data_obj;
} MatrixObject;

typedef struct {
    MatrixObject base;
} RowObject;

typedef struct {
    MatrixObject base;
} ColumnObject;

extern PyTypeObject MatrixType;
extern PyTypeObject MatrixDataType;
extern PyTypeObject RowType;
extern PyTypeObject ColumnType;

#endif // MATRIX_H