#pragma once

#include <vector>
#include "item.h"
#include "../header/character.h"
class Room {
  private:
    vector<Character*> enemies;
    vector<Item*> items;

  public:
    Room(){}
    ~Room();
    
    void removeEnemies();
    void removeItems();

    // These two functions are for the Map class to add enemies and items during map construction. They should not be used during normal gameplay
    void addEnemies(Character enemyToAdd);
    void addItems(Item* itemToAdd);
    
    vector<Character*> getEnemies() {return enemies;} 
    vector<Item*> getItems() {return items;}
    
    bool hasPotions();
    bool hasWeapons();
    bool hasArmour();

    int getExperience();

    std::string serialize() const; // For save game
    bool deserialize(const std::string& data); // For load game
};