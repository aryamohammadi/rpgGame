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

    std::string serialize() const; // For save game
    bool deserialize(const std::string& data); //For load game
};