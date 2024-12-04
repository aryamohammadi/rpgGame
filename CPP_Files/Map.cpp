#include "../header/Map.h"
#include "set"

Map::Map() { // Constructor
  worldRooms.reserve(16);
}

void Map::distributeEnemiesAndItems(Weapon::WeaponType typeOfWeapon) {
  srand(time(0));
  Character enemyToAdd("enemy1");

  // DISTRIBUTING ENEMIES
  std::set<int> selectedRooms;
  for (int i = 0; i < 8; i++)  { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 16);
  }

  for (int roomIndex : selectedRooms) {
    enemyToAdd.setName("enemy1");
    // Set the enemy type as Ranged or Melee randomly. 
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


  // DISTRIBUTING ITEMS
  selectedRooms.clear();
  for (int i = 0; i < 8; i++) { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 16);
  }
  // Distribute items to 8 rooms
  for (int roomIndex : selectedRooms) {
    // Out of 16 rooms, 8 have potions (4 with another very good potion), 4 have weapons, and 4 have armor. Have one weapon and one armor every 4 rooms (1 row on the map grid). We don't want 4 weak armors in rooms 0-3 and 8 strong enemies in rooms 8-15

    Potion* itemToAdd = new Potion(ItemType::POTION, "potion1", Item::Grade::COMMON, "red potion", 50 + (roomIndex * 10));
    worldRooms.at(roomIndex).addItems(itemToAdd);
  }

  // Distribute stronger potions in 4 of the rooms
  for (unsigned i = 0; i < 4; i++) {
    Potion* strongerItemToAdd = new Potion(ItemType::POTION, "potion2", Item::Grade::RARE, "blue potion", 80 + (i * 20));
    worldRooms.at(i).addItems(strongerItemToAdd);
  }
  

  // DISTRIBUTING WEAPONS 

  selectedRooms.clear();
  // Selecting 3 random rooms, one room gets a super powerful weapon
  for (unsigned i = 0; i < 3; i++) {
    selectedRooms.insert(rand() % 16);
  }
  for (int roomIndex : selectedRooms) {
    Weapon* weaponToAdd = new Weapon(ItemType::WEAPON, "weapon1", Item::Grade::UNCOMMON, "weapon1", 10 + (3 * roomIndex), typeOfWeapon);
    worldRooms.at(roomIndex).addItems(weaponToAdd);
  }
  Weapon* weaponToAdd = new Weapon(ItemType::WEAPON, "super-weapon", Item::Grade::LEGENDARY, "super-weapon", 80, typeOfWeapon);
  worldRooms.at((rand() % 4) + 12).addItems(weaponToAdd);

  // DISTRIBUTING ARMOR
  selectedRooms.clear();

  // Selecting 3 random rooms, one room gets super-armour
  for (unsigned i = 0; i < 3; i++) {
    selectedRooms.insert(rand() % 16);
  }
  for (int roomIndex : selectedRooms) {
    Armour* armourToAdd = new Armour(ItemType::ARMOUR, "armour1", Item::Grade::UNCOMMON, "armour1", 5 + (2 * roomIndex));
    worldRooms.at(roomIndex).addItems(armourToAdd);
  }

  Armour* armourToAdd = new Armour (ItemType::ARMOUR, "super-armour", Item::Grade::LEGENDARY, "armour1", 60);
  worldRooms.at((rand() % 4) + 12).addItems(armourToAdd);
}