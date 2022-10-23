import moviepy.editor as mp
import numpy as np

#########################
##### Video segment #####
#########################

def Import_Vid(path):   # Zaimportowanie pliku wideo
    global film
    film = mp.VideoFileClip(path)

def Extract_frame(num): # Pobranie klatki
    global film
    frame = film.get_frame(num).tolist()
    return frame
