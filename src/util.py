from moviepy.editor import *
from moviepy.video.fx import *
import PIL



def craftDescription(broadcaster_name, game):
    craftedDesc = f"#{broadcaster_name} #{game}\n" +"#viral #Twitch #twitchclip #gaming " 
       
    return craftedDesc



def createCustomVideo(input_clip: str, title: str):

    temp_output_path = input_clip.replace('.mp4', '_temp.mp4')

    clip = VideoFileClip(input_clip)
    clip2 = clip.resize((640, 360)).set_fps(30)
    
    black_bar = ImageClip("BlackBar.png")
    top = black_bar.set_duration(clip.duration).set_position(("center", "top")).set_fps(1)
    bottom = black_bar.set_duration(clip.duration).set_position(("center", "bottom")).set_fps(1)
    
    text = TextClip(title, size=(640, 360), color="white").set_duration(clip.duration).set_position(("center", "center")).set_fps(1)
    textTop = CompositeVideoClip([top, text]).set_fps(1)

    combine = clips_array([[textTop], [clip2], [bottom]]).set_fps(30)

    combine.write_videofile(temp_output_path, codec='libx264')

    import os
    os.replace(temp_output_path, input_clip)

