from upload import Upload
from util import *
import sys
import json
import os

jsonFile = sys.argv[1]
browser_profile = sys.argv[2]



# Load the JSON file
with open(jsonFile, 'r') as file:
    data = json.load(file)


upload = Upload(browser_profile, "geckodriver", 4, False)
# Iterate through the outer array
for inner_array in data:
    # Iterate through the inner array (list of clips)
    for clip in inner_array:
        
        createCustomVideo(clip['file_name'], clip['clip_description'])

        config = {
            "file" : clip['file_name'], # change to file_name
            "title" : clip['clip_description'] + " #shorts ",
            "description" : craftDescription(clip['broadcaster_name'], clip['game']),
            "tags" : [clip['broadcaster_name'], clip['game'], "shorts", "short", "Twitch", "clip", "gaming"]
        }
        
        # Do something with the clip information
        print(config)
        #print (craftDescription(clip['broadcaster_name'], clip['game']))
        upload.upload(**config)

        os.remove(clip['file_name'])
        

upload.close()
os.remove(jsonFile)