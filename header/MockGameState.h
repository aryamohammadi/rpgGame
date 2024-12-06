#ifndef MOCKGAMESTATE_H
#define MOCKGAMESTATE_H

#include "../header/GameState.h"
#include <string>
#include <iostream>

class GameStateMock : public GameState {
private:
    std::string mockData; // Data to simulate game state

public:
    // Constructor to initialize mock data
    GameStateMock(const std::string& initialData = "") : mockData(initialData) {}

    // Serialize the mock game state
    std::string serialize() const override {
        return mockData;
    }

    // Deserialize the mock game state
    bool deserialize(const std::string& data) override {
        mockData = data;
        return true; // Always succeed in this mock implementation
    }
    
    std::string getSerializedData() const {
        return mockData;
    }

    void setSerializedData(const std::string& data) {
        mockData = data;
    }
};

#endif // MOCKGAMESTATE_H
