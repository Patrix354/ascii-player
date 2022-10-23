import ASCIIaudio
import ASCIIvideo
import os
import sys

def Import_Module():        # Ta funkcja jest potrzebna tylko podczas użytkowania ziezainstalowanego modułu
    sys.path.append("build/lib.linux-x86_64-cpython-310/") 

if __name__ == '__main__':
    Import_Module()
    import ASCIIart

    ASCIIaudio.Soundtrack_extract("media_files/Al.mp4")
    ASCIIaudio.Soundmodule_init()
    ASCIIaudio.Do_some_music_things()

    ASCIIvideo.Import_Vid("media_files/Webdriver.mp4")
    f = ASCIIvideo.Extract_frame(0)

    ASCIIart.def_frame(len(f[0]), len(f))
    ASCIIart.load_frame(f)

    # ... 

    ASCIIart.clean()
