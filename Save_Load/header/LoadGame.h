#ifndef LOADGAME_H
#define LOADGAME_H

#include <string>
#include <fstream>
#include <iostream>

class LoadGame {
public:
    // Constructor accepting the file name to load
    explicit LoadGame(const std::string& filename);

    // Template method to load any object that implements GameState
    template <typename GameState>
    bool load(GameState& state) {
        std::ifstream file(loadFile);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open load file." << std::endl;
            return false;
        }

        // Read the serialized data from the file
        std::string serializedData((std::istreambuf_iterator<char>(file)),
                                    std::istreambuf_iterator<char>());

        file.close();

        // Use the deserialize method of GameState
        return state.deserialize(serializedData);
    }

private:
    std::string loadFile;  // The file where the game state will be loaded from
};

#endif
