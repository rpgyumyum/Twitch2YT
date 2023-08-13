import json
from selenium import webdriver
from webdriver_manager.firefox import GeckoDriverManager

# Initialize the Firefox driver using GeckoDriverManager
driver = webdriver.Firefox(executable_path=GeckoDriverManager().install())

# Load the JSON file
with open('Valorant.json', 'r') as file:
    data = json.load(file)

# Iterate through the outer array
for inner_array in data:
    # Iterate through the inner array (list of clips)
    for clip in inner_array:
        broadcaster_name = clip['broadcaster_name']
        clip_description = clip['clip_description']
        clip_name = clip['clip_name']
        game = clip['game']
        
        # Do something with the clip information
        print(f"Clip {game} - {broadcaster_name}")

# Close the driver after you're done
driver.quit()
