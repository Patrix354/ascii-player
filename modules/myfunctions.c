#include <python3.10/Python.h>
#include <time.h>
#include "myfunctions.h"

int ** frame;
int lin_num = 0;
int kol_num = 0;
char* color_space = " .,:*-^=+%&$@0#";

double luma_cnt(PyObject * pix) //Obliczanie luminancji na podstawie listy z wartościami [R, G, B]
{
    double coeff[] = {0.2126, 0.7152, 0.0722};
    double luma = 0;
    for(int i = 0; i < 3; i++)
    {
        luma += PyFloat_AsDouble(PyList_GetItem(pix , i)) * coeff[i];
    }
    return luma;
}

PyObject * get_pixel(PyObject * frame, int x, int y)    //Pobieranie z listy pikseli konkretnej wartości
{
    return PyList_GetItem(PyList_GetItem(frame, y), x);
}

PyObject * ASCIIart_load_frame(PyObject * self, PyObject * args)    //Załadowanie listy pikseli do pamięci
{
    PyObject * Pyframe;
    if(!PyArg_ParseTuple(args, "O!", &PyList_Type, &Pyframe))
    {
        return NULL;
    }

    for(int i = 0; i < lin_num; i++)
    {
        for(int j = 0; j < kol_num; j++)
        {
            frame[j][i] = luma_cnt(get_pixel(Pyframe, j, i));
        }
    }
    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_def_frame(PyObject * self, PyObject * args) //Zdefiniowanie rozmiarów klatki
{
    if(!PyArg_ParseTuple(args, "ii", &kol_num, &lin_num))
    {
        return NULL;
    }

    frame = malloc(sizeof(int*) * kol_num);
    for(int i = 0; i < kol_num; i++)
    {
        frame[i] = malloc(sizeof(int) * lin_num);
    }

    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_clean(PyObject * self, PyObject * args)     //Zwolnienie pamięci na przechowywanie klatki
{
    for(int i = 0; i < kol_num; i++)
    {
        free(frame[i]);
    }
    free(frame);
    return Py_BuildValue("i", 1);
}