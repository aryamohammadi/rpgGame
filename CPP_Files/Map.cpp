Clutch
clutch0777_91649
Online

Dream Team did one thing wrong — 11/5/24, 3:41 PM
Hi Ryan. I will call you on discord at 4 PM
Clutch — 11/5/24, 3:41 PM
im on campus in the lib i just saw ur messages
have u accepted the lab yet
Dream Team did one thing wrong — 11/5/24, 3:45 PM
No not yet, I'm going to do that right now
I can come to the library if you prefer
Clutch — 11/5/24, 3:50 PM
yeah if u dont mind
Dream Team did one thing wrong — 11/5/24, 3:51 PM
Alright, see you when I get there
You said it's not a very involved lab, right?
Clutch — 11/5/24, 3:52 PM
eh idk forsure i just know we all have to be using the same unit test file
Dream Team did one thing wrong — 11/8/24, 12:53 PM
Hi Ryan. It turns out that Lab 5 is not due until next week, not this Friday, so we don't need to rush to complete it today, if you hadn't already.
Clutch — 11/8/24, 2:21 PM
Yea my bad idk how I didn’t know that
Dream Team did one thing wrong — 11/8/24, 2:24 PM
No problem, I forgot that myself
Dream Team did one thing wrong — 11/11/24, 6:47 PM
Hi Ryan. Are you okay with changing the Navigation Diagram with the feedback Josh gave us?
Dream Team did one thing wrong — 11/12/24, 8:06 AM
Hi Ryan, this week we will need to work on our sprint tasks. Do you know what you need to do?
Dream Team did one thing wrong — 11/12/24, 4:48 PM
Good evening Ryan. May I call you tonight at 8 PM to discuss the project and what both of our next tasks are?
Dream Team did one thing wrong — 11/12/24, 8:54 PM
Hi Ryan, I'm very sorry that I missed the call. I can let you know what you can do next, but do you have a good idea already?
If you would like, I can call you right now to clear up any information.
Clutch — 11/12/24, 9:44 PM
youre good i know what needs to be done
Dream Team did one thing wrong — 11/12/24, 9:57 PM
Alright, sounds good
Dream Team did one thing wrong — 11/14/24, 6:21 PM
Hi Ryan. How is your Navigation Diagram going?
Clutch — 11/14/24, 11:46 PM
Trash I think need help
Dream Team did one thing wrong — 11/15/24, 6:07 AM
You can just copy my tests and code for rectangle.cpp/hpp, test.cpp, and main.yml, they're not that long. I can send them to you if you need them. 
Better yet, copy Matthews, he finished them completely
Clutch — 11/15/24, 12:16 PM
ok thank god
what time is our demo
Dream Team did one thing wrong — 11/15/24, 12:16 PM
3:20
with Ryan Quil
Clutch — 11/15/24, 12:18 PM
oh shit okay ill copy it right now is everything good to go? and is there anything else i need to do in the lab?
Dream Team did one thing wrong — 11/15/24, 12:20 PM
Only one person needs to have the branches done
I will have them done
Then, everything will be good to go
You can work on the sprint tasks or your other work
Clutch — 11/15/24, 12:27 PM
so what do i need to lab wise can u give me a quick run down
like do i still create a branch or no im confused
Dream Team did one thing wrong — 11/15/24, 12:33 PM
No you don't
For the lab, I will be showcasing our passing and failing tests branches, describing them, and then showing a pull request to main
Clutch — 11/15/24, 12:43 PM
so what do i even need to do?
I dont need to push anything? I literally havent done a thing
Dream Team did one thing wrong — 11/15/24, 12:47 PM
You don't need to do anything
I asked a grader
Clutch — 11/15/24, 12:51 PM
dang okay thx
Dream Team did one thing wrong — 11/16/24, 12:55 PM
Hi Ryan. I have a friend in Data Science who will be taking CS 105 next quarter. May I give him your username so he can ask you questions about the class and professor?
Clutch — 11/17/24, 3:34 PM
yea idc
Dream Team did one thing wrong — 11/17/24, 3:36 PM
Alright lol
Clutch — 11/22/24, 2:18 PM
MainMenu:

The MainMenu class is responsible for displaying the menu and handling user interaction like selecting game options or difficulty. Follows the SRP as the class is focused solely on managing the user interface of the main menu. It doesn’t handle gameplay, difficulty logic, or other unrelated functionality. The MainMenu class also follows the OCP as it can be extended by adding new menu options or behaviors without modifying its existing methods. The MainMenu class operates independently of the Difficulty class. It uses a simple setDifficulty method internally and does not depend on the concrete implementation of Difficulty. This separation ensures that MainMenu does not violate DIP. Adhering to the SOLID principles has made it so that integration with the main branch and other features of the program should be very straight forward.



