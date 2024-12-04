#include <vector>
#include "Room.h"
#include "item.h"

class Map {
  private:
    vector<Room> worldRooms;
    
    void distributeEnemiesAndItems(Weapon::WeaponType);

  public:
    Map();
    void removeEnemies(int index);
    void removeItems(int index);
    int nextRoom (string direction, int currentRoom);
    bool hasEnemies(int index);
    bool hasItems(int index);
};