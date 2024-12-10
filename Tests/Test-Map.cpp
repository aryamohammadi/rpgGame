#include "../CPP_Files/Map.cpp"
#include "../googletest/googletest/include/gtest/gtest.h"

// Map()
TEST(TestMap, MapConstructor) { 
  Map testMap;
  
  EXPECT_EQ(testMap.getMapSize(), 16);
}

// changeRoomBasedOnDirection(string direction)
TEST(TestMap, RoomMovement) {
  Map testMap;

  EXPECT_FALSE(testMap.changeRoomBasedOnDirection("up"));

  EXPECT_TRUE(testMap.changeRoomBasedOnDirection("down"));

  EXPECT_EQ(testMap.getPlayerIndex(), 4); // After moving down from index 0, the new 
                                          // player index should be 4.

  EXPECT_FALSE(testMap.changeRoomBasedOnDirection("left"));

  EXPECT_TRUE(testMap.changeRoomBasedOnDirection("right"));

  EXPECT_EQ(testMap.getPlayerIndex(), 5); // After moving right from index 4, the new
                                          // player index should be 5
}

TEST(TestMap, manipulatingEnemies) {
  Map testMap;
  testMap.distributeEnemiesAndItems(Weapon::WeaponType::Sword);
  int count = 0;

  // Test that 8 rooms have enemies
  count = 0;
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

}

TEST(testMap, manipulatingItems) {
  Map testMap;
  testMap.distributeEnemiesAndItems(Weapon::WeaponType::Sword);
  int count = 0;
  // Test that 

  // 8 rooms have potions
  count = 0;
  for (unsigned i = 0; i < 16; i++) {
    if (testMap.roomHasPotions(i)) {
      count++;
    }
  }
  EXPECT_EQ(count, 8);


  // 4 rooms have weapons
  // This test has bad logic,
  // there may be a normal weapon and the superweapon in the same room
  count = 0;
  for (unsigned i = 0; i < 16; i++) {
    if (testMap.roomHasWeapons(i)) {
      count++;
    }
  }
  EXPECT_EQ(count, 4);  // 3 rooms have normal weapons, room 8-14 has the super-weapon.
  

  // 4 rooms have armour
  // This test has bad logic,
  // there may be a normal armour and the superarmour in the same room
  count = 0;
  for (unsigned i = 0; i < 16; i++) {
    if (testMap.roomHasArmour(i)) {
      count++;
    }
  }
  EXPECT_EQ(count, 4); // 3 rooms have normal armour, room 8-14 has the super-armour

  // And test removing items
  for (unsigned i = 0; i < 16; i++) {
    testMap.removeEnemies(i);
  }
  count = 0;
  // Expect no room to have enemies
  for (unsigned i = 0; i < 16; i++) {
    if (testMap.roomHasItems(i));
    count++;
  }
  EXPECT_EQ(count, 0); // 0 rooms have any items

  // We're combining tests for 
  // Map::distributingItemsAndItems()
  // Room::removeEnemies/Items
  // Room::hasEnemies/Items
  // Room::getExperience
  // since they rely on each other 
}

TEST(testMap, returningEnemiesAndItems) {
  Map testMap;
  testMap.distributeEnemiesAndItems(Weapon::WeaponType::Sword);

  int index = 0;
  while (testMap.returnEnemiesInRoom(index).size() == 0 && index < 16) {
    index++;
  }
  EXPECT_LT(index, 16);

  index = 0;
  while (testMap.returnItemsInRoom(index).size() == 0 && index < 16) {
    index++;
  }
  EXPECT_LT(index, 16);

}