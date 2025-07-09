#include <Python.h>
#include <structmember.h>
#include "matrix.h"
#include "matrix_data.h"

void MatrixData_dealloc(MatrixDataObject *self)
{
    if (self->data)
        free(self->data);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

PyMemberDef MatrixData_members[] = {
    {"pointer", T_ULONGLONG, offsetof(MatrixDataObject, data), READONLY, "Row pointer"},
    {"size", T_LONG, offsetof(MatrixDataObject, size), READONLY, "Size in elements"},
    {NULL}};