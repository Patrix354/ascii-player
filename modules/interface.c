#include <python3.10/Python.h>
#include "interface.h"

static PyObject * ASCIImoduleError;

static int get_height_of_frame(void* frame)
{
	int length = ((PyListObject*)frame)->allocated;
	return length;
}

static int get_width_of_frame(void* frame)
{
	void* first_line = *((PyListObject*)frame)->ob_item;
	int length = ((PyListObject*)first_line)->allocated;
	return length;
} 

static int* alocate_memory_for_converted_frame(int frame_width, int frame_height)
{
	int* c_frame = malloc(frame_width * frame_height * sizeof(int));
	return c_frame;
}

int* convert_python_frame_into_C_table(void* frame)
{
	int frame_width = get_width_of_frame(frame);
	int frame_height = get_height_of_frame(frame);
	int index_offset = 0;

	static int* converted_frame = NULL;
	static void* selected_line = NULL;
	static void* selected_pixel = NULL;

	if (converted_frame == NULL)	converted_frame = alocate_memory_for_converted_frame(frame_width, frame_height);
	
	for (int i = 0; i < frame_height; i++)
	{
		selected_line = ((PyListObject*) frame)->ob_item[i];
		for (int j = 0; j < frame_width; j++)
		{
			selected_pixel = ((PyListObject*) selected_line)->ob_item[j];
			index_offset = i * frame_width + j;
			converted_frame[index_offset] = *( ((PyLongObject*) selected_pixel)->ob_digit);
		}
	}
		
	return converted_frame;
}

PyObject* ASCIImodule_Process_and_print(PyObject* dummy_arg, PyObject* valid_args)
{
	void* input_frame = ((PyTupleObject*)valid_args)->ob_item[0];
	//////
	int frame_width = get_width_of_frame(input_frame);
	int frame_height = get_height_of_frame(input_frame);
	//////
	char* character_space = " .,`:*-^=+%&$@0#";
	//////
	static int* frame_in_C_format = NULL;
	static char* frame_ready_to_display = NULL;
	//////////////////////////////////////
	// printf("ty!\n");
	frame_in_C_format = convert_python_frame_into_C_table(input_frame);
	frame_ready_to_display = process_frame(frame_in_C_format, frame_width, frame_height, character_space);
    display_frame(frame_ready_to_display);

	return Py_BuildValue("i", 0);
}



////////////////////////////////////////////////////////////////////////////////////////
////////////////// Niżej nie warto zaglądać, nie ma tam nic ciekawego //////////////////
////////////////////////////////////////////////////////////////////////////////////////

static PyMethodDef ASCIImodule_methods[] = {
    {"Process_and_print", ASCIImodule_Process_and_print, METH_VARARGS, "Przetwarzanie i wypisanie klatki" },
    {NULL,NULL, 0,NULL}
};

static PyModuleDef ASCIImodule_module = {
	PyModuleDef_HEAD_INIT,
	"ASCIImodule",                        // Module name to use with Python import statements
	"Module for displaying videos in console",  // Module description
	0,
	ASCIImodule_methods                   // Structure that defines the methods of the module
};


PyMODINIT_FUNC PyInit_ASCIImodule(void)
{
    PyObject *m;

    m = PyModule_Create(&ASCIImodule_module);
    if (m == NULL)
        return NULL;

    ASCIImoduleError = PyErr_NewException("ASCIImodule.error", NULL, NULL);
    Py_XINCREF(ASCIImoduleError);
    if (PyModule_AddObject(m, "error", ASCIImoduleError) < 0) {
        Py_XDECREF(ASCIImoduleError);
        Py_CLEAR(ASCIImoduleError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

