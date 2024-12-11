#include "../header/MainMenu.h"
#include "../header/Game.h"
#include <iostream>
#include <algorithm> 

using namespace std;

void MainMenu::displayMenu() 
{
    cout << "\n\n\n====== Main Menu ======\n";
    cout << "1. Start Game\n";
    cout << "2. Settings\n";
    cout << "3. Exit\n\n";
}

bool MainMenu::setDifficulty(const std::string& difficulty) 
{
    string normalizedDifficulty = normalizeInput(difficulty);

    // Check if the normalized input matches a valid difficulty
    if (validDifficulties.find(normalizedDifficulty) != validDifficulties.end()) {
        currentDifficulty = validDifficulties[normalizedDifficulty];
        cout << "\nDifficulty set to " << currentDifficulty << "! You've got this!\n\n";
        return true;
    } else {
        cout << "\nInvalid Difficulty Level. Please try again.\n";
        return false;
    }
}

std::string MainMenu::getDifficulty() const 
{
    return currentDifficulty;
}

void MainMenu::settings() 
{
    string difficulty;
    cout << "\nChoose a New Difficulty (Rookie, Elite, Battlestar): ";
    cin >> difficulty;

    if (!setDifficulty(difficulty)) {
        cout << "Please try again.\n";
    }
}

std::string MainMenu::selectGameOption() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear leftover input

    std::cout << "Select an option (New Game, Load Game): ";
    std::string option;
    std::getline(std::cin, option); // Read full line input from the user

    // Normalize input
    std::string normalizedOption = normalizeInput(option);

    // Check if valid
    if (gameOptions.find(normalizedOption) == gameOptions.end()) {
        std::cout << "\nInvalid game option. Returning to Main Menu...\n";
        return "";
    }

    return normalizedOption;
}





std::string MainMenu::normalizeInput(const std::string& input) const 
{
    string normalized = input;
    transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    return normalized;
}