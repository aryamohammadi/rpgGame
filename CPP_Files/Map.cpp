#include "../header/Map.h"
#include "set"

Map::Map() { // Constructor
  worldRooms.reserve(16);
}

void Map::distributeEnemiesAndItems() {
  srand(time(0));
  Character enemyToAdd("enemy1");

  // Placing enemies among 8 random rooms
  std::set<int> selectedRooms;
  for (int i = 0; i < 8; i++)  { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 16);
  }

  for (int roomIndex : selectedRooms) {
    enemyToAdd.setName("enemy1");
    if (rand() % 2 == 0) {
        enemyToAdd.setAttackType(AttackType::Ranged);
    }
    else {
      enemyToAdd.setAttackType(AttackType::Melee);
    }
    // Change enemy stats based on the room index
    enemyToAdd.setDamage(roomIndex * 2); // Damage is already random from Arya's combat class
    enemyToAdd.setHealth(roomIndex * 10);
    worldRooms.at(roomIndex).addEnemies(enemyToAdd);

    // If rand() % 2 == 1, then add a second enemy with name "enemy2" and give it the opposite type, higher attack, and lower health than enemy1
    if (rand() % 2 == 1) {
      enemyToAdd.setName("enemy2");

      if (enemyToAdd.getAttackType() == AttackType::Ranged) {
        enemyToAdd.setAttackType(AttackType::Melee); 
      }
      else {
        enemyToAdd.setAttackType(AttackType::Ranged);
      }

      enemyToAdd.setDamage(roomIndex * 3);
      enemyToAdd.setHealth(roomIndex * 7);

      worldRooms.at(roomIndex).addEnemies(enemyToAdd);
    }
  }


  // Placing items among 8 DIFFERENT random rooms
  selectedRooms.clear();
  for (int i = 0; i < 8; i++) { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 16);
  }

  for (int roomIndex : selectedRooms) {
    // Out of 16 rooms, 8 have potions (4 with another very good potion), 4 have weapons, and 4 have armor. Have one weapon and one armor every 4 rooms (1 row on the map grid). We don't want 4 weak armors in rooms 0-3 and 8 strong enemies in rooms 8-15

    Potion* itemToAdd = new Potion(POTION, "potion1", )
    worldRooms.at(roomIndex).addItems();
  }
}