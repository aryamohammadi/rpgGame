#pragma once
#include <string> // we need to include the string library to use the string data type
#include "inventory.h"  

#include "../header/AttackType.h"
#include "../header/itemType.h"
#include <string>
using std::string;
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
        AttackType currentAttackType;
    public:
        void swap(Character& other) noexcept;/* noexcept is an exception specifier that tells the compiler 
                                                that this function will not throw any exceptions */
        Character(const Character& other);
        ~Character();
        Character(const std::string& name);
        // Copy assignment operator
        Character& operator=(const Character& other);

        void setHealth(int healthOfCharacter){ 
            health = healthOfCharacter;
            isDead = health <= 0; 
        }
        void takeDamage(int damageOnCharacter){ 
            health-= damageOnCharacter; 
            isDead = health <= 0;
        }

        friend void swap(Character* char1,Character* char2){
            Character* temp = char1;
            char1 = char2;
            char2 = temp;
        }
        
        void increaseHealth(int amount){health += amount;}
  
        void equipWeapon(Weapon* newWeapon);
        void changeWeapon(int index); 

        void modifySpeed(int delta);
        void resetSpeed(){currentSpeed = baseSpeed;}
        int getSpeed() const {return currentSpeed;}

        void setAttackType(AttackType attackType) {currentAttackType = attackType;}
        AttackType getAttackType() const {return currentAttackType;}

        void attack(Character& target);

        void pickUpItem(const Item& item);
        
        int itemsWithName(const string& name) const;
        bool useItem(const string& itemName); //finds closest with name and returns if succesfull
        bool useItem(const string& itemName, ItemType type); //finds exact item with name and type and returns if successful
        bool useItem(int index); //uses index and returns if successful
        
        bool throwAwayItem(const string& name);
        bool throwAwayItem(const string& name, ItemType type);
        bool throwAwayItem(int index);

        std::ostream& showInventory(ostream& out) const;
        std::ostream& outputWeapons(ostream& out) const;
  
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
        AttackType getAttackType() const;
        bool isAlive() const;
        std::string getCharacterName() const; // Returns the character's name
        friend ostream& operator<<(ostream& out, const Character& entity);
};
