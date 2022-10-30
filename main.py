import ASCIIaudio
import ASCIIvideo
import os
import sys
import time

def add_module_path():        # Ta funkcja jest potrzebna tylko podczas użytkowania niezainstalowanego modułu
    sys.path.append("build/lib.linux-x86_64-cpython-310/") 

def setup(path, w, h):
    add_module_path()
    import ASCIIart

    ASCIIaudio.soundmodule_init(path)
    ASCIIvideo.module_init(path, w, h)
    ASCIIart.init(w, h)

def main():
    add_module_path()
    import ASCIIart

    file = "media_files/AURORA-Cure_for_me360p.mp4"
    width = 90
    height = 60

    setup(file, width, height)  # inicjalizacja

    ASCIIaudio.play()   #Załącz muzykę
    ASCIIvideo.play(0)  #Załącz video od klatki 0
        
    ASCIIart.clean()    #Zwolnienie pamięci

if __name__ == '__main__':
    main()
