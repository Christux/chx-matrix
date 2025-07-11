#include <Python.h>
#include "matrix.h"
#include "utils.h"
#include "matrix_object.h"
#include "matrix_methods.h"
#include "matrix_row.h"
#include "matrix_column.h"
#include "matrix_maths.h"


inline static PyObject *get_row(MatrixObject *self, Py_ssize_t row_idx, Py_ssize_t col_start, Py_ssize_t col_end)
{

    if (row_idx < 0 || row_idx >= self->rows || col_start < 0 || col_start >= self->cols || col_end < 0 || col_end >= self->cols || col_start > col_end)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    return create_row_from_matrix(
        self,
        col_end - col_start + 1,
        self->stride_i,
        self->stride_j,
        row_idx * self->stride_i + col_start * self->stride_j + self->offset);
}

inline static PyObject *get_column(MatrixObject *self, Py_ssize_t col_idx, Py_ssize_t row_start, Py_ssize_t row_end)
{

    if (col_idx < 0 || col_idx >= self->cols || row_start < 0 || row_start >= self->rows || row_end < 0 || row_end >= self->rows || row_start > row_end)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return NULL;
    }

    return create_column_from_matrix(
        self,
        row_end - row_start + 1,
        self->stride_i,
        self->stride_j,
        row_start * self->stride_i + col_idx * self->stride_j + self->offset);
}

inline static PyObject *get_sub_matrix(
    MatrixObject *self,
    Py_ssize_t row_start,
    Py_ssize_t row_end,
    Py_ssize_t col_start,
    Py_ssize_t col_end)
{

    if (row_start < 0 || row_start >= self->rows || row_end < 0 || row_end >= self->rows || row_start > row_end || col_start < 0 || col_start >= self->cols || col_end < 0 || col_end >= self->cols || col_start > col_end)
    {

        PyErr_Format(PyExc_IndexError,
                     "Invalid slice indices: row_start=%zd, row_end=%zd, col_start=%zd, col_end=%zd",
                     row_start, row_end, col_start, col_end);

        return NULL;
    }

    if (row_start == row_end && col_start == col_end)
    {
        return get(self, row_start, col_start);
    }

    if (row_start == row_end)
    {
        return get_row(self, row_start, col_start, col_end);
    }

    if (col_start == col_end)
    {
        return get_column(self, col_start, row_start, row_end);
    }

    return create_from_matrix(
        self,
        row_end - row_start + 1,
        col_end - col_start + 1,
        self->stride_i,
        self->stride_j,
        row_start * self->stride_i + col_start * self->stride_j + self->offset);
}

static PyObject *Matrix_get_shape(MatrixObject *self, void *closure)
{
    return Py_BuildValue("(nn)", self->rows, self->cols);
}

PyObject *Matrix_get(MatrixObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"i", "j", NULL};
    Py_ssize_t i, j;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "nn", kwlist, &i, &j))
        return NULL;

    return get(self, i, j);
}

