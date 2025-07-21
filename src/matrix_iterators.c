#include <Python.h>
#include "matrix.h"
#include "matrix_iterators.h"
#include "matrix_row.h"
#include "matrix_column.h"


static PyObject *MatrixRowIter_iter(PyObject *self) {
    Py_INCREF(self);
    return self;
}

static PyObject *MatrixRowIter_next(PyObject *self) {
    MatrixRowIter *iter = (MatrixRowIter *)self;
    MatrixObject *m = iter->matrix;

    if (iter->index >= m->rows)
        return NULL;

    Py_ssize_t i = iter->index++;
    return create_row_from_matrix(m, m->cols, m->stride_i, m->stride_j, i * m->stride_i + m->offset);
}

static PyTypeObject MatrixRowIterType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "matrix.MatrixRowIter",
    .tp_basicsize = sizeof(MatrixRowIter),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Row iterator over Matrix",
    .tp_iter = MatrixRowIter_iter,
    .tp_iternext = MatrixRowIter_next,
    .tp_dealloc = (destructor)PyObject_Del,
};

PyObject *Matrix_iter_rows(MatrixObject *self, PyObject *Py_UNUSED(ignored)) {
    MatrixRowIter *it = PyObject_New(MatrixRowIter, &MatrixRowIterType);
    if (!it)
        return NULL;

    Py_INCREF(self);
    it->matrix = self;
    it->index = 0;

    return (PyObject *)it;
}

static PyObject *MatrixColumnIter_iter(PyObject *self) {
    Py_INCREF(self);
    return self;
}

static PyObject *MatrixColumnIter_next(PyObject *self) {
    MatrixColumnIter *iter = (MatrixColumnIter *)self;
    MatrixObject *m = iter->matrix;

    if (iter->index >= m->cols)
        return NULL;

    Py_ssize_t j = iter->index++;
    return create_column_from_matrix(m, m->rows, m->stride_i, m->stride_j, j * m->stride_j + m->offset);
}

static PyTypeObject MatrixColumnIterType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "matrix.MatrixColumnIter",
    .tp_basicsize = sizeof(MatrixColumnIter),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Column iterator over Matrix",
    .tp_iter = MatrixColumnIter_iter,
    .tp_iternext = MatrixColumnIter_next,
    .tp_dealloc = (destructor)PyObject_Del,
};

PyObject *Matrix_iter_columns(MatrixObject *self, PyObject *Py_UNUSED(ignored)) {
    MatrixColumnIter *it = PyObject_New(MatrixColumnIter, &MatrixColumnIterType);
    if (!it)
        return NULL;

    Py_INCREF(self);
    it->matrix = self;
    it->index = 0;

    return (PyObject *)it;
}
