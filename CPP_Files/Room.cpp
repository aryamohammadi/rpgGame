#include "../header/Room.h"
#include "../header/AttackType.h"
#include "../header/character.h"
#include <ctime>
#include <iostream>
Room::~Room(){
    removeEnemies();
    removeItems();
}
void Room::removeEnemies() {
    for(Character* currentCharacter : enemies){
        delete currentCharacter;
        currentCharacter = nullptr;
    }
    enemies.clear();
}

void Room::removeItems() {
  for (unsigned i; i < items.size(); i++) {
    delete items[i];
    items[i] = nullptr;
  }
  items.clear();
}

void Room::addEnemies(Character enemyToAdd) {
  enemies.push_back(&enemyToAdd);
}

void Room::addItems(Item* itemToAdd) {
  items.push_back(itemToAdd);
}

int Room::getExperience() {
  int totalExperience = 0;
  for(unsigned i; i < enemies.size(); i++) {
    totalExperience += enemies[i]->getExperience();
  }
  return totalExperience;
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
        oss << enemy->serialize() << "\n";
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
        enemies.push_back(&enemy);
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