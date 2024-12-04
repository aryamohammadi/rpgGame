#include <vector>
#include "item.h"
#include "../header/character.h"
class Room {
  private:
    vector<int> connectedRooms;
    vector<Character> enemies;
    vector<Item*> items;

  public:
    void removeEnemies();
    void removeItems();

    // These two functions are for the Map class to add enemies and items during map construction. They should not be used during normal gameplay
    void addEnemies();
    void addItems();
    
    // Maybe return a reference for both of these getters?
    vector<Character> getEnemies() {return enemies;} 
    vector<Item*> getItems() {return items;}

    std::string serialize() const; // For save game
    bool deserialize(const std::string& data); // For load game
};