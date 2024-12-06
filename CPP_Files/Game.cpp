#include "../header/Game.h"
#include <sstream>

void Game::startGame() {
    std::cout << "Game starting!" << std::endl; // Placeholder
    std::cout << "Please enter the name for your player character: ";

    std::string playerName;
    std::cin >> playerName;

    Character playerCharacter (playerName);
    Weapon defaultWeapon = new Weapon();

    // Have player enter attackType
    // Declare Map with attackType as parameter
    // Start player in room 0 

    // Once player moves to new Room (down or right), start a battle if there are enemies
    // If there are items, offer to move them into storage
    // If the player enters "menu", offer to save and quit
    // save, equip, use, move, pickup

    // For every 100 experience, call increase storage capacity, and increase damage and health by 10
}

Game::~Game() {

}

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
