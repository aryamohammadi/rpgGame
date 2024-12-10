#include "../CPP_Files/Map.cpp"
#include "../googletest/googletest/include/gtest/gtest.h"

// Map()
TEST(TestMap, MapConstructor) { 
  Map testMap;
  
  EXPECT_EQ(testMap.getMapSize(), 16);
}

// changeRoomBasedOnDirection(string direction)
TEST(TestMap, ValidRoom) {
  Map testMap;

  EXPECT_FALSE(testMap.changeRoomBasedOnDirection("up"));

  EXPECT_TRUE(testMap.changeRoomBasedOnDirection("down"));

  EXPECT_EQ(testMap.getPlayerIndex(), 4); // After moving down from index 0, the new 
                                          // player index should be 4.
}

TEST(TestMap, manipulatingEnemiesAndItems) {
  Map testMap;
  testMap.distributeEnemiesAndItems(Weapon::WeaponType::Sword);

  // Test that 8 rooms have enemies
  int count = 0;
  for (unsigned i = 0; i < 16; i++) {
    if (testMap.roomHasEnemies(i)) {
      count++;
    }
  }
  EXPECT_EQ(count, 8); // 8 rooms should have been given enemies

  // Test getting each room's experience (any integer > 0)
  int experience = 0;
  for (unsigned i = 0; i < 16; i++) {
    experience += testMap.getRoomExperience(i);
  }
  EXPECT_GT(experience, 0);

  // Test removing enemies
  for (unsigned i = 0; i < 16; i++) {
    testMap.removeEnemies(i);
  }
  count = 0;
  // Expect no room to have enemies
  for (unsigned i = 0; i < 16; i++) {
    if (testMap.roomHasEnemies(i));
    count++;
  }
  EXPECT_EQ(count, 0); 

  // Test that 
  // 4 rooms have weapons
  int count = 0;
  for (unsigned i = 0; i < 16; i++) {
    if (testMap.roomHasEnemies(i)) {
      count++;
    }
  }
  EXPECT_EQ(count, 4); // 


  // 4 rooms have armour
  // And test removing items

  // We're combining tests for 
  // Map::distributingItemsAndItems()
  // Room::removeEnemies/Items
  // Room::hasEnemies/Items
  // Room::getExperience
  // since they rely on each other 
}