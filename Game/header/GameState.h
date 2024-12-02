#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>

class GameState {
public:
    virtual std::string serialize() const = 0; // Converts the game state to a string
    virtual bool deserialize(const std::string& data) = 0; // Reconstructs the game state
    virtual ~GameState() = default;
};

#endif
