#pragma once
#include <vector>
#include <iostream>
#include "Room.h"
#include "item.h"

class Map {
  private:
    std::vector<Room> worldRooms;
    void distributeEnemiesAndItems(Weapon::WeaponType);
    int playerIndex = 0;
    void fillWorldRooms();
  public:
    Map(Weapon::WeaponType typeOfWeapon);
    void removeEnemies(int index);
    void removeItems(int index);
    bool roomHasEnemies(int index);
    bool roomHasItems(int index);
    int getPlayerIndex() { return playerIndex; }
    bool changeRoomBasedOnDirection (std::string direction);
    std::vector<Character*> returnEnemiesInRoom (int index) { return worldRooms.at(index).getEnemies(); }
    std::vector<Item*> returnItemsInRoom (int index) { return worldRooms.at(index).getItems(); }

    std::string serialize() const; // For save game
    bool deserialize(const std::string& data); //For load game
    bool returnRoomBasedOnDirection(string direction, int currentRoom);
};