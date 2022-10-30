#include <python3.10/Python.h>
#include "modulefunctions.h"

static uint8_t ** frame;
static uint8_t ** scaled_frame;
static int lines = 0, columns = 0, radius = 0;
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

static int avg(uint8_t ** f, int beg_x, int end_x, int beg_y, int end_y)   //Uśrednianie danego rejonu tablicy
{
    int n = 0;
    int sum = 0;
    int average = 0;
    for(int i = beg_y; i <= end_y; i++)     //Średnia arytmetyczna w regionie podanym w argumencie
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

static void def_scaled_frame()    //Tworzenie przesklowanej klatki
{
    int scaled_lines = lines / radius;    //Wymiary skalowanej klatki
    int scaled_columns = columns / radius;

    scaled_frame = malloc(sizeof(uint8_t*) * scaled_columns);   //Alokowanie pamięci na przeskalowaną klatkę
    for(int i = 0; i < scaled_columns; i++)
    {
        scaled_frame[i] = malloc(sizeof(uint8_t) * scaled_lines);
    }
}

static void scale_frame()   //Skalowanie załadowanej klatki
{
    for(int i = 0; i+radius-1 < lines; i+= radius)    //Uśrednianie danego regionu pixeli
    {
        for(int j = 0; j+radius-1 < columns; j+= radius)
        {
            scaled_frame[j/radius][i/radius] = avg(frame, j, j+radius-1, i, i+radius-1);
        }
    }
}

static void map_pixels()    //Przeliczanie wartości luminancji na index w tablicy ze zdefiniowanymi znakami
{
    int scaled_lines = lines / radius;    //Wymiary skalowanej klatki
    int scaled_columns = columns / radius;
    
    for(int i = 0; i < scaled_lines; i++)   
    {
        for(int j = 0; j < scaled_columns; j++)
        {
            scaled_frame[j][i] = map(scaled_frame[j][i], 0, 255, 0, strlen(color_space)-1);
        }
    }
}

static void print()     //Wypisanie tablicy
{
    int scaled_lines = lines / radius;    //Wymiary skalowanej klatki
    int scaled_columns = columns / radius;

    system("clear");
    for(int i = 0; i < scaled_lines; i++)
    {
        for(int j = 0; j < scaled_columns; j++)
        {
            printf("%c", color_space[scaled_frame[j][i]]);
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
    int scaled_columns = columns / radius; //Wymiar skalowanej klatki, potrzebny jest tylko jeden 

    for(int i = 0; i < columns; i++)    //Zwalnianie pamięci
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

PyObject * ASCIIart_print_frame(PyObject * self, PyObject * args)   //Wypisanie obrazu.
{                                                                   
    scale_frame();
    map_pixels();
    print();
    return Py_BuildValue("i", 1);
}

PyObject * ASCIIart_init(PyObject * self, PyObject * args)  //Inicjalizacja modułu
{
    int width, height, scale;
    if(!PyArg_ParseTuple(args, "iii", &width, &height, &scale))
    {
        return NULL;
    }

    columns = width;
    lines = height;
    radius = scale;

    def_frame();
    def_scaled_frame();

    return Py_BuildValue("i", 1);
} 