#include <gtest/gtest.h>
#include "../header/Difficulty.h"

// Test fixture for Difficulty class
class DifficultyTests : public ::testing::Test {
protected:
    Difficulty difficulty;
};

// Test default difficulty is Elite
TEST_F(DifficultyTests, DefaultDifficultyTest) {
    ASSERT_EQ(difficulty.getDifficulty(), Difficulty::Elite);
    ASSERT_DOUBLE_EQ(difficulty.getAttackMultiplier(), 1.0);
    ASSERT_DOUBLE_EQ(difficulty.getHealthModifier(), 1.0);
}

// Test setting Rookie difficulty
TEST_F(DifficultyTests, SetRookieTest) {
    difficulty.setDifficulty("Rookie");
    ASSERT_EQ(difficulty.getDifficulty(), Difficulty::Rookie);
    ASSERT_DOUBLE_EQ(difficulty.getAttackMultiplier(), 0.8);
    ASSERT_DOUBLE_EQ(difficulty.getHealthModifier(), 1.2);
}

// Test setting Battlestar difficulty
TEST_F(DifficultyTests, SetBattlestarTest) {
    difficulty.setDifficulty("Battlestar");
    ASSERT_EQ(difficulty.getDifficulty(), Difficulty::Battlestar);
    ASSERT_DOUBLE_EQ(difficulty.getAttackMultiplier(), 1.5);
    ASSERT_DOUBLE_EQ(difficulty.getHealthModifier(), 0.8);
}

// Test invalid difficulty throws an exception
TEST_F(DifficultyTests, InvalidDifficultyTest) {
    ASSERT_THROW(difficulty.setDifficulty("Hardcore"), std::invalid_argument);
}

// Test for setting difficulty to the same difficulty
TEST_F(DifficultyTests, RepeatedSameDifficultyTest) {
    difficulty.setDifficulty("Elite");
    ASSERT_EQ(difficulty.getDifficulty(), Difficulty::Elite);

    difficulty.setDifficulty("Elite");
    ASSERT_EQ(difficulty.getDifficulty(), Difficulty::Elite); 
}

// Test for large inputs
TEST_F(DifficultyTests, LongInputTest) {
    std::string longInput(1000, 'a'); // A string of 1000 'a's
    ASSERT_THROW(difficulty.setDifficulty(longInput), std::invalid_argument);
}


// Test for numbers as input
TEST_F(DifficultyTests, InvalidNumericInputTest) {
    ASSERT_THROW(difficulty.setDifficulty("123"), std::invalid_argument);
}

// Test for special characters in input
TEST_F(DifficultyTests, InvalidSpecialCharacterInputTest) {
    ASSERT_THROW(difficulty.setDifficulty("@elite!"), std::invalid_argument);
}

// Test for empty input
TEST_F(DifficultyTests, EmptyInputTest) {
    ASSERT_THROW(difficulty.setDifficulty(""), std::invalid_argument);
}

// Test for blank space
TEST_F(DifficultyTests, WhitespaceInputTest) {
    ASSERT_THROW(difficulty.setDifficulty("   "), std::invalid_argument);
}

// Test for case insensitive input
TEST_F(DifficultyTests, CaseInsensitiveInputTest) {
    difficulty.setDifficulty("ROOKIE");
    ASSERT_EQ(difficulty.getDifficulty(), Difficulty::Rookie);

    difficulty.setDifficulty("elite");
    ASSERT_EQ(difficulty.getDifficulty(), Difficulty::Elite);

    difficulty.setDifficulty("bAttleStar");
    ASSERT_EQ(difficulty.getDifficulty(), Difficulty::Battlestar);
}

