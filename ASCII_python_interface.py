import moviepy.editor as mp
import numpy as np
import cv2
import sys
import time
import keyboard_detection
import ASCIImodule

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
    return Import_Vid(file)

def play(clip, begin_frame, width, height):
    '''
    This function executes sequence of procedures to play a video
    '''
    framerate = Get_framerate_of_clip(clip)
    number_of_frames = Get_number_of_frames_in_clip(clip)
    start = time.time()

    while True:
        if keyboard_detection.is_pressed(32) == True: #SPACE
            return current_frame_number

        current_frame_number = int((time.time() - start) * framerate) + begin_frame
        if current_frame_number >= number_of_frames:
            return -1

        image = extract_frame(clip, current_frame_number, width, height)   
        ASCIImodule.Process_and_print(image)
