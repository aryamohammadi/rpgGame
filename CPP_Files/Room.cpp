#include "../header/Room.h"
#include "../header/AttackType.h"
#include "../header/character.h"
#include <ctime>
#include <iostream>

void Room::removeEnemies() {
  enemies.clear();
}

void Room::removeItems() {
  for (unsigned i; i < items.size(); i++) {
    delete items[i];
  }
  items.clear();
}

void Room::addEnemies(Character enemyToAdd) {
  enemies.push_back(enemyToAdd);
}

void Room::addItems(Item* itemToAdd) {
  items.push_back(itemToAdd);
}

int Room::getExperience() {
  int totalExperience = 0;
  for(unsigned i; i < enemies.size(); i++) {
    totalExperience += enemies[i].getExperience();
  }
}