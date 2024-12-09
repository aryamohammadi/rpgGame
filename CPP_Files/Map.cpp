#include <set>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>
#include "../header/Map.h"
#include "../header/AttackType.h"
#include "../header/character.h"
#include "../header/Room.h"
#include "../header/item.h"


Map::Map(Weapon::WeaponType typeOfWeapon) { // Constructor
  worldRooms.reserve(16);
  fillWorldRooms();
  distributeEnemiesAndItems(typeOfWeapon);
}

void Map::distributeEnemiesAndItems(Weapon::WeaponType typeOfWeapon) {
  srand(time(0));
  Character enemyToAdd("enemy1");

  // DISTRIBUTING ENEMIES
  std::set<int> selectedRooms;
  
  for (int i = 0; i < 8; i++)  { // Keep adding random room indeces until the set is 8 rooms large
  int newIndex = rand() % static_cast<int>(worldRooms.size());
    do{
      newIndex = rand() % static_cast<int>(worldRooms.size());
    }while(newIndex == 0 && selectedRooms.find(newIndex) != selectedRooms.end());
    selectedRooms.insert(newIndex); // Do not add enemies to the starting room. We don't want the player to get a nasty surprise
  }

  for (int roomIndex : selectedRooms) {
    if(roomIndex >= worldRooms.size()){
      std::cerr << "Invalid roomIndex: " << roomIndex << std::endl;
      continue;
    }
    enemyToAdd.setName("enemy1");
    // Set the enemy type as Ranged or Melee randomly. 
    if(rand() % 2 == 0){
        enemyToAdd.setAttackType(AttackType::Ranged);
    }
    else{
      enemyToAdd.setAttackType(AttackType::Melee);
    }
    // Change enemy stats based on the room index
    enemyToAdd.setDamage(roomIndex * 2); // Damage is already random from Arya's combat class
    enemyToAdd.setHealth(roomIndex * 10);
    enemyToAdd.setExperience(roomIndex * 25);
    Weapon* enemyWeapon = new Weapon(ItemType::WEAPON, "enemyweapon", "enemyweapon", roomIndex * 4, Weapon::WeaponType::Bow);
    if (enemyToAdd.getAttackType() == AttackType::Melee) {
      enemyWeapon->setWeaponType(Weapon::WeaponType::Sword);
    }
    enemyToAdd.equipWeapon(enemyWeapon);
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
      enemyToAdd.setExperience(35 * roomIndex);
      enemyWeapon = new Weapon(ItemType::WEAPON, "enemyweapon", "enemyweapon", roomIndex * 4, Weapon::WeaponType::Bow);

      if (enemyToAdd.getAttackType() == AttackType::Melee) {
        enemyWeapon->setWeaponType(Weapon::WeaponType::Sword);
      }
      enemyToAdd.equipWeapon(enemyWeapon);
      worldRooms.at(roomIndex).addEnemies(enemyToAdd);
    }

    Character superEnemy("Super Enemy");
    superEnemy.setAttackType(AttackType::Melee);
    superEnemy.setDamage(60);
    superEnemy.setHealth(300); // This might be unbalanced, but the game doesn't have to be fair
    superEnemy.setExperience(600);
    Armour* superArmour = new Armour(ItemType::ARMOUR, "superarmour", "superarmour", 30);
    enemyWeapon = new Weapon(ItemType::WEAPON, "enemyweapon", "enemyweapon", roomIndex * 4, Weapon::WeaponType::Sword);
    superEnemy.equipArmour(superArmour);
    superEnemy.equipWeapon(enemyWeapon);
    worldRooms.at(worldRooms.size() - 1).addEnemies(superEnemy);
  }

  // Give the enemies weapons depending on their type
  // Give the super enemy armour


  // DISTRIBUTING ITEMS
  selectedRooms.clear();
  for (int i = 0; i < 8; i++) { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 16);
  }
  // Distribute items to 8 rooms
  for (int roomIndex : selectedRooms) {
    // Out of 16 rooms, 8 have potions (4 with another very good potion), 4 have weapons, and 4 have armor. Have one weapon and one armor every 4 rooms (1 row on the map grid). We don't want 4 weak armors in rooms 0-3 and 8 strong enemies in rooms 8-15

    Potion* itemToAdd = new Potion(ItemType::POTION, "potion1", "red potion", 50 + (roomIndex * 10));
    worldRooms.at(roomIndex).addItems(itemToAdd);
  }

  // Distribute stronger potions in 4 of the rooms
  for (unsigned i = 0; i < 4; i++) {
    Potion* strongerItemToAdd = new Potion(ItemType::POTION, "potion2", "blue potion", 80 + (i * 20));
    worldRooms.at(i).addItems(strongerItemToAdd);
  }
  

  // DISTRIBUTING WEAPONS 
  selectedRooms.clear();
  // Selecting 3 random rooms, one room gets a super powerful weapon
  for (unsigned i = 0; i < 3; i++) {
    selectedRooms.insert(rand() % 16);
  }
  for (int roomIndex : selectedRooms) {
    Weapon* weaponToAdd = new Weapon(ItemType::WEAPON, "weapon1", "weapon1", 10 + (3 * roomIndex), typeOfWeapon);
    worldRooms.at(roomIndex).addItems(weaponToAdd);
  }
  Weapon* weaponToAdd = new Weapon(ItemType::WEAPON, "super-weapon", "super-weapon", 80, typeOfWeapon);
  worldRooms.at((rand() % 4) + 12).addItems(weaponToAdd);

  // DISTRIBUTING ARMOR
  selectedRooms.clear();

  // Selecting 3 random rooms, one room gets super-armour
  for (unsigned i = 0; i < 3; i++) {
    selectedRooms.insert(rand() % 16);
  }
  for (int roomIndex : selectedRooms) {
    Armour* armourToAdd = new Armour(ItemType::ARMOUR, "armour1", "armour1", 5 + (2 * roomIndex));
    worldRooms.at(roomIndex).addItems(armourToAdd);
  }
  Armour* armourToAdd = new Armour (ItemType::ARMOUR, "super-armour", "armour1", 60);
  worldRooms.at((rand() % 4) + 12).addItems(armourToAdd);
  
  
}

