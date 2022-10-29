import ASCIIaudio
import ASCIIvideo
import os
import sys
import time

def Import_Module():        # Ta funkcja jest potrzebna tylko podczas użytkowania ziezainstalowanego modułu
    sys.path.append("build/lib.linux-x86_64-cpython-310/") 

if __name__ == '__main__':
    Import_Module()
    import ASCIIart

    ASCIIvideo.Import_Vid("media_files/Webdriver.mp4")  # Importowanie video
    f = ASCIIvideo.Extract_frame(0)
    
    ASCIIart.def_frame(len(f[0]), len(f))   #Zaalokowanie pamięci dla klatki o wymiarach takich jakie były w pliku 
    ASCIIart.load_frame(f)  #Załadowanie klatki do modułu

    ASCIIart.def_scaled_frame(10)   #Zaalokowanie pamięci na przeskalowaną klatkę gdzie na 1 pixel przypada kwadrat o boku 10 pixeli
    ASCIIart.scale_frame()     #Wykonanie operacji przeskalowania klatki

    ASCIIart.clean()    #Zwolnienie pamięci
