#include <python3.10/Python.h>
#include "myfunctions.h"

static PyObject * ASCIIart_hello(PyObject * self, PyObject * args)
{
    printf("Hello");

    return NULL;   //Zwracanie wartości int w formacie Pythonowskim
}
// Funkcja testowa