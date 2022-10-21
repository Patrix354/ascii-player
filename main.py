import pygame 
import time
import moviepy.editor as mp

#########################
### Audio segment

def Soundtrack_extract(path):
    clip = mp.VideoFileClip(path)
    clip.audio.write_audiofile("soundtrack.mp3")

def Soundmodule_init():
    pygame.mixer.init()
    pygame.mixer.music.load("soundtrack.mp3")

def Do_some_music_shit():
    pygame.mixer.music.play()
    time.sleep(3)
    pygame.mixer.music.pause()
    time.sleep(3)
    pygame.mixer.music.unpause()
    time.sleep(3)

#################
### Video segment

def Import_Vid(path):
    global film
    film = mp.VideoFileClip(path)

def Extract_frame(num):
    frame = film.get_frame(3)
    return frame

if __name__ == '__main__':
    Soundtrack_extract("Al.mp4")
    Soundmodule_init()
    #Do_some_music_shit()

    Import_Vid("Al.mp4")
    f = Extract_frame(1)
    print(f)