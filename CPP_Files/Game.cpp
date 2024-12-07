#include "../header/Game.h"
#include <sstream>
#include <filesystem>
#include <limits>
#include <iostream>
#include <algorithm>

Game::Game()
    : currentState(GameState::MainMenu),
      player("Hero"),
      gameMap(Weapon::WeaponType::Sword) // Default initialization for Map
{}

void Game::run() {
    while (currentState != GameState::GameOver) {
        switch (currentState) {
            case GameState::MainMenu:
                showMainMenu();
                break;
            case GameState::InGame:
                playGame();
                break;
            case GameState::GameOver:
                std::cout << "\nGame Over! Thanks for playing.\n";
                break;
        }
    }
}

void Game::newGame() {
    std::cout << "Starting a new game...\n";
    player = Character("Hero"); // Reset the player
    inventory = Inventory();    // Reset the inventory
    difficulty = Difficulty();  // Reset difficulty
    applyDifficulty();          // Apply difficulty modifiers

    // Allow the player to choose their weapon type
    std::cout << "Choose your weapon type (1 = Sword, 2 = Staff, 3 = Bow): ";
    int weaponChoice;
    std::cin >> weaponChoice;

    Weapon::WeaponType weaponType;
    switch (weaponChoice) {
        case 1:
            weaponType = Weapon::WeaponType::Sword;
            break;
        case 2:
            weaponType = Weapon::WeaponType::Staff;
            break;
        case 3:
            weaponType = Weapon::WeaponType::Bow;
            break;
        default:
            std::cout << "Invalid choice, defaulting to Sword.\n";
            weaponType = Weapon::WeaponType::Sword;
    }

    gameMap = Map(weaponType); // Initialize the map with the chosen weapon type
    currentState = GameState::InGame; // Transition to the game state
}

bool Game::loadGame(const std::string& saveFile) {
    std::cout << "Loading game from " << saveFile << "...\n";
    LoadGame loader(saveFile);
    std::string data;
    if (loader.load(data) && deserialize(data)) {
        applyDifficulty();      // Apply difficulty after deserialization
        currentState = GameState::InGame; // Transition to the game state
        std::cout << "Game loaded successfully!\n";
        return true;
    }
    std::cout << "Failed to load the game.\n";
    return false;
}

void Game::saveGame(const std::string& saveFile) {
    std::cout << "Saving game to " << saveFile << "...\n";
    SaveGame saver(saveFile);
    if (saver.save(serialize())) {
        std::cout << "Game saved successfully!\n";
    } else {
        std::cout << "Failed to save the game.\n";
    }
}

std::string Game::serialize() const {
    std::ostringstream oss;
    oss << player.serialize() << "\n"
        << difficulty.serialize() << "\n"
        << gameMap.serialize() << "\n"
        << inventory.serialize();
    return oss.str();
}

bool Game::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string playerData, difficultyData, mapData, inventoryData;

    if (!std::getline(iss, playerData) ||
        !std::getline(iss, difficultyData) ||
        !std::getline(iss, mapData) ||
        !std::getline(iss, inventoryData)) {
        return false;
    }

    return player.deserialize(playerData) &&
           difficulty.deserialize(difficultyData) &&
           gameMap.deserialize(mapData) &&
           inventory.deserialize(inventoryData);
}

void Game::applyDifficulty() {
    player.setDamage(player.getDamage() * difficulty.getAttackMultiplier());
    player.setHealth(player.getHealth() * difficulty.getHealthModifier());
}

void Game::showMainMenu() {
    menu.displayMenu();
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            newGame();
            break;
        case 2: {
            std::string saveFile;
            std::cout << "Enter the save file name: ";
            std::cin >> saveFile;
            if (!loadGame(saveFile)) {
                std::cout << "Returning to Main Menu...\n";
            }
            break;
        }
        case 3:
            exitGame();
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

void Game::playGame() {
    std::cout << "\nWelcome to the game! Explore, battle, and survive.\n";
    std::string playerCommand;

    while (true) {
        std::cout << "\nWhat would you like to do? (Type 'save' to save progress, 'quit' to exit): ";
        std::cin >> playerCommand;

        std::transform(playerCommand.begin(), playerCommand.end(), playerCommand.begin(), ::tolower);

        if (playerCommand == "save") {
            while (true) {
                std::cout << "\nPress 1 to Save and Continue or Press 2 to Save and Return to the Main Menu: ";
                std::cin >> playerCommand;

                if (playerCommand == "1") {
                    saveGame("savefile.json");
                    std::cout << "Game saved! Continuing...\n";
                    break;
                } else if (playerCommand == "2") {
                    saveGame("savefile.json");
                    std::cout << "Game saved! Returning to the Main Menu...\n";
                    currentState = GameState::MainMenu;
                    return;
                } else {
                    std::cout << "Invalid choice! Please enter 1 or 2.\n";
                }
            }
        } else if (playerCommand == "quit") {
            std::cout << "Exiting the game. Goodbye!\n";
            currentState = GameState::GameOver;
            return;
        } else if (playerCommand == "move") {
            std::string direction;
            std::cout << "Enter a direction (up, down, left, right): ";
            std::cin >> direction;

            if (!gameMap.changeRoomBasedOnDirection(direction)) {
                std::cout << "Invalid direction. Try again.\n";
            } else {
                std::cout << "Moved to a new room.\n";
                if (gameMap.roomHasEnemies(gameMap.getPlayerIndex())) {
                    std::cout << "Enemies encountered! Prepare for battle.\n";
                    // Trigger combat logic
                }
            }
        } else {
            std::cout << "Invalid command. Try again.\n";
        }
    }
}

void Game::exitGame() {
    currentState = GameState::GameOver;
}