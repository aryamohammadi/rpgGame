#include "gtest/gtest.h"
#include "../header/Game.h"
#include "../header/character.h"
#include "../header/inventory.h"
#include "Map.h"

TEST(GameTests, SerializeGameState) {
    Game game;

    // Modify the game state
    game.character.setHealth(100);
    game.inventory.addItem(new Weapon(ItemType::WEAPON, "Sword", Item::COMMON, "A basic sword", 10, Weapon::Sword, 0));

    std::string serializedState = game.serialize();

    ASSERT_FALSE(serializedState.empty());  // Check that it's not empty

    // Optionally validate the serialized string contains specific information
    ASSERT_NE(serializedState.find("Sword"), std::string::npos);
    ASSERT_NE(serializedState.find("100"), std::string::npos);
}

TEST(GameTests, DeserializeGameState) {
    Game game;

    // Create a serialized string that matches the expected format
    std::string sampleData = 
        "Warrior\n100\n0\n20\n20\n0\n0\nnull\nnull\n"
        "1\n10\nSword\n0\nA basic sword\n10\n0\n0\n"; // Mocked serialized data

    ASSERT_TRUE(game.deserialize(sampleData));  // Check if deserialization succeeds

    // Validate the game state
    EXPECT_EQ(game.character.getHealth(), 100);
    ASSERT_TRUE(game.inventory.getItem(0) != nullptr);
    EXPECT_EQ(game.inventory.getItem(0)->getName(), "Sword");
}

TEST(GameTests, DeserializeInvalidData) {
    Game game;

    // Provide invalid serialized data
    std::string invalidData = "InvalidData\nMoreInvalidData\n";

    EXPECT_FALSE(game.deserialize(invalidData));  // Ensure deserialization fails
}
