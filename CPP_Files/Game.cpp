#include "../header/Game.h"
#include <sstream>
#include <filesystem>
#include <limits>


Game::Game() : currentState(GameState::MainMenu), player("Hero"), difficulty() {}

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
        << inventory.serialize();
    return oss.str();
}

bool Game::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string playerData, difficultyData, inventoryData;

    if (!std::getline(iss, playerData) ||
        !std::getline(iss, difficultyData) ||
        !std::getline(iss, inventoryData)) {
        return false;
    }

    return player.deserialize(playerData) &&
           difficulty.deserialize(difficultyData) &&
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

    while (true) {
        std::cout << "\nWhat would you like to do? (Type 'save' to save progress): ";
        std::string input;
        std::getline(std::cin >> std::ws, input);

        input = normalizeInput(input);

        if (input == "save") {
            while (true) {
                std::cout << "\nPress 1 to Save and Continue or Press 2 to Save and Return to the Main Menu: ";
                std::getline(std::cin, input);
                input = normalizeInput(input);

                if (input == "1") {
                    saveGame("savefile.json");
                    std::cout << "Game saved! Continuing...\n";
                    break;
                } else if (input == "2") {
                    saveGame("savefile.json");
                    std::cout << "Game saved! Returning to the Main Menu...\n";
                    currentState = GameState::MainMenu;
                    return;
                } else {
                    std::cout << "Invalid choice! Please enter 1 or 2.\n";
                }
            }
        } else if (input == "exit") {
            std::cout << "Exiting the game. Goodbye!\n";
            currentState = GameState::GameOver;
            return;
        } else {
            std::cout << "You chose to " << input << ". Keep going!\n";
        }
    }
}

void Game::exitGame() {
    currentState = GameState::GameOver;
}

std::string Game::normalizeInput(const std::string& input) const {
    std::string normalized = input;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    auto start = normalized.find_first_not_of(' ');
    auto end = normalized.find_last_not_of(' ');
    return (start == std::string::npos) ? "" : normalized.substr(start, end - start + 1);
}
