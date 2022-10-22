#include <python3.10/Python.h>

static PyObject * ASCIIartError;

/*static PyObject * spam_NazwaFunkcji(PyObject * self, PyObject * args)
{
    char* msg;
    if (!PyArg_ParseTuple(args, "s", &msg)) // Parsowanie argumentów, np. string pod wskaźnik msg
    {
        return NULL;
    }

    return Py_BuildValue("i", 1);   //Zwracanie wartości int w formacie Pythonowskim
}*/
// Funkcja testowa

////////////////////////////////////////////////////////////////////////////////////////
////////////////// Niżej nie warto zaglądać ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

static PyMethodDef ASCIIart_methods[] = {
//    {"NazwaFunkcji", spam_witaj, METH_VARARGS, "Funkcaj Testowa"},
    {NULL,NULL, 0,NULL}
};

static struct PyModuleDef ASCIIartmodule = {
    PyModuleDef_HEAD_INIT,
    "ASCIIart",   /* name of module */
    NULL, /* module documentation, may be NULL */
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

