#include "Map.h"
#include "set"

Map::Map() { // Constructor
  worldRooms.reserve(64);
}

void Map::distributeEnemiesAndItems() {
  srand(time(0));

  // Placing enemies among 32 random rooms
  std::set<int> selectedRooms;
  while (selectedRooms.size() < 32) {
    selectedRooms.insert(rand() % 64);
  }

  for (int roomIndex : selectedRooms) {
    worldRooms.at(roomIndex).addEnemies();
  }
}