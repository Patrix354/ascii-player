import moviepy.editor as mp

#########################
##### Video segment #####
#########################

def Import_Vid(path):
    global film
    film = mp.VideoFileClip(path)

def Extract_frame(num):
    global film
    frame = film.get_frame(num)
    return frame
