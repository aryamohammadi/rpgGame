#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <string>
#include <fstream>
#include <iostream>

class SaveGame {
public:
    // Constructor accepting the file name to save
    explicit SaveGame(const std::string& filename);

    // Template to save any object that implements GameState
    template <typename GameState>
    bool save(const GameState& state) {
        std::ofstream file(saveFile);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open save file." << std::endl;
            return false;
        }

        // Use the serialize method of GameState
        file << state.serialize();
        file.close();
        return true;
    }

private:
    std::string saveFile;  // File where the game state will be saved
};

#endif