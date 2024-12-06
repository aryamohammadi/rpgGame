#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <string>
#include <stdexcept>

class Difficulty {
public:
    // Enum for difficulty levels
    enum Level { Rookie, Elite, Battlestar };

    // Constructor to initialize with a default difficulty
    Difficulty();

    // Set the difficulty level
    void setDifficulty(const std::string& difficulty);

    // Get the current difficulty level
    Level getDifficulty() const;

    // Get the attack multiplier for the current difficulty
    double getAttackMultiplier() const;

    // Get the defense multiplier for the current difficulty
    double getDefenseMultiplier() const;

    // Get the health modifier for the current difficulty
    double getHealthModifier() const;

private:
    Level currentDifficulty;

    // Helper to normalize input string to lowercase
    static std::string toLower(const std::string& str);
};

#endif // DIFFICULTY_H
