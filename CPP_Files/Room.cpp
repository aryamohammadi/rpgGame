#include "../header/Room.h"
#include <ctime>
#include <iostream>

void Room::removeEnemies() {
  
}

void Room::addEnemies() {
  srand(time(0));

  // Add either one or two enemies to the room's given vector
  Character enemyToAdd("");
  std::cout << "WARNING: ADD ATTRIBUTES TO enemyToAdd IN Room.cpp" << std::endl;
  enemies.push_back(enemyToAdd);

  if (rand() % 2 == 0) {
    Character anotherEnemytoAdd("");
    std::cout << "WARNING: ADD ATTRIBUTES TO anotherEnemytoAdd IN Room.cpp" << std::endl;
    enemies.push_back(anotherEnemytoAdd);
  }
}

void Room::addItems() {
  srand(time(0));

 // Add one, two, or three to the room's given vector.
 // 8 rooms have 1 item
 // 4 rooms have 2 items
 // 2 rooms have 3 items

  Item* item1;
  std::cout << "WARNING: ADD ATTRIBUTES TO item1 IN Room.cpp" << std::endl;
  items.push_back(item1);

  if (rand() % 2 == 0) {
    Item* item2;
    std::cout << "WARNING: ADD ATTRIBUTES TO item2 IN Room.cpp" << std::endl;
    items.push_back(item2);

    if (rand() % 8 == 0) {
    Item* item3;
    std::cout << "WARNING: ADD ATTRIBUTES TO item3 IN Room.cpp" << std::endl;
    items.push_back(item3);
  }
  }
}

// Serialize the Room
std::string Room::serialize() const {
    std::ostringstream oss;

    // Serialize connectedRooms
    oss << connectedRooms.size() << "\n";
    for (int roomID : connectedRooms) {
        oss << roomID << " ";
    }
    oss << "\n";

    // Serialize enemies
    oss << enemies.size() << "\n";
    for (const auto& enemy : enemies) {
        oss << enemy.serialize() << "\n";
    }

    // Serialize items
    oss << items.size() << "\n";
    for (const auto* item : items) {
        oss << (item ? item->serialize() : "null") << "\n";
    }

    return oss.str();
}

// Deserialize the Room
bool Room::deserialize(const std::string& data) {
    std::istringstream iss(data);
    size_t roomCount, enemyCount, itemCount;

    // Deserialize connectedRooms
    if (!(iss >> roomCount)) return false;
    connectedRooms.clear();
    for (size_t i = 0; i < roomCount; ++i) {
        int roomID;
        if (!(iss >> roomID)) return false;
        connectedRooms.push_back(roomID);
    }

    // Deserialize enemies
    if (!(iss >> enemyCount)) return false;
    enemies.clear();
    std::string enemyData;
    for (size_t i = 0; i < enemyCount; ++i) {
        std::getline(iss >> std::ws, enemyData);
        Character enemy;
        if (!enemy.deserialize(enemyData)) return false;
        enemies.push_back(enemy);
    }

    // Deserialize items
    if (!(iss >> itemCount)) return false;
    items.clear();
    std::string itemData;
    for (size_t i = 0; i < itemCount; ++i) {
        std::getline(iss >> std::ws, itemData);
        if (itemData == "null") {
            items.push_back(nullptr);
        } else {
            std::istringstream itemStream(itemData);
            int itemType;
            if (!(itemStream >> itemType)) return false;

            Item* newItem = nullptr;
            switch (static_cast<ItemType>(itemType)) {
                case ItemType::WEAPON:
                    newItem = new Weapon();
                    break;
                case ItemType::ARMOUR:
                    newItem = new Armour();
                    break;
                case ItemType::POTION:
                    newItem = new Potion();
                    break;
                default:
                    return false;
            }

            if (!newItem->deserialize(itemData)) {
                delete newItem;
                return false;
            }
            items.push_back(newItem);
        }
    }

    return true;
}