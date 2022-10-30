import ASCIIaudio
import ASCIIvideo
import os
import sys
import time

def Import_Module():        # Ta funkcja jest potrzebna tylko podczas użytkowania ziezainstalowanego modułu
    sys.path.append("build/lib.linux-x86_64-cpython-310/") 

def setup(path, radius):
    Import_Module()
    import ASCIIart

    ASCIIaudio.Soundmodule_init(path)
    width, height = ASCIIvideo.Vid_module_init(path)
    ASCIIart.init(width, height, radius)

def main():
    file = "media_files/RickRoll.mp4"
    scale = 7

    setup(file, scale)

    ASCIIaudio.play()
    ASCIIvideo.play(0)
        
    ASCIIart.clean()    #Zwolnienie pamięci

if __name__ == '__main__':
    main()