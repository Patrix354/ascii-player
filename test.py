import os
import sys
import termios
from select import select
import atexit
 

def set_console_attributes():
    fd = sys.stdin.fileno()
    new_term = termios.tcgetattr(fd)
    old_term = termios.tcgetattr(fd)

    # New terminal setting unbuffered
    new_term[3] = (new_term[3] & ~termios.ICANON & ~termios.ECHO)
    termios.tcsetattr(fd, termios.TCSAFLUSH, new_term)
    atexit.register(restore_console_atributes, fd, old_term)


def getch():
    return sys.stdin.read(1)

def read_keyboard_events():
    dr,dw,de = select([sys.stdin], [], [], 0)
    return dr != []

def is_pressed():
    if read_keyboard_events():
        c = getch()
        return ord(c)

def restore_console_atributes(fd, old_term):
    termios.tcsetattr(fd, termios.TCSAFLUSH, old_term)

# Test    
if __name__ == "__main__":
    set_console_attributes()
    print('Hit any key, or ESC to exit')
    while True:
        key = is_pressed()
        if key != None:
            print(key)

        