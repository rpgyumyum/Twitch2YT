#include "twitch.hpp"
#include <cstdlib>
#include <fstream>


int main(int argc, const char* argv [])
{
    std::string clientId = "";
    std::string clientSecret = "";
    std::string jsonDataClipsCount = "100"; //How many clips json infortmation we retrieve(need to be higher than clipscount bc we filter for english content)
    int timeSeconds = (86400 * 60); //time in seconds substracted from current time from when we dowload clips
    int clipsCount = 2; //how many clips we download per game/broadcaster

    std::string authToken = getOAuthToken(clientId, clientSecret);



    std::vector<Bubble> bubbles = getAllBubbles();

    
    for (int i = 0; i < bubbles.size(); i++)
    {
        Json::Value allClips(Json::arrayValue);
        
        for (int j = 0; j < bubbles[i].GAMES_NAMES.size();j++)
        {
            std::cout << bubbles[i].GAMES_NAMES[j] << ": " << std::endl;
            std::string newGameId = getGameOrBroadcasterId(bubbles[i].GAMES_NAMES[j], authToken, clientId, false);
            std::cout << newGameId << std::endl;
            Json::Value JsonData = getClipJsonData(false, authToken, clientId, newGameId, jsonDataClipsCount, getRFC3339TimeLast24H(timeSeconds));
            Json::Value clipsArray = downloadClipsFromJson(JsonData, clipsCount, bubbles[i].BUBBLE_NAME, j, bubbles[i].GAMES_NAMES[j]);
            allClips.append(clipsArray);
            std::cout << std::endl;
        }
        

        for (int j = 0; j < bubbles[i].BROADCASTER_NAMES.size();j++)
        {
            std::cout << bubbles[i].BROADCASTER_NAMES[j] << ": " << std::endl;
            std::string newBroadcasterId = getGameOrBroadcasterId(bubbles[i].BROADCASTER_NAMES[j], authToken, clientId, true);
            std::cout << newBroadcasterId << std::endl;
            Json::Value JsonData = getClipJsonData(true, authToken, clientId, newBroadcasterId, jsonDataClipsCount, getRFC3339TimeLast24H(timeSeconds));
            Json::Value clipsArray = downloadClipsFromJson(JsonData, clipsCount, bubbles[i].BUBBLE_NAME, j, bubbles[i].GAMES_NAMES[j]);
            allClips.append(clipsArray);
            std::cout << std::endl;
        }


        std::ofstream o(bubbles[i].BUBBLE_NAME + ".json"); // Write all clips to a single JSON file
        if (o.is_open())
        {
            Json::StreamWriterBuilder writer;
            std::unique_ptr<Json::StreamWriter> jsonWriter(writer.newStreamWriter());
            jsonWriter->write(allClips, &o);
            o.close();
        }
        else
        {
            std::cerr << "Unable to open file for writing." << std::endl;
        } 


        //Upload every downloaded clip with python 
        std::string pythonCommand = "python src/main.py " + bubbles[i].BUBBLE_NAME + ".json " + bubbles[i].BROWSER_PROFILE_PATH;
        std::cout << pythonCommand << std::endl << std::endl << std::endl << std::endl;
        system(pythonCommand.c_str());
        
    }

    return 0;

}