void Map::removeEnemies(int index) {
  worldRooms.at(index).removeEnemies();
}

void Map::removeItems(int index) {
  worldRooms.at(index).removeItems();
}

bool Map::roomHasEnemies(int index) {
  if (worldRooms.at(index).getEnemies().empty()) {
    return true;
  }
  else {
    return false;
  }
}

bool Map::roomHasItems(int index) {
  if (worldRooms.at(index).getItems().empty()) {
    return true;
  }
  else {
    return false;
  }
}


// return false if the direction is invalid in the 4x4 grid
// return true and change playerIndex if the direction is valid
bool Map::changeRoomBasedOnDirection(string direction) {

  for (unsigned i; i < direction.size(); i++) {
      std::transform(direction.begin(), direction.end(), direction.begin(), ::tolower); // Now we only need one if condition
  }

  if (direction == "left") {
    if (playerIndex % 4 == 0) {
      return false;
    }
    else {
      playerIndex -= 1;
      return true;
    }
  }

  if (direction == "right") {
    if (playerIndex % 4 == 3) {
      return false;
    }
    else {
      playerIndex += 1;
      return true;
    }
  }

  if (direction == "up") {
    if (playerIndex < 4) {
      return false;
    }
    else {
      playerIndex -= 4;
      return true;
    }
  }

  if (direction == "down") {
    if (playerIndex > 11) {
      return false;
    }
    else {
      playerIndex += 4;
      return true;
    }
  }


  return false;
}

// Serialize the Map
std::string Map::serialize() const {
    std::ostringstream oss;

    // Serialize the number of rooms
    oss << worldRooms.size() << "\n";

    // Serialize each room in the map
    for (const auto& room : worldRooms) {
        oss << room.serialize() << "\n";
    }

    return oss.str();
}

// Deserialize the Map
bool Map::deserialize(const std::string& data) {
    std::istringstream iss(data);
    size_t roomCount;

    // Read the number of rooms
    if (!(iss >> roomCount)) return false;

    worldRooms.clear(); // Clear existing rooms before deserialization

    std::string roomData;

    // Deserialize each room
    for (size_t i = 0; i < roomCount; ++i) {
        std::getline(iss >> std::ws, roomData); // Read serialized room data
        Room room;
        if (!room.deserialize(roomData)) {
            return false; // Fail if any room fails to deserialize
        }
        worldRooms.push_back(room);
    }

    return true;
}

void Map::fillWorldRooms(){
  for(unsigned i = 0; i < 16; i++){
    worldRooms.push_back(Room());
  }
}