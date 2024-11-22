#include "MainMenu.h"

void MainMenu::displayMenu() 
{
    cout << endl << endl << endl << "====== Main Menu ======" << endl;
    cout << "1. Start Game" << endl;
    cout << "2. Settings" << endl;
    cout << "3. Exit" << endl << endl;
}

void MainMenu::settings() 
{
    cout << endl<< "Choose A New Difficulty (Rookie, Elite, Battlestar): " << endl;
    string difficulty;
    cin >> difficulty;
    cout << endl << "Difficulty set to " << difficulty << "!!!" << "  You've got this!!!" << endl << endl;
}

void MainMenu::selectGameOption() 
{
    cout << "Select an option (New Game, Load Game): ";
    string option;
    cin.ignore();
    getline(cin, option);
    cout << endl << "You selected: " << option << "!! Good Luck On Your Adventure!!!" << endl << endl;
}
