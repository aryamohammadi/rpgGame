#pragma once

#include <string>
#include <map>

class MainMenu {
public:
      
    // Display the main menu options
    void displayMenu();

    // Set the game difficulty (returns true if valid, false otherwise)
    bool setDifficulty(const std::string& difficulty);

    // Access the current difficulty
    std::string getDifficulty() const;

    // Settings menu for difficulty selection
    void settings();

    // Select a game option (e.g., New Game, Load Game)
    std::string selectGameOption();

    // Function to normalize input strings
    std::string normalizeInput(const std::string& input) const;

private:

    std::string currentDifficulty = "Elite"; // Default difficulty

    // A map of valid difficulties
    std::map<std::string, std::string> validDifficulties = {
        {"rookie", "Rookie"},
        {"elite", "Elite"},
        {"battlestar", "Battlestar"}
    };

    

    // A list of valid game options
    std::map<std::string, std::string> gameOptions = {
        {"new game", "New Game"},
        {"load game", "Load Game"}
    };
};