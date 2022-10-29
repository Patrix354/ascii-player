#include <python3.10/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "myfunctions.h"

uint8_t ** frame;
uint8_t ** scaled_frame;
int lin_num = 0;
int col_num = 0;
int radius = 0;
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

int avg(uint8_t ** f, int beg_x, int end_x, int beg_y, int end_y)   //Uśrednianie danego rejonu tablicy
{
    int n = 0;
    int sum = 0;
    int average = 0;
    for(int i = beg_y; i <= end_y; i++)
    {
        for(int j = beg_x; j <= end_x; j++)
        {
            sum += f[j][i];
            n++;
        }
    }
    average = sum/n;
    return average;
}

PyObject * get_pixel(PyObject * frame, int x, int y)    //Pobieranie z listy pikseli konkretnej wartości
{
    return PyList_GetItem(PyList_GetItem(frame, y), x);
}

PyObject * ASCIIart_load_frame(PyObject * self, PyObject * args)    //Załadowanie listy pikseli do pamięci i liczenie z niego luminancji
{
    PyObject * Pyframe;
    if(!PyArg_ParseTuple(args, "O!", &PyList_Type, &Pyframe))
    {
        return NULL;
    }

    for(int i = 0; i < lin_num; i++)
    {
        for(int j = 0; j < col_num; j++)
        {
            frame[j][i] = luma_cnt(get_pixel(Pyframe, j, i));
        }
    }
    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_def_frame(PyObject * self, PyObject * args) //Inicjalizacja klatki o odpowiednich rozmiarach
{ 
    if(!PyArg_ParseTuple(args, "ii", &col_num, &lin_num))
    {
        return NULL;
    }

    frame = malloc(sizeof(uint8_t*) * col_num);
    for(int i = 0; i < col_num; i++)
    {
        frame[i] = malloc(sizeof(uint8_t) * lin_num);
    }
    
    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_clean(PyObject * self, PyObject * args)     //Zwolnienie pamięci na przechowywanie klatki (normalnej i przeskalowanej)
{
    int scaled_lines = lin_num / radius;
    int scaled_columns = col_num / radius;

    for(int i = 0; i < col_num; i++)
    {
        free(frame[i]);
    }
    free(frame);

    for(int i = 0; i < scaled_columns; i++)
    {
        free(scaled_frame[i]);
    }
    free(scaled_frame);

    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_def_scaled_frame(PyObject * self, PyObject * args)    //Tworzenie przesklowanej klatki
{
    if(!PyArg_ParseTuple(args, "i", &radius))
    {
        return NULL;
    }    

    int scaled_lines = lin_num / radius;
    int scaled_columns = col_num / radius;
    scaled_frame = malloc(sizeof(uint8_t*) * scaled_columns);
    for(int i = 0; i < scaled_columns; i++)
    {
        scaled_frame[i] = malloc(sizeof(uint8_t) * scaled_lines);
    }


    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_scale_frame(PyObject * self, PyObject * args)   //Skalowanie załadowanej klatki
{
    int scaled_lines = lin_num / radius;
    int scaled_columns = col_num / radius;
    for(int i = 0; i+radius-1 < lin_num; i+= radius)
    {
        for(int j = 0; j+radius-1 < col_num; j+= radius)
        {
            scaled_frame[j/radius][i/radius] = avg(frame, j, j+radius-1, i, i+radius-1);
        }
    }

    for(int i = 0; i < scaled_lines; i++)
    {
        for(int j = 0; j < scaled_columns; j++)
        {
            printf("%d, ", scaled_frame[j][i]);
        }
        printf("\n");
    }
    return Py_BuildValue("i", 1);
}