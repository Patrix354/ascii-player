import moviepy.editor as mp
import numpy as np
import cv2
import sys
import time

import ASCIImodule

#########################
##### Video segment #####
#########################

def Import_Vid(path):   # Zaimportowanie pliku wideo z wykorzystaniem biblioteki OpenCV2
    return cv2.VideoCapture(path)

def Get_framerate_of_clip(clip):
    return clip.get(5)

def Get_number_of_frames_in_clip(clip):
    return clip.get(7)

def Set_current_frame(clip, frame_number):
    clip.set(1, frame_number)        # Ustaw żądaną klatkę

def Read_frame_from_clip(clip):
    return clip.read()[1]  # Odczytaj klatkę 

def Resize_frame(frame, width, height):
    return cv2.resize(frame, (width, height), interpolation=cv2.INTER_AREA)

def extract_frame(clip, frame_number, width, height): # Pobranie klatki z wykorzystaniem biblioteki OpenCV2
    Set_current_frame(clip, frame_number)        # Ustaw żądaną klatkę
    frame = Read_frame_from_clip(clip) # Odczytaj klatkę                       
    frame = Resize_frame(frame, width, height)  #Przeskaluj pobraną klatkę na podane wartości
    return frame.tolist()

def setup(file):
    return Import_Vid(file)                                # Importowanie video

def play(clip, begin_frame, width, height):
    framerate = Get_framerate_of_clip(clip)
    number_of_frames = Get_number_of_frames_in_clip(clip)
    start = time.time()
    while True:                                                                     #To wyrażenie jest po to, aby przy opóźnieniach lub spowolnieniach 
        frame_num = int((time.time() - start) * framerate) + begin_frame        #w przetwarzaniu zachować synchronizację z muzyką
        if frame_num >= number_of_frames:                                     #Warunek sprawdzający czy nie skończył się plik
            break
        f = extract_frame(clip, frame_num, width, height)   

        ASCIImodule.Process_and_print(f)  #Załadowanie klatki do modułu