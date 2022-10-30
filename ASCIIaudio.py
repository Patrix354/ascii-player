import pygame 
import time
import moviepy.editor as mp

#########################
##### Audio segment #####
#########################

def Soundtrack_extract(path):   # Pobranie ścieżki dźwiękowej z pliku
    clip = mp.VideoFileClip(path)
    clip.audio.write_audiofile("media_files/soundtrack.mp3")

def Soundmodule_init(file): # Załadowanie pobranej ścieżki dźwiękowej
    Soundtrack_extract(file)
    
    pygame.mixer.pre_init()
    pygame.mixer.init()
    pygame.mixer.music.load("media_files/soundtrack.mp3")

def play():   # funkcja do przetestowania czy działa odtwarzanie dźwięku
    pygame.mixer.music.play()
