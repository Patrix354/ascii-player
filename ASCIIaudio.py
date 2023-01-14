import pygame 
import time
import moviepy.editor as mp

#########################
##### Audio segment #####
#########################

def soundtrack_extract(path):
    '''
    '''
    clip = mp.VideoFileClip(path)
    clip.audio.write_audiofile("media_files/soundtrack.mp3")

def soundmodule_init(file):
    '''
    '''
    soundtrack_extract(file)
    pygame.mixer.pre_init()
    pygame.mixer.init()
    pygame.mixer.music.load("media_files/soundtrack.mp3")

def play():
    '''
    '''
    if pygame.mixer.music.get_pos() <= 5:
        pygame.mixer.music.play()
    else:
        pygame.mixer.music.unpause()

def pause():
    pygame.mixer.music.pause()

def scroll_music(seconds):
    '''
    '''
    pygame.mixer.music.set_pos(seconds)

def restart_music():
    '''
    '''
    pygame.mixer.music.rewind()