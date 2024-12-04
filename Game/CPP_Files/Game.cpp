#include "../header/Game.h"
#include <sstream>

// Serialize the game state into a string
std::string Game::serialize() const {
    std::ostringstream oss;
    oss << character.serialize() << "\n"
        << map.serialize() << "\n"
        << inventory.serialize();
    return oss.str();
}

// Deserialize the game state from a string
bool Game::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string charData, mapData, invData;

    if (!std::getline(iss, charData) || 
        !std::getline(iss, mapData) ||
        !std::getline(iss, invData)) {
        return false;
    }

    return character.deserialize(charData) &&
           map.deserialize(mapData) &&
           inventory.deserialize(invData);
}
