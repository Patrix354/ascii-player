import moviepy.editor as mp
import numpy as np
import cv2
import sys
import time
import keyboard_detection
import ASCIImodule
import ASCIIaudio

#########################
##### Video segment #####
#########################

def Import_Vid(path):
    return cv2.VideoCapture(path)

def Get_framerate_of_clip(clip):
    '''
    This function returns framerate of clip
    '''
    return clip.get(5)

def Get_number_of_frames_in_clip(clip):
    '''
    This function returns length of video in frame number
    '''
    return clip.get(7)

def Set_current_frame(clip, frame_number):
    '''
    This function sets player pointer to a given frame
    '''
    clip.set(1, frame_number)

def Read_frame_from_clip(clip):
    '''
    This function extracts frame from clip file without any processing
    '''
    return clip.read()[1]

def Resize_frame(frame, width, height):
    '''
    This function resizes frame to given dimentions
    '''
    return cv2.resize(frame, (width, height), interpolation=cv2.INTER_AREA)

def Monochromatize_frame(frame):
    '''
    This function monochromatizes frame
    '''
    return cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

def extract_frame(clip, frame_number, width, height):
    '''
    This function extracts frame from clip file, resizes it, monochromatizes it
    and returns as a list
    '''
    Set_current_frame(clip, frame_number)
    frame = Read_frame_from_clip(clip)                    
    frame = Resize_frame(frame, width, height)
    frame = Monochromatize_frame(frame)
    return frame.tolist()

def setup(file):
    ASCIIaudio.soundmodule_init(file)
    return Import_Vid(file)

def play(clip, begin_frame, width, height):
    '''
    This function executes sequence of procedures to play a video, gets nessesary properties for smooth display and 
    calls function responsible for managing place of timestamp (here it names current_frame_number)
    '''
    ASCIIaudio.play() 
    framerate = Get_framerate_of_clip(clip)
    number_of_frames = Get_number_of_frames_in_clip(clip)
    start = time.time()
    frame_offset = 0

    while True:
        overpassed_time = time.time() - start
        current_frame_number = int(overpassed_time * framerate) + begin_frame + frame_offset
        if current_frame_number >= number_of_frames:
            return -1

        image = extract_frame(clip, current_frame_number, width, height)   
        ASCIImodule.Process_and_print(image)


        pressed_key = keyboard_detection.what_is_pressed()
        if pressed_key == 32: #SPACE
            ASCIIaudio.pause()
            return current_frame_number
        if pressed_key == 113: # Quit - q key
            sys.exit(0)

        frame_offset = manage_scrolling(framerate, frame_offset, current_frame_number, number_of_frames, pressed_key)
        

def manage_scrolling(framerate, frame_offset, current_frame_number, number_of_frames, pressed_key):
    '''
    This function takes bunch of properties of a video like framerate,
    how much video is already scrolled (here it names frame_offset), current playing frame, total count of frames in file
    and key that was pressed (if it is not value of pressed key is None).
    It returns new frame_offset (overall moves timestamp 5s forward or backward)
    '''
    if pressed_key == 97: #LEFT ARROW - a key
        if current_frame_number < 5*framerate:
            ASCIIaudio.restart_music()
            frame_offset = -current_frame_number
        else:
            frame_offset -= 5*framerate
            ASCIIaudio.scroll_music((current_frame_number/framerate) - 5)

    if pressed_key == 100: #RIGHT ARROW - d key
        if current_frame_number > (number_of_frames - 5*framerate):
            sys.exit(0)
        else:
            frame_offset += 5*framerate
            ASCIIaudio.scroll_music((current_frame_number/framerate) + 5)
    return frame_offset