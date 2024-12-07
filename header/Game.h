#ifndef GAME_H
#define GAME_H

#include "MainMenu.h"
#include "GameState.h"
#include "character.h"
#include "inventory.h"
#include "Map.h"
#include "SaveGame.h"
#include "LoadGame.h"
#include "Difficulty.h"
#include <string>
#include <sstream>
#include <iostream>
#include <filesystem>

class Game {
public:
    Game(); // Constructor

    void run(); // Main game loop
    void startGame(); // Starts the game

    // Game state management
    void newGame();                         // Start a new game
    bool loadGame(const std::string& saveFile); // Load a saved game
    void saveGame(const std::string& saveFile); // Save the current game

    // Serialization
    std::string serialize() const;         // Serialize game state to a string
    bool deserialize(const std::string& data); // Deserialize game state from a string

private:
    // Game states
    enum class GameState { MainMenu, InGame, GameOver };
    GameState currentState; // Current state of the game

    Character player;       // The main character
    Map gameMap;            // The game's map
    Inventory inventory;    // The game's inventory
    Difficulty difficulty;  // Difficulty settings
    MainMenu menu;          // Main menu handler

    void showMainMenu();    // Handle the main menu logic
    void playGame();        // Handle in-game logic
    void exitGame();        // Handle exiting the game

    // Normalizes user input
    std::string normalizeInput(const std::string& input) const;

    // Applies difficulty modifiers to the game state
    void applyDifficulty();
};

#endif // GAME_H