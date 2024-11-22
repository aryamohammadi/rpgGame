#pragma once
#define CHARACTER_H

#include "../header/AttackType.h"
#include <string> // we need to include the string library to use the string data type

class Inventory;

class Character{
    private:
        std::string characterName;
        Inventory inventoryOfCharacter; // Added by Arya; changed from inventoryOfCharacter to inventoryOfCharacter because of the Inventory class
        int health;
        int damage;
        int defense;
        bool isDead;
        AttackType currentAttackType; // New property to track the attack type

    public:
        Character(const std::string& name) : characterName(name), health(100),damage(0),defense(0),isDead(false){} 
        Character& operator=(const Character& other); // Added by Arya; copy assignment operator
        Character(const Character& other); // Added by Arya; copy constructor
        void swap(Character& other) noexcept; // Added by Arya; swap function
                                              /* noexcept is an exception specifier that tells the compiler 
                                                 that this function will not throw any exceptions */
        
        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }
        virtual void attack() = 0;
        virtual void defend() = 0;
       

        void setAttackType(AttackType attackType) { 
        currentAttackType = attackType; 
        }

        AttackType getAttackType() const { 
        return currentAttackType; 
        }

};