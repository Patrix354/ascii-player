#include <python3.10/Python.h>
#include "myfunctions.h"

uint8_t ** frame;
uint8_t ** scaled_frame;
int lin_num = 0, col_num = 0, radius = 0;
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

uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max)    //Mapowanie wartości pixela na indeks żądanego znaku w tablicy
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

PyObject * get_pixel(PyObject * frame, int x, int y)    //Pobieranie z listy pikseli konkretnej wartości
{
    return PyList_GetItem(PyList_GetItem(frame, y), x);
}

PyObject * ASCIIart_load_frame(PyObject * self, PyObject * args)    //Załadowanie listy pikseli do pamięci i liczenie z niego luminancji
{
    PyObject * Pyframe;     //Klatka w postaci pythonowej listy
    if(!PyArg_ParseTuple(args, "O!", &PyList_Type, &Pyframe))
    {
        return NULL;
    }

    for(int i = 0; i < lin_num; i++)    //Konwertowanie listy pythonowej na tablicę w C
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
    if(!PyArg_ParseTuple(args, "ii", &col_num, &lin_num))   //Dopasowywanie argumentów
    {
        return NULL;
    }

    frame = malloc(sizeof(uint8_t*) * col_num);     //Alokowanie pamięci na klatkę
    for(int i = 0; i < col_num; i++)
    {
        frame[i] = malloc(sizeof(uint8_t) * lin_num);
    }
    
    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_clean(PyObject * self, PyObject * args)     //Zwolnienie pamięci na przechowywanie klatki (normalnej i przeskalowanej)
{
    int scaled_lines = lin_num / radius;    //Wymiary skalowanej klatki
    int scaled_columns = col_num / radius;

    for(int i = 0; i < col_num; i++)    //Zwalnianie pamięci
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
    if(!PyArg_ParseTuple(args, "i", &radius))   //Dopasowywanie argumentów
    {
        return NULL;
    }    
    int scaled_lines = lin_num / radius;    //Wymiary skalowanej klatki
    int scaled_columns = col_num / radius;

    scaled_frame = malloc(sizeof(uint8_t*) * scaled_columns);   //Alokowanie pamięci na przeskalowaną klatkę
    for(int i = 0; i < scaled_columns; i++)
    {
        scaled_frame[i] = malloc(sizeof(uint8_t) * scaled_lines);
    }


    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_scale_frame(PyObject * self, PyObject * args)   //Skalowanie załadowanej klatki
{
    int scaled_lines = lin_num / radius;    //Wymiary skalowanej klatki
    int scaled_columns = col_num / radius;

    for(int i = 0; i+radius-1 < lin_num; i+= radius)    //Uśrednianie danego regionu pixeli
    {
        for(int j = 0; j+radius-1 < col_num; j+= radius)
        {
            scaled_frame[j/radius][i/radius] = avg(frame, j, j+radius-1, i, i+radius-1);
        }
    }

    for(int i = 0; i < scaled_lines; i++)   //Wypisywanie przeskalowanej klatki (w celach testowych)
    {
        for(int j = 0; j < scaled_columns; j++)
        {
            printf("%d, ", scaled_frame[j][i]);
        }
        printf("\n");
    }
    return Py_BuildValue("i", 1);
}