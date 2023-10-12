#include "twitch.hpp"
#include <sqlite3.h>


std::vector<std::string> getArrayFromString(std::string databaseString)
{
    std::vector<std::string> databaseArray;

    std::stringstream ss(databaseString);
    std::string item;

    while (std::getline(ss, item, ',')) {
        databaseArray.push_back(item);
    }

    
    return databaseArray;
}

std::vector<Bubble> getAllBubbles()
{
    std::vector<Bubble> bubbles; // Vector to store all retrieved bubbles

    sqlite3* db;
    int rc = sqlite3_open("Credentials.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }

    const char* sql_query = "SELECT * FROM Credentials;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql_query, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Bubble newBubble;
        newBubble.BUBBLE_NAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (sqlite3_column_text(stmt, 1))
            newBubble.GAMES_NAMES = getArrayFromString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        if (sqlite3_column_text(stmt, 2))
            newBubble.BROADCASTER_NAMES = getArrayFromString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
         if (sqlite3_column_text(stmt, 6))
            newBubble.BROWSER_PROFILE_PATH = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

        bubbles.push_back(newBubble); // Add the retrieved bubble to the vector
    }

    

    if (rc != SQLITE_DONE) {
        std::cerr << "Error while fetching data: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return bubbles; // Return the vector containing all retrieved bubbles
}
