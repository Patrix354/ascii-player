import moviepy.editor as mp
import numpy as np
import cv2

#########################
##### Video segment #####
#########################

def Import_Vid(path):   # Zaimportowanie pliku wideo z wykorzystaniem biblioteki MoviePy
    global film
    film = mp.VideoFileClip(path)

def Extract_frame(num): # Pobranie klatki z wykorzystaniem biblioteki MoviePy
    global film
    frame = film.get_frame(num).tolist()
    return frame
