import moviepy.editor as mp
import numpy as np
import cv2
import sys
import time

#########################
##### Video segment #####
#########################

metadata = {}

def add_module_path():        # Ta funkcja jest potrzebna tylko podczas użytkowania ziezainstalowanego modułu
    sys.path.append("build/lib.linux-x86_64-cpython-310/") 

def import_Vid(path):   # Zaimportowanie pliku wideo z wykorzystaniem biblioteki OpenCV2
    global film
    film = cv2.VideoCapture(path)

def extract_frame(num): # Pobranie klatki z wykorzystaniem biblioteki OpenCV2
    global film, metadata
    film.set(1, num)        # Ustaw klatkę w żądanym miejscu
    frame = film.read()[1]  # Odczytaj klatkę                       
    frame = cv2.resize(frame, (metadata["width"], metadata["height"]))  #Przeskaluj pobraną klatkę na podane wartości
    return frame.tolist()

def module_init(file, w = 90, h = 60):
    global film, metadata
    import_Vid(file)                                # Importowanie video
    metadata["width"], metadata["height"] = w, h
    read_metadata()

def read_metadata():
    global film, metadata
    metadata["frames_cnt"] = film.get(7)
    metadata["framerate"] = film.get(5)

def play(beg):
    global metadata
    add_module_path()
    import ASCIIart

    start = time.time()
    while True:                                                                     #To wyrażenie jest po to, aby przy opóźnieniach lub spowolnieniach 
        frame_num = int((time.time() - start) * metadata["framerate"]) + beg        #w przetwarzaniu zachować synchronizację z muzyką
        if frame_num >= metadata["frames_cnt"]:                                     #Warunek sorawdzający czy nie skończył się plik
            break
        f = extract_frame(frame_num)   

        ASCIIart.load_frame(f)  #Załadowanie klatki do modułu
        ASCIIart.print()    #Wypisanie klatki
