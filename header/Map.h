#pragma once

#include <vector>
#include <iostream>
#include "Room.h"
#include "item.h"

class Map {
  private:
    vector<Room> worldRooms;
    int playerIndex = 0;

  public:
    Map();
    void distributeEnemiesAndItems(Weapon::WeaponType);

    void removeEnemies(int index);
    void removeItems(int index);

    bool roomHasEnemies(int index) { return !worldRooms.at(index).getEnemies().empty(); }
    bool roomHasItems(int index) { return !worldRooms.at(index).getItems().empty(); }
    bool roomHasPotions(int index) { return worldRooms.at(index).hasPotions(); }
    bool roomHasWeapons(int index) { return worldRooms.at(index).hasWeapons(); }
    bool roomHasArmour(int index) { return worldRooms.at(index).hasArmour(); }

    int getPlayerIndex() { return playerIndex; }

    bool changeRoomBasedOnDirection (string direction);

    vector<Character*> returnEnemiesInRoom (int index) { return worldRooms.at(index).getEnemies(); }
    vector<Item*> returnItemsInRoom (int index) { return worldRooms.at(index).getItems(); }
    
    int getMapSize() { return worldRooms.size(); } // This is purely for testing the Map constructor, this is not used in the actual program
    int getRoomExperience(int index) { return worldRooms.at(index).getExperience(); } // This is only for testing Room::getExperience(), this is not used in the actual program

    std::string serialize() const; // For save game
    bool deserialize(const std::string& data); //For load game
    void fillWorldRooms();
};