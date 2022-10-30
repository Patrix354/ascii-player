import moviepy.editor as mp
import numpy as np
import cv2
import sys
import time

#########################
##### Video segment #####
#########################

def Import_Module():        # Ta funkcja jest potrzebna tylko podczas użytkowania ziezainstalowanego modułu
    sys.path.append("build/lib.linux-x86_64-cpython-310/") 

def Import_Vid(path):   # Zaimportowanie pliku wideo z wykorzystaniem biblioteki OpenCV2
    global film
    film = cv2.VideoCapture(path)

def Extract_frame(num): # Pobranie klatki z wykorzystaniem biblioteki OpenCV2
    global film
    film.set(1, num)
    ret, frame = film.read()
    return frame.tolist()

def Vid_module_init(file):
    Import_Module()
    import ASCIIart

    Import_Vid(file)  # Importowanie video
    f = Extract_frame(0) #Pobranie pierwszej klatki aby sprawdzić wymiary potrzene zo zalokowania pamieci
    return len(f[0]), len(f) #(szerokość, wysokość)

def play(beg):
    Import_Module()
    import ASCIIart

    start = time.time()
    for i in range(1000):
        frame_num = int((time.time() - start) * 30) + beg     #Program niestety nie dziła płynnie z prędością 30 fps. 
        f = Extract_frame(frame_num)           #Dlatego pobierane są obrazy z taką gęstością żeby nie następowała latencja między audio i video

        ASCIIart.load_frame(f)  #Załadowanie klatki do modułu
        ASCIIart.print()    #Wypisanie klatki