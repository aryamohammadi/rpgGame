#include "MainMenu.h"
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

void MainMenu::selectGameOption() 
{
    cout << "Select an option (New Game, Load Game): ";
   
    string option;
    getline(cin, option); // Read user input

    // Normalize input
    string normalizedOption = normalizeInput(option);
    cout << "Normalized Option: [" << normalizedOption << "]" << endl; // Debugging

    // Check if the option is valid
    if (gameOptions.find(normalizedOption) != gameOptions.end()) {
        cout << "\nYou selected: " << gameOptions[normalizedOption] << "! Good luck on your adventure!\n";
    } else {
        cout << "\nInvalid game option. Please try again.\n";
    }
}



std::string MainMenu::normalizeInput(const std::string& input) const 
{
    string normalized = input;
    transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
    return normalized;
}
