#include <python3.10/Python.h>
#include "myfunctions.h"

static PyObject * ASCIIartError;

////////////////////////////////////////////////////////////////////////////////////////
////////////////// Niżej nie warto zaglądać, nie ma tam nic ciekawego //////////////////
////////////////////////////////////////////////////////////////////////////////////////

static PyMethodDef ASCIIart_methods[] = {
    {"load_frame", ASCIIart_load_frame, METH_VARARGS, "Załadowanie klatki"},
    {"def_frame", ASCIIart_def_frame, METH_VARARGS, "Zdefiniowanie wielkości klatki"},
    {"clean", ASCIIart_clean, METH_NOARGS, "Zwalnianie pamięci po zakończonym działaniu"},
    {"def_scaled_frame", ASCIIart_def_scaled_frame, METH_VARARGS, "Zdefiniowanie przeskalowanej klatki"},
    {"print", ASCIIart_print_frame, METH_NOARGS, "Wypisanie aktualnie przechowywanej klatki w postaci ASCII art"},
    {NULL,NULL, 0,NULL}
};

static struct PyModuleDef ASCIIartmodule = {
    PyModuleDef_HEAD_INIT,
    "ASCIIart",   /* name of module */
    NULL, /* module documentation */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    ASCIIart_methods
};

PyMODINIT_FUNC PyInit_ASCIIart(void)
{
    PyObject *m;

    m = PyModule_Create(&ASCIIartmodule);
    if (m == NULL)
        return NULL;

    ASCIIartError = PyErr_NewException("ASCIIart.error", NULL, NULL);
    Py_XINCREF(ASCIIartError);
    if (PyModule_AddObject(m, "error", ASCIIartError) < 0) {
        Py_XDECREF(ASCIIartError);
        Py_CLEAR(ASCIIartError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

