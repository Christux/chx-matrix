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
