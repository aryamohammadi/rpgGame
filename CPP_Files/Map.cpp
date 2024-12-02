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

// Serialize the Map
std::string Map::serialize() const {
    std::ostringstream oss;

    // Serialize the number of rooms
    oss << worldRooms.size() << "\n";

    // Serialize each room in the map
    for (const auto& room : worldRooms) {
        oss << room.serialize() << "\n";
    }

    return oss.str();
}

// Deserialize the Map
bool Map::deserialize(const std::string& data) {
    std::istringstream iss(data);
    size_t roomCount;

    // Read the number of rooms
    if (!(iss >> roomCount)) return false;

    worldRooms.clear(); // Clear existing rooms before deserialization

    std::string roomData;

    // Deserialize each room
    for (size_t i = 0; i < roomCount; ++i) {
        std::getline(iss >> std::ws, roomData); // Read serialized room data
        Room room;
        if (!room.deserialize(roomData)) {
            return false; // Fail if any room fails to deserialize
        }
        worldRooms.push_back(room);
    }

    return true;
}