PyObject *Matrix_subscript(MatrixObject *self, PyObject *key)
{

    if (!PyTuple_Check(key) || PyTuple_Size(key) != 2)
    {
        PyErr_SetString(PyExc_TypeError, "Matrix requires two indices: matrix[i, j]");
        return NULL;
    }

    PyObject *row_key = PyTuple_GET_ITEM(key, 0);
    PyObject *col_key = PyTuple_GET_ITEM(key, 1);

    if (PyLong_Check(row_key) && PyLong_Check(col_key))
    {
        Py_ssize_t i = PyLong_AsSsize_t(row_key);
        Py_ssize_t j = PyLong_AsSsize_t(col_key);

        return get(self, i, j);
    }

    if (PyLong_Check(row_key) && PySlice_Check(col_key))
    {
        Py_ssize_t i = PyLong_AsSsize_t(row_key);

        if (i < 0 || i >= self->rows)
        {
            PyErr_SetString(PyExc_IndexError, "Matrix row index out of range");
            return NULL;
        }

        Py_ssize_t c_start, c_stop, c_step;
        if (PySlice_Unpack(col_key, &c_start, &c_stop, &c_step) < 0)
            return NULL;

        PySlice_AdjustIndices(self->cols, &c_start, &c_stop, c_step);
        if (c_step != 1)
        {
            PyErr_SetString(PyExc_NotImplementedError, "Only step=1 is supported");
            return NULL;
        }

        return get_sub_matrix(self, i, i, c_start, c_stop - 1);
    }

    if (PySlice_Check(row_key) && PyLong_Check(col_key))
    {
        Py_ssize_t j = PyLong_AsSsize_t(col_key);
        if (j < 0 || j >= self->cols)
        {
            PyErr_SetString(PyExc_IndexError, "Matrix column index out of range");
            return NULL;
        }

        Py_ssize_t r_start, r_stop, r_step;
        if (PySlice_Unpack(row_key, &r_start, &r_stop, &r_step) < 0)
            return NULL;

        PySlice_AdjustIndices(self->rows, &r_start, &r_stop, r_step);
        if (r_step != 1)
        {
            PyErr_SetString(PyExc_NotImplementedError, "Only step=1 is supported");
            return NULL;
        }

        return get_sub_matrix(self, r_start, r_stop - 1, j, j);
    }

    if (PySlice_Check(row_key) && PySlice_Check(col_key))
    {
        Py_ssize_t r_start, r_stop, r_step;
        Py_ssize_t c_start, c_stop, c_step;

        if (PySlice_Unpack(row_key, &r_start, &r_stop, &r_step) < 0 ||
            PySlice_Unpack(col_key, &c_start, &c_stop, &c_step) < 0)
            return NULL;

        PySlice_AdjustIndices(self->rows, &r_start, &r_stop, r_step);
        PySlice_AdjustIndices(self->cols, &c_start, &c_stop, c_step);

        if (r_step != 1 || c_step != 1)
        {
            PyErr_SetString(PyExc_NotImplementedError, "Only step=1 is supported for now");
            return NULL;
        }

        return get_sub_matrix(self, r_start, r_stop - 1, c_start, c_stop - 1);
    }

    PyErr_SetString(PyExc_TypeError, "Invalid index types: expected integers or slices");
    return NULL;
}

PyObject *Matrix_set(MatrixObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"i", "j", "value", NULL};
    Py_ssize_t i, j;
    double value;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "nnd", kwlist, &i, &j, &value))
        return NULL;

    Py_INCREF(self);
    return set(self, i, j, value);
}

int Matrix_ass_subscript(MatrixObject *self, PyObject *key, PyObject *value_obj)
{
    Py_ssize_t i, j;
    double value;

    if (!PyTuple_Check(key) || PyTuple_Size(key) != 2)
    {
        PyErr_SetString(PyExc_TypeError, "indices must be a tuple of two integers");
        return -1;
    }

    PyObject *i_obj = PyTuple_GetItem(key, 0);
    PyObject *j_obj = PyTuple_GetItem(key, 1);

    i = PyLong_AsSsize_t(i_obj);
    j = PyLong_AsSsize_t(j_obj);

    if (i < 0 || i >= self->rows || j < 0 || j >= self->cols)
    {
        PyErr_SetString(PyExc_IndexError, "index out of range");
        return -1;
    }

    value = PyFloat_AsDouble(value_obj);
    if (PyErr_Occurred())
        return -1;

    set_in_table(self, i, j, value);
    return 0;
}

inline static PyObject *setAll(MatrixObject *self, double value)
{

    for (Py_ssize_t i = 0; i < self->rows; i++)
    {
        for (Py_ssize_t j = 0; j < self->cols; j++)
        {
            set_in_table(self, i, j, value);
        }
    }

    return (PyObject *)self;
}

PyObject *Matrix_setAll(MatrixObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"value", NULL};
    double value;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "d", kwlist, &value))
        return NULL;

    Py_INCREF(self);
    return setAll(self, value);
}

PyObject *Matrix_transpose(MatrixObject *self, PyObject *Py_UNUSED(ignored))
{

    PyTypeObject *self_type = Py_TYPE(self);
    PyTypeObject *type;

    if (self_type == &RowType)
    {
        type = &ColumnType;
    }
    else if (self_type == &ColumnType)
    {
        type = &RowType;
    }
    else
    {
        type = &MatrixType;
    }

    MatrixObject *matrix = (MatrixObject *)type->tp_alloc(type, 0);

    if (!matrix)
        return NULL;

    Py_INCREF(self->data_obj);

    instanciate_matrix(
        matrix,
        self->cols,
        self->rows,
        self->stride_j,
        self->stride_i,
        self->offset,
        self->data_obj);

    return (PyObject *)matrix;
}

