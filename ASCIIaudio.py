import pygame 
import time
import moviepy.editor as mp

#########################
##### Audio segment #####
#########################

def Soundtrack_extract(path):   # Pobranie ścieżki dźwiękowej z pliku
    clip = mp.VideoFileClip(path)
    clip.audio.write_audiofile("media_files/soundtrack.mp3")

def Soundmodule_init(): # Załadowanie pobranej ścieżki dźwiękowej
    pygame.mixer.init()
    pygame.mixer.music.load("media_files/soundtrack.mp3")

def Do_some_music_things():   # funkcja do przetestowania czy działa odtwarzanie dźwięku
    pygame.mixer.music.play()
    time.sleep(3)
    pygame.mixer.music.pause()
    time.sleep(3)
    pygame.mixer.music.unpause()
    time.sleep(3)
    pygame.mixer.music.pause()