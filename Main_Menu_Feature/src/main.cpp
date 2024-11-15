#include "MainMenu.h"

int main() 
{
    MainMenu menu;
    int choice;

    do 
    {
        menu.displayMenu();
        cout << endl << endl << "Enter your choice: ";
        cin >> choice;
      

        switch (choice) 
        {
            case 1:
                menu.changeDifficulty();
                break;
            case 2:
                menu.selectGameOption();
                break;
            case 3:
                cout << endl << endl << "Exiting Battlestar! See you soon!!" << endl << endl;
                break;
            default:
                cout << endl << "Invalid choice. Try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
