#include "MainMenu.h"
#include <iostream>
#include <limits> // For numeric_limits

using namespace std;

int main() 
{
    MainMenu menu;
    int choice;

    do 
    {
        menu.displayMenu();
        cout << endl << endl << "Enter your choice: ";

        // Input validation
        if (!(cin >> choice)) 
        {
            // Clear the error state of cin
            cin.clear();

            // Ignore invalid input until a newline is encountered
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Print an error message and continue the loop
            cout << endl << "Invalid Choice! Please Enter 1-3!" << endl;
            continue;
        }

        // Handle valid input
        switch (choice) 
        {
            case 1:
                menu.selectGameOption();
                break;
            case 2:
                menu.settings();
                break;
            case 3:
                cout << endl << endl << "Exiting Battlestar! See you soon!!" << endl << endl;
                break;
            default:
                cout << endl << "Invalid Choice! Please Enter 1-3!" << endl;
        }
    } while (choice != 3);

    return 0;
}
