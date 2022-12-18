import ASCIIaudio
import ASCII_python_interface
import os
import sys
import time


def main():
    file = "media_files/AURORA-Cure_for_me360p.mp4"
    width = 90
    height = 60

    ASCIIaudio.soundmodule_init(file)
    clip_file = ASCII_python_interface.setup(file)  # inicjalizacja

    ASCIIaudio.play()   #Załącz muzykę
    ASCII_python_interface.play(clip_file, 0, width, height)  #Załącz video od klatki 0
        

if __name__ == '__main__':
    main()
