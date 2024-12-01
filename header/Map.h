#include <vector>
#include "Room.h"

class Map {
  private:
    vector<Room> worldRooms;
    
    void distributeEnemiesAndItems();

  public:
    Map();
    void removeEnemies(int index);
    void removeItems(int index);
    int nextRoom (string direction, int currentRoom);
    bool hasEnemies(int index);
    bool hasItems(int index);
};