#pragma once

#include "../header/AttackType.h"
#include <string>
class Inventory;
class Item;
class Armour;
class Character{
    private:
        std::string characterName;
        Inventory* storage;
        Armour* armour;
        Weapon* weapon;
        int health;
        int damage;
        int defense; 
        int baseSpeed;
        int currentSpeed;
        bool isDead;
        AttackType currentAttackType;
    public:
        Character(const std::string& name);
        void swap(Character& other) noexcept;/* noexcept is an exception specifier that tells the compiler 
                                                that this function will not throw any exceptions */
        Character(const Character& other);
        Character& operator=(const Character& other);
        ~Character();

        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void increaseHealth(int amount){health += amount;}

        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }

        void equipArmour(Armour* newArmour);
        void deEquipArmour();

        void equipWeapon(Weapon* newWeapon);
        void changeWeapon(int index); 

        void modifySpeed(int delta);
        void resetSpeed(){currentSpeed = baseSpeed;}
        int getSpeed() const {return currentSpeed;}

        void setAttackType(AttackType attackType) {currentAttackType = attackType;}
        AttackType getAttackType() const {return currentAttackType;}

        void attack(Character& target){weapon->useItem(target);}

        void pickUpItem(const Item& item);
        
        bool useItem(const string& itemName); //finds closest with name and returns if succesfull
        bool useItem(const string& itemName, ItemType type); //finds exact item with name and type and returns if successful
        bool useItem(int index); //uses index and returns if successful
        
        bool throwAwayItem(const string& name);
        bool throwAwayItem(const string& name, ItemType type);
        bool throwAwayItem(int index);

        string showInventory() const;
        string outputWeapons() const;
};
