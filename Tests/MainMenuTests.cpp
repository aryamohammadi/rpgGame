#include <gtest/gtest.h>
#include "../header/MainMenu.h"

// Test fixture for MainMenu class
class MainMenuTests : public ::testing::Test {
protected:
    MainMenu mainMenu;
};

// Test menu display
TEST_F(MainMenuTests, DisplayMenuTest) {
    testing::internal::CaptureStdout();
    mainMenu.displayMenu();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("====== Main Menu ======"), std::string::npos);
    ASSERT_NE(output.find("1. Start Game"), std::string::npos);
    ASSERT_NE(output.find("2. Settings"), std::string::npos);
    ASSERT_NE(output.find("3. Exit"), std::string::npos);
}

// Test settings menu with valid difficulty input
TEST_F(MainMenuTests, SettingsValidDifficultyTest) {
    testing::internal::CaptureStdout();
    std::istringstream input("rookie\n");
    std::cin.rdbuf(input.rdbuf());

    mainMenu.settings();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("Difficulty set to Rookie!"), std::string::npos);
}

// Test settings menu with invalid difficulty input
TEST_F(MainMenuTests, SettingsInvalidDifficultyTest) {
    testing::internal::CaptureStdout();
    std::istringstream input("hardcore\n");
    std::cin.rdbuf(input.rdbuf());

    mainMenu.settings();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("Invalid Difficulty Level"), std::string::npos);
}

// Test select game option with valid input
TEST_F(MainMenuTests, SelectGameOptionValidTest) {
    std::istringstream input("new game\n"); // Simulate input
    std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout(); // Start capturing output
    mainMenu.selectGameOption();     
    std::string output = testing::internal::GetCapturedStdout(); // Get captured output

    ASSERT_NE(output.find("You selected: New Game! Good luck on your adventure!"), std::string::npos);
}

// Test select game option with invalid input
TEST_F(MainMenuTests, SelectGameOptionInvalidTest) {
    testing::internal::CaptureStdout();
    std::istringstream input("Play\n");
    std::cin.rdbuf(input.rdbuf());

    mainMenu.selectGameOption();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("Invalid game option"), std::string::npos);
}

// Test select game option with empty input
TEST_F(MainMenuTests, SelectGameOptionEmptyInputTest) {
    testing::internal::CaptureStdout();
    std::istringstream input("\n"); 
    std::cin.rdbuf(input.rdbuf());

    mainMenu.selectGameOption();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("Invalid game option"), std::string::npos);
}

// Test select game option with blank space input
TEST_F(MainMenuTests, SelectGameOptionWhitespaceInputTest) {
    testing::internal::CaptureStdout();
    std::istringstream input("   \n"); // Simulate input with only spaces
    std::cin.rdbuf(input.rdbuf());

    mainMenu.selectGameOption();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("Invalid game option"), std::string::npos);
}

// Test select game option with case-insensitive input
TEST_F(MainMenuTests, SelectGameOptionCaseInsensitiveTest) {
    testing::internal::CaptureStdout();
    std::istringstream input("NeW gAmE\n"); 
    std::cin.rdbuf(input.rdbuf());

    mainMenu.selectGameOption();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("You selected: New Game! Good luck on your adventure!"), std::string::npos);
}


// Test invalid number chosen
TEST_F(MainMenuTests, InvalidMenuChoiceTest) {
    testing::internal::CaptureStdout();
    std::istringstream input("5\n3\n");
    std::cin.rdbuf(input.rdbuf());

    int choice;
    do {
        mainMenu.displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice! Please enter a number between 1 and 3.\n";
        } else {
            switch (choice) {
                case 1:
                    mainMenu.selectGameOption();
                    break;
                case 2:
                    mainMenu.settings();
                    break;
                case 3:
                    std::cout << "Exiting Battlestar! See you soon!\n";
                    break;
                default:
                    std::cout << "Invalid choice! Please enter a number between 1 and 3.\n";
            }
        }
    } while (choice != 3);

    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_NE(output.find("Invalid choice! Please enter a number between 1 and 3."), std::string::npos);
}

// Test select game option with large input
TEST_F(MainMenuTests, SelectGameOptionLargeInputTest) {
    std::string longInput(1000, 'A'); 
    std::istringstream input(longInput + "\n");
    std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    mainMenu.selectGameOption();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("Invalid game option"), std::string::npos);
}

// Test select game option with numeric input
TEST_F(MainMenuTests, SelectGameOptionNumericInputTest) {
    testing::internal::CaptureStdout();
    std::istringstream input("123\n");
    std::cin.rdbuf(input.rdbuf());

    mainMenu.selectGameOption();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("Invalid game option"), std::string::npos);
}
