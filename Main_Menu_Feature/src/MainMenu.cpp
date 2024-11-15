#include "MainMenu.h"

void MainMenu::displayMenu() 
{
    cout << endl << endl << endl << "====== Main Menu ======" << endl;
    cout << "1. Change Difficulty" << endl;
    cout << "2. Select Game Option" << endl;
    cout << "3. Exit" << endl << endl;
}

void MainMenu::changeDifficulty() 
{
    cout << endl<< "Enter new game difficulty (Rookie, Elite, Battlestar): " << endl;
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
    cout << "You selected: " << option << "!! Good Luck On Your Adventure!!!" << endl << endl;
}
