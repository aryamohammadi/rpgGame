#pragma once

#include <string>
#include <sstream>
#include "../header/inventory.h"
#include "../header/armour.h"
#include "../header/weapon.h"
#include "../header/AttackType.h"

using std::string;

class Character {
private:
    string characterName;
    Inventory* storage;
    Armour* armour;
    Weapon* weapon;
    int health;
    int defense;
    int baseSpeed;
    int currentSpeed;
    bool isDead;
    AttackType currentAttackType;

public:
    Character()
        : characterName("Warrior"), health(100), defense(0), baseSpeed(20), currentSpeed(20),
          isDead(false), armour(nullptr), storage(new Inventory()), weapon(nullptr) {}

    Character(const string& name)
        : characterName(name), health(100), defense(0), baseSpeed(20), currentSpeed(20),
          isDead(false), armour(nullptr), storage(new Inventory()), weapon(nullptr) {}

    ~Character() {
        delete storage;
        delete armour;
        delete weapon;
    }

    string getName() const { return characterName; }
    int getHealth() const { return health; }
    int getDefense() const { return defense; }
    bool isAlive() const { return !isDead; }

    void setHealth(int healthOfCharacter) {
        health = healthOfCharacter;
        isDead = health <= 0;
    }

    void takeDamage(int damageOnCharacter) {
        health -= damageOnCharacter;
        isDead = health <= 0;
    }

    void increaseHealth(int amount) { health += amount; }

    void equipWeapon(Weapon* newWeapon) {
        if (weapon) delete weapon; // Delete the current weapon to avoid memory leaks
        weapon = newWeapon;
    }

    void equipArmour(Armour* newArmour) {
        if (armour) delete armour; // Delete the current armour to avoid memory leaks
        armour = newArmour;
    }

    void resetSpeed() { currentSpeed = baseSpeed; }

    std::string serialize() const; // For save game
    bool deserialize(const std::string& data); // For load game
};
