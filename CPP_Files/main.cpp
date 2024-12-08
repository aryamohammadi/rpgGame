s#include "../header/Game.h"
#include <iostream>
int main() {
    Game game; // Instantiate the Game
    game.run(); // Start the game loop
    return 0;


    // Previous version of main.cpp, kept here in case it needs to be changed back
    /*
    MainMenu menu;
    int choice;

    do {
        menu.displayMenu();
        cout << "Enter your choice: ";

        // Input validation for numeric choice
        if (!(cin >> choice)) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "\nInvalid choice! Please enter a number between 1 and 3.\n";
            continue;
        }

        // Handle menu choices
        switch (choice) {
            case 1: {
                cin.ignore(); // Clear newline left in buffer
                menu.selectGameOption();
                break;
            }
            case 2: {
                menu.settings(); // Use the `settings` function for difficulty selection
                break;
            }
            case 3:
                cout << "\nExiting Battlestar! See you soon!\n\n\n"; // Will Exit the program
                break;
            default:
                cout << "\nInvalid choice! Please enter a number between 1 and 3.\n";
        }
    } while (choice != 3); // Exit the loop when the user selects option 3
    */
}
