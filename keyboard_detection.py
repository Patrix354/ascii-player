import os
import sys
import termios
import atexit
from select import select
 

def set_console_attributes():
    file_descriptor = sys.stdin.fileno()
    new_atributtes = termios.tcgetattr(file_descriptor)
    old_atributtes = termios.tcgetattr(file_descriptor)

    new_atributtes[3] = (new_atributtes[3] & ~termios.ICANON & ~termios.ECHO)
    termios.tcsetattr(file_descriptor, termios.TCSAFLUSH, new_atributtes)
    atexit.register(restore_console_atributes, file_descriptor, old_atributtes)


def getch():
    return sys.stdin.read(1)

def read_keyboard_events():
    '''
    This function checks if something appears on sys.stdin, if not it returns False
    '''
    dr,dw,de = select([sys.stdin], [], [], 0)
    return dr != []

def is_pressed(key):
    if read_keyboard_events():
        c = getch()
        if ord(c) == key:
            return True
        else:
            return False

def restore_console_atributes(file_descriptor, old_atributtes):
    termios.tcsetattr(file_descriptor, termios.TCSAFLUSH, old_atributtes)

        