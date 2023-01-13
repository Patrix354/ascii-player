import ASCIIaudio
import ASCII_python_interface
import keyboard_detection
import os
import sys
import time
import argparse

def Parse_input_arguments():
    parser = argparse.ArgumentParser(description="ASCIIplayer - This is a simple multimedia player, but it works fully in terminal ")
    parser.add_argument('-W', '--width', type=int, metavar='', help='Width of displayed frame')
    parser.add_argument('-H', '--height', type=int, metavar='', help='Height of displayed frame')
    parser.add_argument('-P', '--path', type=str, metavar='', help='Path to media source file')
    arguments = parser.parse_args()
    return vars(arguments)

def main():
    arguments = Parse_input_arguments()
    keyboard_detection.set_console_attributes()
    ASCIIaudio.soundmodule_init(arguments["path"])
    clip_file = ASCII_python_interface.setup(arguments["path"])
    current_frame = 0

    while current_frame >= 0:
        ASCIIaudio.play() 
        current_frame = ASCII_python_interface.play(clip_file, current_frame, arguments["width"], arguments["height"])
        
        if current_frame > 0:
            ASCIIaudio.pause()
            while True:
                if keyboard_detection.is_pressed(32):
                    break
                

if __name__ == '__main__':
    main()
