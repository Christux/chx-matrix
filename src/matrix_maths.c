#include <Python.h>
#include "matrix.h"
#include "matrix_maths.h"
#include "utils.h"


PyObject *Matrix_scale(MatrixObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"factor", NULL};
    double value;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "d", kwlist, &value))
        return NULL;

    for (Py_ssize_t i = 0; i < self->rows; i++)
    {
        for (Py_ssize_t j = 0; j < self->cols; j++)
        {
            set_in_table(self, i, j, get_from_table(self, i, j) * value);
        }
    }

    Py_INCREF(self);
    return (PyObject *)self;    
}

PyObject *Matrix_add(MatrixObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"other", NULL};
    PyObject *other = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist, &other))
        return NULL;

    if (!PyObject_TypeCheck(other, &MatrixType) && !PyObject_TypeCheck(other, &RowType) && !PyObject_TypeCheck(other, &ColumnType)) {
        PyErr_SetString(PyExc_TypeError, "Expected a Matrix or Row or Column as 'other'");
        return NULL;
    }

    MatrixObject *other_matrix = (MatrixObject *)other;

    if (self->rows != other_matrix->rows || self->cols != other_matrix->cols) {
        PyErr_SetString(PyExc_ValueError, "Matrix dimensions must match for addition");
        return NULL;
    }

    for (Py_ssize_t i = 0; i < self->rows; i++) {
        for (Py_ssize_t j = 0; j < self->cols; j++) {
            set_in_table(self, i, j, get_from_table(self, i, j) + get_from_table(other_matrix, i, j));
        }
    }

    Py_INCREF(self);
    return (PyObject *)self;
}

PyObject *Matrix_substract(MatrixObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"other", NULL};
    PyObject *other = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist, &other))
        return NULL;

    if (!PyObject_TypeCheck(other, &MatrixType) && !PyObject_TypeCheck(other, &RowType) && !PyObject_TypeCheck(other, &ColumnType)) {
        PyErr_SetString(PyExc_TypeError, "Expected a Matrix or Row or Column as 'other'");
        return NULL;
    }

    MatrixObject *other_matrix = (MatrixObject *)other;

    if (self->rows != other_matrix->rows || self->cols != other_matrix->cols) {
        PyErr_SetString(PyExc_ValueError, "Matrix dimensions must match for substraction");
        return NULL;
    }

    for (Py_ssize_t i = 0; i < self->rows; i++) {
        for (Py_ssize_t j = 0; j < self->cols; j++) {
            set_in_table(self, i, j, get_from_table(self, i, j) - get_from_table(other_matrix, i, j));
        }
    }

    Py_INCREF(self);
    return (PyObject *)self;
}

PyObject *Matrix_multiply(MatrixObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"left", "right", NULL};
    PyObject *left_obj = NULL;
    PyObject *right_obj = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO", kwlist, &left_obj, &right_obj))
        return NULL;

    if (!(PyObject_TypeCheck(left_obj, &MatrixType) && PyObject_TypeCheck(right_obj, &MatrixType)) &&
        !(PyObject_TypeCheck(left_obj, &RowType) && PyObject_TypeCheck(right_obj, &RowType)) &
        !(PyObject_TypeCheck(left_obj, &ColumnType) && PyObject_TypeCheck(right_obj, &ColumnType))) {
        PyErr_SetString(PyExc_TypeError, "Arguments 'left' and 'right' must be Matrix or Row or Column");
        return NULL;
    }

    MatrixObject *left = (MatrixObject *)left_obj;
    MatrixObject *right = (MatrixObject *)right_obj;

    if (left->cols != right->rows) {
        PyErr_SetString(PyExc_ValueError, "Incompatible matrix dimensions for multiplication");
        return NULL;
    }

    if (self->rows != left->rows || self->cols != right->cols) {
        PyErr_SetString(PyExc_ValueError, "Result matrix dimensions do not match multiplication output");
        return NULL;
    }

    for (Py_ssize_t i = 0; i < left->rows; i++) {
        for (Py_ssize_t j = 0; j < right->cols; j++) {
            double sum = .0;
            for (Py_ssize_t k = 0; k < left->cols; k++) {
                double a = get_from_table(left, i, k);
                double b = get_from_table(right, k, j);
                sum += a * b;
            }
            set_in_table(self, i, j, sum);
        }
    }

    Py_INCREF(self);
    return (PyObject *)self;
}