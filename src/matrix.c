#include <Python.h>
#include <structmember.h> 
#include "matrix.h"
#include "matrix_row.h"
#include "matrix_column.h"
#include "matrix_data.h"
#include "matrix_object.h"
#include "matrix_methods.h"
#include "utils.h"


extern PyMemberDef MatrixData_members[];

PyTypeObject MatrixDataType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "chx_matrix.MatrixData",
    .tp_basicsize = sizeof(MatrixDataObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "Données matricielles partagées",
    .tp_members = MatrixData_members,
    .tp_new = PyType_GenericNew,
    .tp_dealloc = (destructor)MatrixData_dealloc,
};

extern PyMethodDef Matrix_methods[];
extern PyGetSetDef Matrix_getset[];
extern PyMemberDef Matrix_members[];

static PyMappingMethods Matrix_mappingmethods = {
    .mp_length = NULL,
    .mp_subscript = (binaryfunc)Matrix_subscript,
    .mp_ass_subscript = (objobjargproc)Matrix_ass_subscript,
};

PyTypeObject MatrixType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "chx_matrix.Matrix",
    .tp_doc = "Simple Matrix class",
    .tp_basicsize = sizeof(MatrixObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)Matrix_init,
    .tp_dealloc = (destructor)Matrix_dealloc,
    .tp_methods = Matrix_methods,
    .tp_members = Matrix_members,
    .tp_str = (reprfunc)Matrix_str,
    .tp_repr = (reprfunc)Matrix_str,
    .tp_as_mapping = &Matrix_mappingmethods,
    .tp_getset = Matrix_getset,
};

static PyMappingMethods Row_mapping = {
    .mp_length = NULL,
    .mp_subscript = (binaryfunc)Row_subscript,
    .mp_ass_subscript = (objobjargproc)Row_ass_subscript,
};

PyTypeObject RowType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "chx_matrix.Row",
    .tp_doc = "Simple Row class",
    .tp_basicsize = sizeof(RowObject),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc)Row_init,
    .tp_base = &MatrixType,
    .tp_as_mapping = &Row_mapping,
};

extern PyMethodDef Column_methods[];

static PyMappingMethods Column_mapping = {
    .mp_length = NULL,
    .mp_subscript = (binaryfunc)Column_subscript,
    .mp_ass_subscript = (objobjargproc)Column_ass_subscript,
};

PyTypeObject ColumnType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "chx_matrix.Column",
    .tp_doc = "Simple Column class",
    .tp_basicsize = sizeof(ColumnObject),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_init = (initproc)Column_init,
    .tp_base = &MatrixType,
    .tp_methods = Column_methods,
    .tp_as_mapping = &Column_mapping,
};

static PyModuleDef matrixmodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "chx_matrix",
    .m_doc = "Simple C matrix module",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_chx_matrix(void) {
    PyObject *module;
    if (PyType_Ready(&MatrixType) < 0)
        return NULL;

    module = PyModule_Create(&matrixmodule);
    if (module == NULL)
        return NULL;

    Py_INCREF(&MatrixType);
    if (PyModule_AddObject(module, "Matrix", (PyObject *)&MatrixType) < 0) {
        Py_DECREF(&MatrixType);
        Py_DECREF(module);
        return NULL;
    }

    if (PyType_Ready(&MatrixDataType) < 0)
        return NULL;

    Py_INCREF(&MatrixDataType);
    if (PyModule_AddObject(module, "MatrixData", (PyObject *)&MatrixDataType) < 0) {
        Py_DECREF(&MatrixDataType);
        Py_DECREF(module);
        return NULL;
    }

    if (PyType_Ready(&RowType) < 0)
        return NULL;

    Py_INCREF(&RowType);
    if (PyModule_AddObject(module, "Row", (PyObject *)&RowType)< 0) {
        Py_DECREF(&RowType);
        Py_DECREF(module);
        return NULL;
    }

    if (PyType_Ready(&ColumnType) < 0)
        return NULL;

    Py_INCREF(&ColumnType);
    if (PyModule_AddObject(module, "Column", (PyObject *)&ColumnType)< 0) {
        Py_DECREF(&ColumnType);
        Py_DECREF(module);
        return NULL;
    }

    return module;
}