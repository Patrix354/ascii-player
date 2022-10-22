import ASCIIaudio
import ASCIIvideo
import os
import sys

def Import_Module():        #This function is only for development stage
    file_path = 'build/'
    sys.path.append(os.path.dirname(file_path))

if __name__ == '__main__':
    Import_Module()

    # ASCIIaudio.Soundtrack_extract("/home/piwo/Desktop/Studenckie_smieci/SEM3/PROS/ascii-player/Webdriver.mp4")
    # ASCIIaudio.Soundmodule_init()
    # ASCIIaudio.Do_some_music_shit()

    ASCIIvideo.Import_Vid("/home/piwo/Desktop/Studenckie_smieci/SEM3/PROS/ascii-player/Webdriver.mp4")
    f = ASCIIvideo.Extract_frame(10)
    print(f[200][150])