PyObject *Matrix_copy(MatrixObject *self, PyObject *Py_UNUSED(ignored))
{

    PyTypeObject *type = Py_TYPE(self);

    MatrixObject *matrix = (MatrixObject *)type->tp_alloc(type, 0);
    if (!matrix)
        return NULL;

    MatrixDataObject *mdata = PyObject_New(MatrixDataObject, &MatrixDataType);
    if (!mdata)
        return NULL;

    mdata->size = self->rows * self->cols;
    mdata->data = calloc(mdata->size, sizeof(double));

    if (!mdata->data)
        return PyErr_NoMemory(), NULL;

    instanciate_matrix(matrix, self->rows, self->cols, self->cols, 1, 0, mdata);

    for (Py_ssize_t i = 0; i < self->rows; i++)
    {
        for (Py_ssize_t j = 0; j < self->cols; j++)
        {
            set_in_table(matrix, i, j, get_from_table(self, i, j));
        }
    }

    return (PyObject *)matrix;
}

PyObject *Matrix_get_sub_matrix(MatrixObject *self, PyObject *args, PyObject *kwds)
{

    static char *kwlist[] = {"row_start", "row_end", "col_start", "col_end", NULL};
    Py_ssize_t row_start, row_end, col_start, col_end;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "nnnn", kwlist, &row_start, &row_end, &col_start, &col_end))
        return NULL;

    return get_sub_matrix(self, row_start, row_end, col_start, col_end);
}

PyObject *Matrix_get_row(MatrixObject *self, PyObject *args, PyObject *kwds)
{

    static char *kwlist[] = {"row", NULL};
    Py_ssize_t row_idx;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &row_idx))
        return NULL;

    return get_row(self, row_idx, 0, self->cols - 1);
}

PyObject *Matrix_get_column(MatrixObject *self, PyObject *args, PyObject *kwds)
{

    static char *kwlist[] = {"col", NULL};
    Py_ssize_t col_idx;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "n", kwlist, &col_idx))
        return NULL;

    return get_column(self, col_idx, 0, self->rows - 1);
}

PyObject *Matrix_str(MatrixObject *self)
{
    PyObject *result = PyUnicode_FromString("[\n");
    for (Py_ssize_t i = 0; i < self->rows; i++)
    {
        PyObject *line = PyUnicode_FromString("  [");
        for (Py_ssize_t j = 0; j < self->cols; j++)
        {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%.2f", get_from_table(self, i, j));
            PyObject *num = PyUnicode_FromString(buffer);
            PyUnicode_Append(&line, num);
            Py_DECREF(num);
            if (j < self->cols - 1)
                PyUnicode_Append(&line, PyUnicode_FromString(", "));
        }
        PyUnicode_Append(&line, PyUnicode_FromString("],\n"));
        PyUnicode_Append(&result, line);
        Py_DECREF(line);
    }
    PyUnicode_Append(&result, PyUnicode_FromString("]"));
    return result;
}

PyMethodDef Matrix_methods[] = {
    {"get", (PyCFunction)Matrix_get, METH_VARARGS | METH_KEYWORDS, "Gets value at (i, j)"},
    {"set", (PyCFunction)Matrix_set, METH_VARARGS | METH_KEYWORDS, "Sets value at (i, j)"},
    {"set_all", (PyCFunction)Matrix_setAll, METH_VARARGS | METH_KEYWORDS, "Sets all values"},
    {"transpose", (PyCFunction)Matrix_transpose, METH_NOARGS, "Gets transposed matrix"},
    {"copy", (PyCFunction)Matrix_copy, METH_NOARGS, "Gets copied matrix"},
    {"get_sub_matrix", (PyCFunction)Matrix_get_sub_matrix, METH_VARARGS | METH_KEYWORDS, "Gets a part of the matrix"},
    {"get_row", (PyCFunction)Matrix_get_row, METH_VARARGS | METH_KEYWORDS, "Gets a row of the matrix"},
    {"get_column", (PyCFunction)Matrix_get_column, METH_VARARGS | METH_KEYWORDS, "Gets a column of the matrix"},
    {"scale", (PyCFunction)Matrix_scale, METH_VARARGS | METH_KEYWORDS, "Scales values of the matrix"},
    {NULL}};

PyGetSetDef Matrix_getset[] = {
    {"shape", (getter)Matrix_get_shape, NULL, "matrix dimensions (rows, cols)", NULL},
    {NULL} /* Sentinel */
};