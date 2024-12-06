#include "../header/Difficulty.h"
#include <algorithm>
#include <cctype>

// Constructor: Default to Elite
Difficulty::Difficulty() : currentDifficulty(Elite) {}

// Helper function to convert a string to lowercase
std::string Difficulty::toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Set the difficulty level
void Difficulty::setDifficulty(const std::string& difficulty) {
    std::string normalized = toLower(difficulty);

    if (normalized == "rookie") {
        currentDifficulty = Rookie;
    } else if (normalized == "elite") {
        currentDifficulty = Elite;
    } else if (normalized == "battlestar") {
        currentDifficulty = Battlestar;
    } else {
        throw std::invalid_argument("Invalid difficulty level: " + difficulty);
    }
}

// Get the current difficulty level
Difficulty::Level Difficulty::getDifficulty() const {
    return currentDifficulty;
}

// Get the attack multiplier for the current difficulty
double Difficulty::getAttackMultiplier() const {
    switch (currentDifficulty) {
        case Rookie: return 0.8;
        case Elite: return 1.0;
        case Battlestar: return 1.5;
        default: return 1.0;
    }
}

// Get the defense multiplier for the current difficulty
double Difficulty::getDefenseMultiplier() const {
    switch (currentDifficulty) {
        case Rookie: return 0.9;
        case Elite: return 1.0;
        case Battlestar: return 1.3;
        default: return 1.0;
    }
}

// Get the health modifier for the current difficulty
double Difficulty::getHealthModifier() const {
    switch (currentDifficulty) {
        case Rookie: return 1.2;
        case Elite: return 1.0;
        case Battlestar: return 0.8;
        default: return 1.0;
    }
}