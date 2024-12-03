#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "../header/inventory.h"
#include "../header/armour.h"
#include "../header/weapon.h"
#include "../header/AttackType.h"
#include "../header/itemType.h"

using std::string;
using std::ostream;
class Inventory;
class Item;
class Armour;
class Weapon;
class Character{
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
    void swap(Character& other) noexcept;/* noexcept is an exception specifier that tells the compiler 
                                                that this function will not throw any exceptions */
    Character(const Character& other);
    // Copy assignment operator
    Character& operator=(const Character& other);
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

    bool pickUpItem(Item* item);

    int itemsWithName(const string& name) const;
    bool useItem(const string& itemName); //finds closest with name and returns if succesfull
    bool useItem(const string& itemName, ItemType type); //finds exact item with name and type and returns if successful
    bool useItem(int index); //uses index and returns if successful

    bool throwAwayItem(const string& name);
    bool throwAwayItem(const string& name, ItemType type);
    bool throwAwayItem(int index);

    std::ostream& showInventory(std::ostream& out) const;
    std::ostream& outputWeapons(std::ostream& out) const;

    void equipArmour(Armour* armour);
    void deEquipArmour();

    void increaseStorageCapacity(int amount);
    bool isStorageEmpty() const;
    void sortAlphabetically();
    void sortByAscendingGrade();
    void sortByDescendingGrade();
    void makeLatestFirst();
    void makeOldestFirst();

    // Getters
    int getHealth() const {return health;}
    int getDefense() const{ return defense;}
    std::string getName() const;
    int getDamage() const;
    bool isAlive() const;
    std::string getCharacterName() const; // Returns the character's name
    friend std::ostream& operator<<(std::ostream& out, const Character& entity);
};
