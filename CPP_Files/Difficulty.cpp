#include "../header/Difficulty.h"
#include <algorithm>
#include <cctype>

Difficulty::Difficulty() : currentDifficulty(Elite) {}

std::string Difficulty::toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

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

Difficulty::Level Difficulty::getDifficulty() const {
    return currentDifficulty;
}

double Difficulty::getAttackMultiplier() const {
    switch (currentDifficulty) {
        case Rookie: return 1.5;
        case Elite: return 1.0;
        case Battlestar: return 0.8;
        default: return 1.0;
    }
}

double Difficulty::getHealthModifier() const {
    switch (currentDifficulty) {
        case Rookie: return 1.2;
        case Elite: return 1.0;
        case Battlestar: return 0.8;
        default: return 1.0;
    }
}

std::string Difficulty::serialize() const {
    switch (currentDifficulty) {
        case Rookie: return "Rookie";
        case Elite: return "Elite";
        case Battlestar: return "Battlestar";
        default: return "Unknown";
    }
}

bool Difficulty::deserialize(const std::string& data) {
    std::string normalized = toLower(data);

    if (normalized == "rookie") {
        currentDifficulty = Rookie;
    } else if (normalized == "elite") {
        currentDifficulty = Elite;
    } else if (normalized == "battlestar") {
        currentDifficulty = Battlestar;
    } else {
        return false;
    }
    return true;
}
