#include <cstring>
#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <vector>



//Twitch utility
std::string replaceSpacesWithPercent20(const std::string& inputString);
std::string getRFC3339TimeLast24H(int timeSubtract);

//Twitch functions
std::string getOAuthToken(const std::string& clientId, const std::string& clientSecret);
std::string getGameOrBroadcasterId(std::string gameOrName, std::string& access_token, std::string& client_id, bool searchForBroadcaster);
Json::Value getClipJsonData(bool searchForBroadcaster, std::string& access_token, std::string& client_id, std::string& masterId, std::string countClips, std::string RFC3339Date);
Json::Value downloadClipsFromJson(Json::Value clipsRoot, int clipsCount, std::string bubbleName, int iterator, std::string game);

//SQLITE 
struct Bubble {
    std::string BUBBLE_NAME;
    std::vector<std::string> GAMES_NAMES;
    std::vector<std::string> GAME_IDS;
    std::vector<std::string> BROADCASTER_NAMES;
    std::vector<std::string> BROADCASTER_IDS;
    std::string ACCOUNT_EMAIL;
    std::string TIKTOK_ACCOUNT_PASSWORD;
    std::string YOUTUBE_ACCOUNT_PASSWORD;
};

std::vector<Bubble> getAllBubbles();
