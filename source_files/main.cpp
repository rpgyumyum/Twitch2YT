#include "twitch.hpp"
#include <fstream>

int main(int argc, const char* argv [])
{
    std::string clientId = "mnt51l94omwga9pdo9mskeaxd5fzsq";
    std::string clientSecret = "q9nhswkn2b8csepv5t5gmqtup3kz6h";
    std::string authToken = "w8vjnn9zxc101lwldmtum5lm7jhzty";

    std::vector<Bubble> bubbles = getAllBubbles();

    

    for (int i = 0; i < bubbles.size(); i++)
    {
        Json::Value allClips(Json::arrayValue);
        
        for (int j = 0; j < bubbles[i].GAMES_NAMES.size();j++)
        {
            std::cout << bubbles[i].GAMES_NAMES[j] << ": " << std::endl;
            std::string newGameId = getGameOrBroadcasterId(bubbles[i].GAMES_NAMES[j], authToken, clientId, false);
            std::cout << newGameId << std::endl;
            Json::Value JsonData = getClipJsonData(false, authToken, clientId, newGameId, static_cast<std::string>("100"), getRFC3339TimeLast24H((86400)));
            Json::Value clipsArray = downloadClipsFromJson(JsonData, 2, bubbles[i].BUBBLE_NAME, j, bubbles[i].GAMES_NAMES[j]);
            allClips.append(clipsArray);
            std::cout << std::endl;
        }

        for (int j = 0; j < bubbles[i].BROADCASTER_NAMES.size();j++)
        {
            std::cout << bubbles[i].BROADCASTER_NAMES[j] << ": " << std::endl;
            std::string newBroadcasterId = getGameOrBroadcasterId(bubbles[i].BROADCASTER_NAMES[j], authToken, clientId, true);
            std::cout << newBroadcasterId << std::endl;
            Json::Value JsonData = getClipJsonData(true, authToken, clientId, newBroadcasterId, static_cast<std::string>("100"), getRFC3339TimeLast24H((86400)));
            Json::Value clipsArray = downloadClipsFromJson(JsonData, 2, bubbles[i].BUBBLE_NAME, j, bubbles[i].GAMES_NAMES[j]);
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
        
    }

    return 0;

}