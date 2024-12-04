#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "../../header/character.h"
#include "../../header/inventory.h"
#include "../../header/Map.h"
#include <string>
#include <sstream>

class Game : public GameState {
public:
    Game() : character(), inventory(), map() {}

    // Serialize the entire game state
    std::string serialize() const override {
        std::ostringstream oss;
        oss << character.serialize() << "\n"
            << inventory.serialize() << "\n"
            << map.serialize();
        return oss.str();
    }

    // Deserialize the entire game state
    bool deserialize(const std::string& data) override {
        std::istringstream iss(data);
        std::string charData, invData, mapData;

        if (!std::getline(iss, charData) || 
            !std::getline(iss, invData) || 
            !std::getline(iss, mapData)) {
            return false;
        }

        return character.deserialize(charData) &&
               inventory.deserialize(invData) &&
               map.deserialize(mapData);
    }

    // Start the game
    void startGame() {
        std::cout << "Game starting!" << std::endl; // Placeholder
    }

private:
    Character character; // Player character
    Inventory inventory; // Player inventory
    Map map;             // Game map
};

#endif
