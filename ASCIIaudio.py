import pygame 
import time
import moviepy.editor as mp

#########################
##### Audio segment #####
#########################

def soundtrack_extract(path):   # Pobranie ścieżki dźwiękowej z pliku
    clip = mp.VideoFileClip(path)
    clip.audio.write_audiofile("media_files/soundtrack.mp3")

def soundmodule_init(file): # Załadowanie pobranej ścieżki dźwiękowej
    soundtrack_extract(file)
    
    pygame.mixer.pre_init()
    pygame.mixer.init()
    pygame.mixer.music.load("media_files/soundtrack.mp3")

def play():   # funkcja do przetestowania czy działa odtwarzanie dźwięku
    if pygame.mixer.music.get_pos() <= 5:
        pygame.mixer.music.play()
    else:
        pygame.mixer.music.unpause()

def pause():
    pygame.mixer.music.pause()