Difficulty:

The Difficulty class manages the game's difficulty level, which includes modifiers for attack, defense, and health. The Difficulty class is self-contained and does not depend on any other class. 
This class complies with SRP as it focuses only on encapsulating the logic for difficulty levels and their associated multipliers. It doesn’t handle user input, gameplay, or display logic. This design aligns with DIP because it does not tightly couple itself to higher-level modules like MainMenu. Adhering to the SOLID principles made it so it will be easy for the members of our team to utilize the difficulty class in other features.
You missed a call from Dream Team did one thing wrong that lasted 3 minutes. — 12/1/24, 9:59 AM
You missed a call from Dream Team did one thing wrong that lasted 3 minutes. — 12/1/24, 11:05 AM
You missed a call from Dream Team did one thing wrong that lasted 2 minutes. — 12/1/24, 11:16 AM
Dream Team did one thing wrong — 12/4/24, 11:59 PM
I'm sorry about the delay, here are my CS 100 Notes up to today's discussion, it's in the folder
https://drive.google.com/drive/folders/1DToD0H-uiGUbNCcDq4TqlpZJVGWMJhZ8?usp=sharing
Google Drive: Sign-in
Access Google Drive with a Google account (for personal use) or Google Workspace account (for business use).
Dream Team did one thing wrong — Yesterday at 12:00 AM
If you care, the other notes are up for copying, although they're mostly useless probably
Dream Team did one thing wrong — Today at 3:24 PM
#include "../header/Map.h"
#include "set"

Map::Map(Weapon::WeaponType typeOfWeapon) { // Constructor
  worldRooms.reserve(16);
  distributeEnemiesAndItems(typeOfWeapon);
}

void Map::distributeEnemiesAndItems(Weapon::WeaponType typeOfWeapon) {
  srand(time(0));
  Character enemyToAdd("enemy1");

  // DISTRIBUTING ENEMIES
  std::set<int> selectedRooms;
  for (int i = 0; i < 8; i++)  { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 15 + 1); // Do not add enemies to the starting room. We don't want the player to get a nasty surprise
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
      Weapon* enemyWeapon = new Weapon(ItemType::WEAPON, "enemyweapon", "enemyweapon", roomIndex * 4, Weapon::WeaponType::Bow);

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
    Weapon* enemyWeapon = new Weapon(ItemType::WEAPON, "enemyweapon", "enemyweapon", roomIndex * 4, Weapon::WeaponType::Sword);
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
... (145 lines left)
Collapse
Map.cpp
8 KB
#include <vector>
#include <iostream>
#include "Room.h"
#include "item.h"

class Map {
Expand
Map.h
1 KB
#include "../header/Room.h"
#include "../header/AttackType.h"
#include "../header/character.h"
#include <ctime>
#include <iostream>
Expand
Room.cpp
4 KB
#include <vector>
#include "item.h"
#include "../header/character.h"
class Room {
  private:
    vector<int> connectedRooms;
Expand
Room.h
1 KB
﻿
May Allah save the Palestinians from the destruction of their lives at the hands of the israeli oppressors.
Dream Team did one thing wrong
dream_team_did_one_thing_wrong
Mario/&/Luigi/RPG
 
"If only I could see my brothers coming towards me. My brothers are those who believe in me without seeing me."
- Prophet Muhammad, peace and blessings be upon him
[Sahih Muslim 249a]
#include "../header/Map.h"
#include "set"

Map::Map(Weapon::WeaponType typeOfWeapon) { // Constructor
  worldRooms.reserve(16);
  distributeEnemiesAndItems(typeOfWeapon);
}

void Map::distributeEnemiesAndItems(Weapon::WeaponType typeOfWeapon) {
  srand(time(0));
  Character enemyToAdd("enemy1");

  // DISTRIBUTING ENEMIES
  std::set<int> selectedRooms;
  for (int i = 0; i < 8; i++)  { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 15 + 1); // Do not add enemies to the starting room. We don't want the player to get a nasty surprise
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
      Weapon* enemyWeapon = new Weapon(ItemType::WEAPON, "enemyweapon", "enemyweapon", roomIndex * 4, Weapon::WeaponType::Bow);

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
    Weapon* enemyWeapon = new Weapon(ItemType::WEAPON, "enemyweapon", "enemyweapon", roomIndex * 4, Weapon::WeaponType::Sword);
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
Map.cpp
8 KB