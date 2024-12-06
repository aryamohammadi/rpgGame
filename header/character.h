#pragma once
#include <string> // we need to include the string library to use the string data type
#include "../header/inventory.h"  

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
        std::string characterName;
        Inventory* storage;
        Armour* armour;
        Weapon* weapon;
        int health;
        int defense; 
        int baseSpeed;
        int currentSpeed;
        bool isDead;
        int damage;
        AttackType currentAttackType;
        int experience = 0;
    public:
        void swap(Character& other) noexcept; /* noexcept is an exception specifier that tells the compiler 
                                                that this function will not throw any exceptions */
        Character(const Character& other);
        ~Character();
        Character();
        Character(const std::string& name);
        // Copy assignment operator
        Character& operator=(const Character& other);

        void setHealth(int healthOfCharacter);
        void takeDamage(int damageOnCharacter);

        friend void swap(Character*& char1,Character*& char2);
        
        void increaseHealth(int amount){health += amount;}

        void setDamage(int damage){this->damage = damage;}
        void equipWeapon(Weapon* newWeapon);
        void changeWeapon(int index); 
        void deEquipWeapon();

        void modifySpeed(int delta);
        void resetSpeed(){currentSpeed = baseSpeed;}
        int getSpeed() const {return currentSpeed;}

        void setAttackType(AttackType attackType) {currentAttackType = attackType;}
        AttackType getAttackType() const {return currentAttackType;}

        void attack(Character& target);

        bool pickUpItem(Item* item);
        
        int itemsWithName(const string& name) const;
        bool useItem(const string& itemName); //finds closest with name and returns if succesfull
        bool useItem(const string& itemName, ItemType type); //finds exact item with name and type and returns if successful
        bool useItem(int index); //uses index and returns if successful
        
        bool throwAwayItem(const string& name);
        bool throwAwayItem(const string& name, ItemType type);
        bool throwAwayItem(int index);

        std::ostream& showInventory(ostream& out) const;
        std::ostream& outputWeapons(ostream& out) const;

        std::ostream& showInventory(std::ostream& out) const;
        std::ostream& outputWeapons(std::ostream& out) const;
  
        void equipArmour(Armour* armour);
        void deEquipArmour();
        
        void increaseStorageCapacity(int amount);
        bool isStorageEmpty() const;
        void sortAlphabetically();
        void makeLatestFirst();
        void makeOldestFirst();

        // Setters
        void setHealth(int healthOfCharacter);
        void setDamage(int damageOfCharacter);
        void takeDamage(int damageOnCharacter);
        void setName(std::string name) { characterName == name; }
        void setExperience (int EXP) { experience = EXP; }

        // Getters
        int getHealth() const {return health;}
        int getDefense() const{ return defense;}
        std::string getName() const;
        int getDamage() const{return damage;}
        bool isAlive() const;
        std::string getCharacterName() const; // Returns the character's name
        friend ostream& operator<<(ostream& out, const Character& entity);
        int getExperience() { return experience; }
  
        friend std::ostream& operator<<(std::ostream& out, const Character& entity);
        bool deserialize(const std::string& data);
        std::string serialize() const;
  
        friend std::ostream& operator<<(std::ostream& out, const AttackType& type);
        friend std::istream& operator>>(std::istream& in, AttackType& type);
};
