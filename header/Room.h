#include <vector>
#include "item.h"
#include "Enemy.h"

class Room {
  private:
    vector<int> connectedRooms;
    vector<Enemy> enemies;
    vector<Item> items;

  public:
    void removeEnemies();
    void removeItems();

    // These two functions are for the Map class to add enemies and items during map construction. They should not be used during normal gameplay
    void addEnemies();
    void addItems();
};