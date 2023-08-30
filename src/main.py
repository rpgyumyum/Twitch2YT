from upload import Upload
from util import *
import sys
import json

jsonFile = sys.argv[1]


# Load the JSON file
with open(jsonFile, 'r') as file:
    data = json.load(file)


upload = Upload("/home/Ikarus/.mozilla/firefox/kyos7cmg.Selenium", "geckodriver", 4, False, False)
# Iterate through the outer array
for inner_array in data:
    # Iterate through the inner array (list of clips)
    for clip in inner_array:
        
        #moviepy 

        config = {
            "file" : clip['file_name'], # change to file_name
            "title" : clip['clip_description'] + " #shorts",
            "description" : craftDescription(clip['broadcaster_name'], clip['game']),
            "tags" : [clip['broadcaster_name'], clip['game'], "shorts", "short", "Twitch", "clip", "gaming"]
        }
        
        # Do something with the clip information
        print(config)
        #print (craftDescription(clip['broadcaster_name'], clip['game']))
        upload.upload(**config)

        #remove clip
        #print into a file: clip uploaded 

upload.close()