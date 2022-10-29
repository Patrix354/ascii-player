import ASCIIaudio
import ASCIIvideo
import os
import sys
from time import *

def Import_Module():        # Ta funkcja jest potrzebna tylko podczas użytkowania ziezainstalowanego modułu
    sys.path.append("build/lib.linux-x86_64-cpython-310/") 

if __name__ == '__main__':
    Import_Module()
    import ASCIIart

    ASCIIvideo.Import_Vid("media_files/RickRoll.mp4")  # Importowanie video
    f = ASCIIvideo.Extract_frame(0)
    
    ASCIIart.def_frame(len(f[0]), len(f))   #Zaalokowanie pamięci dla klatki o wymiarach takich jakie były w pliku 
    ASCIIart.def_scaled_frame(5)   #Zaalokowanie pamięci na przeskalowaną klatkę gdzie na 1 pixel przypada kwadrat o boku 10 pixeli
    
    framerate = 10

    start = time()
    for i in range(100):
        f = ASCIIvideo.Extract_frame(2*i)
        ASCIIart.load_frame(f)  #Załadowanie klatki do modułu
        ASCIIart.scale_frame()     #Wykonanie operacji przeskalowania klatki
        ASCIIart.map_pixels()
        ASCIIart.print()
        #sleep(0.05)
    stop = time()
    print(100/(stop-start), "\n")

    ASCIIart.clean()    #Zwolnienie pamięci
