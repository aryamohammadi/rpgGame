#include "../header/Map.h"
#include "set"

Map::Map() { // Constructor
  worldRooms.reserve(16);
}

void Map::distributeEnemiesAndItems() {
  srand(time(0));

  // Placing enemies among 8 random rooms
  std::set<int> selectedRooms;
  for (int i = 0; i < 8; i++)  { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 16);
  }

  for (int roomIndex : selectedRooms) {
    worldRooms.at(roomIndex).addEnemies();
  }


  // Placing items among 8 DIFFERENT random rooms
  selectedRooms.clear();
  for (int i = 0; i < 8; i++) { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 16);
  }

  for (int roomIndex : selectedRooms) {
    worldRooms.at(roomIndex).addItems();
  }
}