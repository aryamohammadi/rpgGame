#include "gtest/gtest.h"
#include "../header/LoadGame.h"
#include "../header/SaveGame.h"
#include "../header/MockGameState.h" // Mock class implementing GameState for testing

TEST(LoadGameTests, LoadSuccess) {
    // Create a test save file
    std::ofstream testFile("test_load_file.txt");
    testFile << "SerializedGameStateData";
    testFile.close();

    // Mock GameState for testing
    GameStateMock mockState;

    // Load game state
    LoadGame loadGame("test_load_file.txt");
    EXPECT_TRUE(loadGame.load(mockState));

    // Verify the mock state contains the expected data
    EXPECT_EQ(mockState.getSerializedData(), "SerializedGameStateData");
}

TEST(LoadGameTests, LoadFileError) {
    // Attempt to load from a non-existent file
    GameStateMock mockState;
    LoadGame loadGame("nonexistent_file.txt");

    EXPECT_FALSE(loadGame.load(mockState));
}
