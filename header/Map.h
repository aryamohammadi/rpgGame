#include <vector>
#include <iostream>
#include "Room.h"
#include "item.h"

class Map {
  private:
    vector<Room> worldRooms;
    void distributeEnemiesAndItems(Weapon::WeaponType);
    int playerIndex = 0;

  public:
    Map();
    void removeEnemies(int index);
    void removeItems(int index);
    bool roomHasEnemies(int index);
    bool roomHasItems(int index);
    int getPlayerIndex() { return playerIndex; }
    bool returnRoomBasedOnDirection (string direction, int currentRoom);
};