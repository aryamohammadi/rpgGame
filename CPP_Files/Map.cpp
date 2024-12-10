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

Map::Map() { // Constructor
  worldRooms.reserve(16);
  // Push back 16 dummy rooms, but don't give them enemies or items, just run the Room constructor
  for (unsigned i = 0; i < 16; i++) {
    Room newRoom;
    worldRooms.push_back(newRoom);
  }
  // distributeEnemiesAndItems(typeOfWeapon);
}

void Map::distributeEnemiesAndItems(Weapon::WeaponType typeOfWeapon) {
  // srand(time(0));
  srand(2);
  int randNum;

  // std::set<int> selectedRooms;
  vector<int> selectedRooms;
  // Re-write this logic to not use a set, but a vector
  // because inserting duplicates doesn't re-call rand()
  // make sure the indices are randomly ordered

  // Populate selectedRooms with 8 random numbers 0-15
  randNum = ((rand() % 15) + 1);
  for (unsigned i = 0; i < 8; i++) {
    int present = count(selectedRooms.begin(), selectedRooms.end(), randNum);
    while (present != 0) {
      // If selectedRooms does not contain randNum, this function will set
      // present equal to 0
      present = count(selectedRooms.begin(), selectedRooms.end(), randNum); 
      randNum = ((rand() % 15) + 1);
    }
    selectedRooms.push_back(randNum);
  }

  // NOTES FROM 11:09 PM 12-8-24
  // I'm running gdb, incrementing through this [for (int roomIndex : selectedRooms)] loop, to find where the segfault is. 
  // The for loop in the Map() constructor pushing back empty Rooms was pretty nice. That way worldRooms has a set size, which is more than .reserve(16) can say, the miserable failure
  // Look at me, lahdee da da, going line by line with gdb, actually using the tools we learned in class, only in an actually challenging and unique environment
  // They should have us do this in class, use our tools on our own code. That would make the labs much more interesting and engaging. At least with B-Trees I knew the purpose of what I was supposed to be doing. Even what I WAS doing, meandering through my nonfunctional code, had a purpose at the end of it all, a better understanding of debugging and how my thought process succeeded and failed. Not that I remember much of it

  // IF GDB FAILS, LOAD THE BREAKPOINTS IN breakpoints.txt with "source breakpoints.txt"


  // DISTRIBUTING ENEMIES
  Character enemyToAdd("enemy1");
  // For 8 random rooms, add 1 or 2 enemies with proper stats
  for (int roomIndex : selectedRooms) {
    if(roomIndex >= worldRooms.size()){
      std::cout << "Invalid roomIndex: " << roomIndex << std::endl;
      continue;
    }
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
  }

    Character superEnemy("Super Enemy");
    superEnemy.setAttackType(AttackType::Melee);
    superEnemy.setDamage(60);
    superEnemy.setHealth(300); // This might be unbalanced, but the game doesn't have to be fair
    superEnemy.setExperience(600);
    Armour* superEnemyArmour = new Armour(ItemType::ARMOUR, "superarmour", "superarmour", 30);
    Weapon* superEnemyWeapon = new Weapon(ItemType::WEAPON, "enemyweapon", "enemyweapon", 60, Weapon::WeaponType::Sword);
    superEnemy.equipArmour(superEnemyArmour);
    superEnemy.equipWeapon(superEnemyWeapon);
    worldRooms.at(worldRooms.size() - 1).addEnemies(superEnemy);


  // DISTRIBUTING ITEMS

  selectedRooms.clear();
  // Populate selectedRooms with 8 random numbers from 0-14
  randNum = ((rand() % 15));
  for (unsigned i = 0; i < 8; i++) {
    // Look at the initial room indices selection for details about this function
    int present = count(selectedRooms.begin(), selectedRooms.end(), randNum);
    while (present != 0) {
      present = count(selectedRooms.begin(), selectedRooms.end(), randNum);
      randNum = ((rand() % 15));
    }
    selectedRooms.push_back(randNum);
  }

  // Distribute items to 8 rooms
  for (int roomIndex : selectedRooms) {
    Potion* itemToAdd = new Potion(ItemType::POTION, "potion1", "red potion", 50 + (roomIndex * 10));
    worldRooms.at(roomIndex).addItems(itemToAdd);
  }

  // Distribute stronger potions in 4 of the rooms
  for (int i = 0; i < 4; i++) {
    int roomIndex = selectedRooms.at(i);
    Potion* strongerItemToAdd = new Potion(ItemType::POTION, "potion2", "blue potion", 80 + (roomIndex * 20));
    worldRooms.at(roomIndex).addItems(strongerItemToAdd);
  }
  

  // DISTRIBUTING WEAPONS 
  selectedRooms.clear();
  // Populate selectedRooms with 3 random numbers 0-14
  // Index 8-14 will have a SuperWeapon
  randNum = ((rand() % 15));
  for (unsigned i = 0; i < 4; i++) {
    // Look at the initial room indices selection for details about this function
    int present = count(selectedRooms.begin(), selectedRooms.end(), randNum);
    while (present != 0) {
      present = count(selectedRooms.begin(), selectedRooms.end(), randNum); 
      randNum = ((rand() % 15));
    }
    selectedRooms.push_back(randNum);
  }

  for (int roomIndex : selectedRooms) {
    Weapon* weaponToAdd = new Weapon(ItemType::WEAPON, "weapon1", "weapon1", 10 + (3 * roomIndex), typeOfWeapon);
    worldRooms.at(roomIndex).addItems(weaponToAdd);
  }

  // SUPER-WEAPON SECTION
  Weapon* superWeapon = new Weapon(ItemType::WEAPON, "super-weapon", "super-weapon", 80, typeOfWeapon);
  // Super weapon goes in one of the rooms 8-14
  randNum = (rand() % 7) + 8;
  while (!worldRooms.at(randNum).hasWeapons()) {
    randNum = (rand() % 7) + 8;
  }
  worldRooms.at(randNum).addItems(superWeapon); 


  // DISTRIBUTING ARMOR
  selectedRooms.clear();
  // Populate selectedRooms with 3 random numbers 0-14
  // Index 8-14 will have a SuperArmour
  randNum = ((rand() % 15));
  for (unsigned i = 0; i < 4; i++) {
    // Look at the initial room indices selection for details about this function
    int present = count(selectedRooms.begin(), selectedRooms.end(), randNum);
    while (present != 0) {
      present = count(selectedRooms.begin(), selectedRooms.end(), randNum); 
      randNum = ((rand() % 15));
    }
    selectedRooms.push_back(randNum);
  }

  for (int roomIndex : selectedRooms) {
    Armour* armourToAdd = new Armour(ItemType::ARMOUR, "armour1", "armour1", 5 + (2 * roomIndex));
    worldRooms.at(roomIndex).addItems(armourToAdd);
  }

  // SUPER-ARMOUR SECTION
  Armour* superArmour = new Armour (ItemType::ARMOUR, "super-armour", "armour1", 60);

  randNum = (rand() % 7) + 8;
  while (!worldRooms.at(randNum).hasArmour()) {
    randNum = (rand() % 7) + 8;
  }
  worldRooms.at(randNum).addItems(superArmour); // rooms 8-14 inclusive



  return;
}

void Map::removeEnemies(int index) {
  worldRooms.at(index).removeEnemies();
}

void Map::removeItems(int index) {
  worldRooms.at(index).removeItems();
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
