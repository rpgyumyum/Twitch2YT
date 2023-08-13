#include "twitch.hpp"
#include <ctime>
#include <locale>

std::string getRFC3339TimeLast24H(int timeSubtract)//86400 is a day
{
    std::time_t currentTime = std::time(nullptr);

    // Calculate time 24 hours ago (subtracting 86,400 seconds)
    std::time_t twentyFourHoursAgo = currentTime - timeSubtract;

    // Format the time to RFC3339 date
    char timeString[std::size("yyyy-mm-ddThh:mm:ssZ")];
    std::strftime(std::data(timeString), std::size(timeString),
        "%FT%TZ", std::gmtime(&twentyFourHoursAgo));
    
    std::string RFC3339Time = static_cast<std::string>(timeString);
    return RFC3339Time;
}

std::string replaceSpacesWithPercent20(const std::string& inputString) 
{
    std::string outputString;
    for (char c : inputString) 
    {
        if (c == ' ') 
        {
            
            outputString += "%20";
        } 
        else 
        {
            outputString += c;
        }
    }
    return outputString;
}