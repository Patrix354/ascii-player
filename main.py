import ASCIIaudio
import ASCII_python_interface
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

    ASCIIaudio.soundmodule_init(arguments["path"])
    clip_file = ASCII_python_interface.setup(arguments["path"])

    ASCIIaudio.play() 
    ASCII_python_interface.play(clip_file, 0, arguments["width"], arguments["height"])
        

if __name__ == '__main__':
    main()
