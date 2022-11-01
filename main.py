import ASCIIaudio
import ASCIIvideo
import os
import sys
import time

sys.path.append("build/lib.linux-x86_64-cpython*/") 
import ASCIIart

def setup(path, w, h):
    sys.tracebacklimit = 0
    ASCIIaudio.soundmodule_init(path)
    ASCIIvideo.module_init(path, w, h)
    ASCIIart.init(w, h)

def parse_args():
    args = {
    "-w" : "90",
    "-h" : "60",
    "-p" : "sample.mp4"
    }

    for i in range(3, len(sys.argv[3:])+2, 2):
        args[sys.argv[i]] = sys.argv[i+1]
    return args


def main():
    args = parse_args()
    # file = "media_files/AURORA-Cure_for_me360p.mp4"
    # width = 90
    # height = 60

    setup(args["-p"], int(args["-w"]), int(args["-h"]))  # inicjalizacja

    ASCIIaudio.play()   #Załącz muzykę
    ASCIIvideo.play(0)  #Załącz video od klatki 0
        
    ASCIIart.clean()    #Zwolnienie pamięci

if __name__ == '__main__':
    main()
