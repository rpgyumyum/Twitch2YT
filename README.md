# Twitch2YT
**Download latest Twitch-clips using it's API and upload them to YouTube-shorts with the Selenium webdriver. This Program can automate content creation for creators and others by scheduling when it should run on a server**

## Dependencies 
- Pillow 9.5.0
- curl 8.2.1
- jsoncpp 
- sqlite3 3.42.0
- Moviepy
- Firefox 116.0
- Firefox - Geckodriver 0.33.0
- gcc 13.2.0
- python 3.11.4
- make 4.4.1

The only version specific package is Pillow because a Moviepy uses a deprecated version of a PIL function.
## Installation 
The program can be used from inside the cloned directory (Maybe I will ad an actual system installation in the future). First we need to compile the CPP sourcefiles with make (make sure to edit the variables in main.cpp to use your twitch API keys + your specific config)
``` bash
$ make clean install
```

After the compilation we get a binary called "TWITCH". 

Then you need to make a database (necessary information in "DATABASE") and put the information in it. The passwords and email columns can be empty. 

In the browser-profile column put in the root directory of a browser where you are logged into your YouTube account. 

## Usage 
After following the installation steps you can execute the binary ```$ ./TWITCH``` 
If Selenium has any issue increase the sleep time or make sure none of those pesky YouTube suggestion boxes pop up and interfere with the webdriver.
