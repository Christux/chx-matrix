#include <Python.h>
#include <structmember.h> 
#include "matrix.h"
#include "matrix_object.h"


int Matrix_init(MatrixObject *self, PyObject *args, PyObject *kwds) {
    static char *kwlist[] = {"rows", "cols", NULL};
    Py_ssize_t rows, cols;
    
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "nn", kwlist, &rows, &cols))
        return -1;

    MatrixDataObject *mdata = PyObject_New(MatrixDataObject, &MatrixDataType);
    if (!mdata)
        return -1;

    mdata->size = rows * cols;
    mdata->data = calloc(mdata->size, sizeof(double));
    
    if (!mdata->data)
        return PyErr_NoMemory(), -1;

    return instanciate_matrix(
        self,
        rows,
        cols,
        cols,
        1,
        0,
        mdata
    );
}

void Matrix_dealloc(MatrixObject *self) {
    Py_XDECREF(self->data_obj);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

PyMemberDef Matrix_members[] = {
    {"rows", T_PYSSIZET, offsetof(MatrixObject, rows), READONLY, "nombre de lignes"},
    {"cols", T_PYSSIZET, offsetof(MatrixObject, cols), READONLY, "nombre de colonnes"},
    {NULL}
};
