#include "../CPP_Files/Map.cpp"
#include "../googletest/googletest/include/gtest/gtest.h"

TEST(TestMap, MapConstructor) {
  Map testMap(Weapon::WeaponType::Sword);
  // Testing that enemies exist in 4 rooms
  for (unsigned i = 0; i < 16; i++) {
    vector<Character*> enemiesPerRoom = testMap.returnEnemiesInRoom(i);

    for (unsigned i = 0; i < 2; i++) {
      
    }
}