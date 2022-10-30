#include <python3.10/Python.h>
#include "modulefunctions.h"

static uint8_t ** frame;
static int lines = 0, columns = 0;
static char* color_space = " .,`:*-^=+%&$@0#";

static double luma_cnt(PyObject * pix) //Obliczanie luminancji na podstawie listy z wartościami [R, G, B]
{
    double coeff[] = {0.2126, 0.7152, 0.0722};
    double luma = 0;
    for(int i = 0; i < 3; i++)
    {
        luma += PyFloat_AsDouble(PyList_GetItem(pix , i)) * coeff[i];
    }
    return luma;
}

static uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max)    //Mapowanie wartości pixela na indeks żądanego znaku w tablicy
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static void def_frame() //Inicjalizacja klatki o odpowiednich rozmiarach
{ 
    frame = malloc(sizeof(uint8_t*) * columns);     //Alokowanie pamięci na klatkę
    for(int i = 0; i < columns; i++)
    {
        frame[i] = malloc(sizeof(uint8_t) * lines);
    }
}

static void map_pixels()    //Przeliczanie wartości luminancji na index w tablicy ze zdefiniowanymi znakami
{   
    for(int i = 0; i < lines; i++)   
    {
        for(int j = 0; j < columns; j++)
        {
            frame[j][i] = map(frame[j][i], 0, 255, 0, strlen(color_space)-1);
        }
    }
}

static void print()     //Wypisanie tablicy
{
    system("clear");
    for(int i = 0; i < lines; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            printf("%c", color_space[frame[j][i]]);
        }
        printf("\n");
    }
}

static PyObject * get_pixel(PyObject * frame, int x, int y)    //Pobieranie z listy pikseli konkretnej wartości
{
    return PyList_GetItem(PyList_GetItem(frame, y), x);
}

//////////////////////////////////////////////
///// Funkcje widoczne z poziomu pythona /////
//////////////////////////////////////////////

PyObject * ASCIIart_load_frame(PyObject * self, PyObject * args)    //Załadowanie listy pikseli do pamięci i liczenie z niego luminancji
{
    PyObject * Pyframe;     //Klatka w postaci pythonowej listy
    if(!PyArg_ParseTuple(args, "O!", &PyList_Type, &Pyframe))
    {
        return NULL;
    }

    for(int i = 0; i < lines; i++)    //Konwertowanie listy pythonowej na tablicę w C
    {
        for(int j = 0; j < columns; j++)
        {
            frame[j][i] = luma_cnt(get_pixel(Pyframe, j, i));
        }
    }

    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_clean(PyObject * self, PyObject * args)     //Zwolnienie pamięci na przechowywanie klatki (normalnej i przeskalowanej)
{
    for(int i = 0; i < columns; i++)    //Zwalnianie pamięci
    {
        free(frame[i]);
    }
    free(frame);

    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_print_frame(PyObject * self, PyObject * args)   //Wypisanie obrazu.
{                                                                   
    map_pixels();
    print();
    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_init(PyObject * self, PyObject * args)  //Inicjalizacja modułu
{
    int width, height;
    if(!PyArg_ParseTuple(args, "ii", &width, &height))
    {
        return NULL;
    }

    columns = width;
    lines = height;

    def_frame();

    return Py_BuildValue("i", 1);
} 