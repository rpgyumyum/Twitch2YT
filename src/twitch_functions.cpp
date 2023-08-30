#include "twitch.hpp"
#include <curl/curl.h>




size_t curlWriteCallback(void* ptr, size_t size, size_t nmemb, std::stringstream* stream) 
{
    size_t totalSize = size * nmemb;
    stream->write(static_cast<char*>(ptr), totalSize);
    return totalSize;
}

std::string getOAuthToken(const std::string& clientId, const std::string& clientSecret) 
{
    std::string OToken;

    std::string apiUrl = "https://id.twitch.tv/oauth2/token";
    std::string postData = "client_id=" + clientId + "&client_secret=" + clientSecret + "&grant_type=client_credentials";

    CURL* curl = curl_easy_init();
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        std::stringstream responseStream;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStream);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) 
        {
            // Request successful, handle the response
            std::string response = responseStream.str();
            std::cout << "Response: " << response << std::endl;

            Json::Value root;
            Json::CharReaderBuilder builder;
            std::string errs;
            std::istringstream stream(response);

            if (Json::parseFromStream(builder, stream, &root, &errs)) 
            {
                // Extract the access token from the JSON response
                if (root.isMember("access_token") && root["access_token"].isString()) 
                {
                    OToken = root["access_token"].asString();
                } 
                else 
                {
                    std::cerr << "Failed to extract access token from the JSON response." << std::endl;
                }
            } 
            else 
            {
                std::cerr << "Failed to parse JSON: " << errs << std::endl;
            }
            
        } 
        else 
        {
            // Request failed
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    } 
    else 
    {
        std::cerr << "Failed to initialize curl" << std::endl;
    }

    return OToken;
}

std::string getGameOrBroadcasterId(std::string gameOrName, std::string& access_token, std::string& client_id, bool searchForBroadcaster)
{
    std::string GameId;
    std::string apiUrl;

    if (searchForBroadcaster == true) 
    {
        apiUrl = "https://api.twitch.tv/helix/users?login=" + gameOrName;  
    }
    else if (searchForBroadcaster == false)
    {
        apiUrl = "https://api.twitch.tv/helix/games?name=" + gameOrName; 
    }
    
    std::string bearer = "Authorization: Bearer " + access_token;
    std::string header = "Client-Id: " + client_id;
    
    CURL* curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, bearer.c_str());
        headers = curl_slist_append(headers, header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        std::stringstream responseStream;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStream);

        CURLcode res = curl_easy_perform(curl);  
        if (res == CURLE_OK)
        {
            std::string response = responseStream.str();

            Json::Value root;
            Json::CharReaderBuilder builder;
            std::string errs;
            std::istringstream stream(response);

            if(Json::parseFromStream(builder, stream, &root, &errs))
            {
                if (root.isMember("data") && root["data"].isArray() && !root["data"].empty())
                {
                    GameId = root["data"][0]["id"].asString();
                } else 
                {
                    std::cerr << "Failed extrat id from json" << std::endl;
                }
            }
            else 
            {
                std::cerr << "JSON: " << errs << std::endl;
            }

        }
        else 
        {
            std::cerr << curl_easy_strerror(res) << std::endl;
        }

        curl_slist_free_all(headers);

     }else
    {
       std::cout << "Failed to init curl"; 
    }

    curl_easy_cleanup(curl);
    

    return GameId;
}

Json::Value getClipJsonData(bool searchForBroadcaster, std::string& access_token, std::string& client_id, std::string& GameBroadId, std::string countClips, std::string RFC3339Date)
{
    Json::Value clipsRoot; 
    std::string apiUrl;
    
    

    if (searchForBroadcaster == true)
    {
        apiUrl = "https://api.twitch.tv/helix/clips?broadcaster_id=" + GameBroadId + "&started_at=" + RFC3339Date + "&first=" + countClips; 
    }
    else
    {
        apiUrl = "https://api.twitch.tv/helix/clips?game_id=" + GameBroadId + "&started_at=" + RFC3339Date + "&first=" + countClips; 
    }
    
    
    
    std::string bearer = "Authorization: Bearer " + access_token;
    std::string header = "Client-Id: " + client_id;
    
    CURL* curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, bearer.c_str());
        headers = curl_slist_append(headers, header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        std::stringstream responseStream;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseStream);

        CURLcode res = curl_easy_perform(curl);  
        if (res == CURLE_OK)
        {
            std::string response = responseStream.str();

            Json::CharReaderBuilder builder;
            std::string errs;
            std::istringstream stream(response);

            if(!Json::parseFromStream(builder, stream, &clipsRoot, &errs))
            {
                std::cerr << "JSON: " << errs << std::endl;  
            }
            
        }
        else 
        {
            std::cerr << curl_easy_strerror(res) << std::endl;
        }

        curl_slist_free_all(headers);

     }else
    {
       std::cout << "Failed to init curl"; 
    }

    curl_easy_cleanup(curl);
    
    return clipsRoot;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

Json::Value downloadClipsFromJson(Json::Value clipsRoot, int clipsCount, std::string bubbleName, int iterator, std::string game)
{
    Json::Value dataArray = clipsRoot["data"];
    Json::Value clipArray(Json::arrayValue);

    int counter{0};
    
    for (auto& entry : dataArray)
    {
        if (entry["language"].asString() == "en" || entry["language"].asString() == "en-gb")
        {
            std::string thumbnailUrl = entry["thumbnail_url"].asString(); 
        
            size_t foundPos = thumbnailUrl.find("-preview");
            thumbnailUrl.erase(foundPos);

            thumbnailUrl = thumbnailUrl + ".mp4";

            CURL *curl;
            FILE *fp;
            CURLcode res;
            std::string url = thumbnailUrl;

            
            std::string filePath = "/home/Ikarus/Projects/Twitch/clips/" + entry["id"].asString() + ".mp4";
            char outfilename[FILENAME_MAX];
            std::strncpy(outfilename, filePath.c_str(), sizeof(outfilename) - 1);
            outfilename[sizeof(outfilename) - 1] = '\0';

            curl = curl_easy_init();
            if (curl) 
            {
                fp = fopen(outfilename,"wb");
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);
                fclose(fp);
            }

            //std::string clipUrl = thumbnailUrl.substr(0, thumbnailUrl.find("-preview", 0));
            std::cout << counter + 1 << " DOWNLOAD: " << filePath << std::endl;

            Json::Value clipObject;
            clipObject["file_name"] = filePath;
            clipObject["clip_description"] = entry["title"].asString();
            clipObject["broadcaster_name"] = entry["broadcaster_name"].asString();
            clipObject["game"] = game;

            clipArray.append(clipObject);


            if (++counter >= clipsCount)
            {
                break;
            }
              
            
        }

        
    }
    
    return clipArray;

}
