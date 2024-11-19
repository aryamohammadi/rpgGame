#include <gtest/gtest.h>
#include "../src/MainMenu.h"
#include <sstream>

using namespace std;

class MainMenuTest : public ::testing::Test {
protected:
    MainMenu menu;
};

// Test that the main menu is displayed correctly
TEST_F(MainMenuTest, DisplayMenuTest) {
    testing::internal::CaptureStdout();
    menu.displayMenu();
    string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.find("====== Main Menu ======") != string::npos);
    ASSERT_TRUE(output.find("1. Start Game") != string::npos);
    ASSERT_TRUE(output.find("2. Settings") != string::npos);
    ASSERT_TRUE(output.find("3. Exit") != string::npos); //expect pass
}

// Test valid difficulty inputs
TEST_F(MainMenuTest, ChangeDifficultyValidInputsTest) {
    vector<string> difficulties = {"Rookie", "Elite", "Battlestar"};
    for (const auto& difficulty : difficulties) {
        istringstream input(difficulty + "\n");
        cin.rdbuf(input.rdbuf());

        testing::internal::CaptureStdout();
        menu.settings();
        string output = testing::internal::GetCapturedStdout();
        ASSERT_TRUE(output.find("Difficulty set to: " + difficulty) != string::npos); //Expect pass
    }
}

// Test invalid difficulty inputs
TEST_F(MainMenuTest, ChangeDifficultyInvalidInputsTest) {
    vector<string> invalidDifficulties = {"Hard", "123", " "};
    for (const auto& invalidInput : invalidDifficulties) {
        istringstream input(invalidInput + "\n");
        cin.rdbuf(input.rdbuf());

        testing::internal::CaptureStdout();
        menu.settings();
        string output = testing::internal::GetCapturedStdout();
        ASSERT_TRUE(output.find("Invalid Difficulty Level") != string::npos); //Expect fail
    }
}

// Test valid game option inputs
TEST_F(MainMenuTest, SelectGameOptionValidInputsTest) {
    vector<string> options = {"New Game", "Load Game"}; 
    for (const auto& option : options) {
        istringstream input(option + "\n");
        cin.rdbuf(input.rdbuf());

        testing::internal::CaptureStdout();
        menu.selectGameOption();
        string output = testing::internal::GetCapturedStdout();
        ASSERT_TRUE(output.find("You selected: " + option) != string::npos); // Expect pass
    }
}

// Test invalid game option inputs
TEST_F(MainMenuTest, SelectGameOptionInvalidInputsTest) {
    vector<string> invalidOptions = {"", "Play", "Continue", "123"};
    for (const auto& invalidInput : invalidOptions) {
        istringstream input(invalidInput + "\n");
        cin.rdbuf(input.rdbuf());

        testing::internal::CaptureStdout();
        menu.selectGameOption();
        string output = testing::internal::GetCapturedStdout();
        ASSERT_TRUE(output.find("Invalid game option") != string::npos);  //Expect Fail
    }
}

// Test handling of invalid menu choices
TEST_F(MainMenuTest, InvalidMenuChoiceTest) {
    istringstream input("5\n3\n");
    cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    int choice;
    do {
        menu.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Choice! Please Enter 1-3!" << endl;
        } else {
            switch (choice) {
                case 1:
                    menu.selectGameOption();
                    break;
                case 2:
                    menu.settings();
                    break;
                case 3:
                    cout << "Exiting Battlestar! See you soon!" << endl;
                    break;
                default:
                    cout << "Invalid Choice! Please Enter 1-3!" << endl;
            }
        }
    } while (choice != 3);

    string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.find("Invalid Choice! Please Enter 1-3!") != string::npos);
}

// Test edge cases for menu input
TEST_F(MainMenuTest, MenuInputEdgeCasesTest) {
    vector<string> edgeCases = {"abc", "", "9999999999999999999"};
    for (const auto& inputCase : edgeCases) {
        istringstream input(inputCase + "\n3\n");
        cin.rdbuf(input.rdbuf());

        testing::internal::CaptureStdout();
        int choice;
        do {
            menu.displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Choice! Please Enter 1-3!" << endl;
            } else {
                switch (choice) {
                    case 1:
                        menu.selectGameOption();
                        break;
                    case 2:
                        menu.settings();
                        break;
                    case 3:
                        cout << "Exiting Battlestar! See you soon!" << endl;
                        break;
                    default:
                        cout << "Invalid Choice! Please Enter 1-3!" << endl;
                }
            }
        } while (choice != 3);

        string output = testing::internal::GetCapturedStdout();
        ASSERT_TRUE(output.find("Invalid Choice! Please Enter 1-3!") != string::npos);
    }
}

// Test empty input for SelectGameOption
TEST_F(MainMenuTest, SelectGameOptionEmptyInputTest) {
    istringstream input("\n");
    cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    menu.selectGameOption();
    string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.find("You selected: ") != string::npos); // Expect pass
}

// Test program exit behavior
TEST_F(MainMenuTest, ExitScenarioTest) {
    istringstream input("3\n");
    cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    int choice;
    do {
        menu.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting Battlestar! See you soon!" << endl;
        }
    } while (choice != 3);

    string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.find("Exiting Battlestar! See you soon!") != string::npos); //Expect pass
}
