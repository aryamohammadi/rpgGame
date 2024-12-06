#include "../googletest/include/gtest/gtest.h"
#include "../header/SaveGame.h"
#include "../header/LoadGame.h"
#include "../header/MockGameState.h" // Mock class implementing GameState for testing

TEST(SaveGameTests, SaveSuccess) {
    // Creating a GameState sim for testing
    GameStateMock mockState;
    mockState.setSerializedData("SerializedGameStateData");

    // Save game state
    SaveGame saveGame("test_save_file.txt");
    EXPECT_TRUE(saveGame.save(mockState));

    // Verify the saved file contains the expected data
    std::ifstream testFile("test_save_file.txt");
    std::string fileContents((std::istreambuf_iterator<char>(testFile)),
                             std::istreambuf_iterator<char>());
    testFile.close();

    EXPECT_EQ(fileContents, "SerializedGameStateData");
}

TEST(SaveGameTests, SaveFileError) {
    // Attempt to save to an invalid path
    GameStateMock mockState;
    SaveGame saveGame("/invalid_path/test_save_file.txt");

    EXPECT_FALSE(saveGame.save(mockState));
}
