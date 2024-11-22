#include "Map.h"
#include "set"

Map::Map() { // Constructor
  worldRooms.reserve(16);
}

void Map::distributeEnemiesAndItems() {
  srand(time(0));

  // Placing enemies among 8 random rooms
  std::set<int> selectedRooms;
  while (selectedRooms.size() < 8) { // Keep adding random room indeces until the set is 8 rooms large
    selectedRooms.insert(rand() % 16);
  }

  for (int roomIndex : selectedRooms) {
    worldRooms.at(roomIndex).addEnemies();
  }
}