#pragma once
#define CHARACTER_H

#include "../header/AttackType.h"
#include <string> // we need to include the string library to use the string data type
#include "inventory.h"  


class Character{
    private:
        std::string characterName;
        Inventory inventoryOfCharacter; // Added by Arya; changed from inventoryOfCharacter to inventoryOfCharacter because of the Inventory class
        int health;
        int damage;
        int defense;
        bool isDead;
        AttackType currentAttackType; // track the attack type

    public:
        // Constructor
        Character(const std::string& name);

        // Copy constructor
        Character(const Character& other);

        // Copy assignment operator
        Character& operator=(const Character& other);
       
        // Destructor
        virtual ~Character();
       
        /* noexcept is an exception specifier that tells the compiler that this function will not throw any exceptions */
        void swap(Character& other) noexcept;
        
        // Setters
        void setHealth(int healthOfCharacter);
        void setDamage(int damageOfCharacter);
        void takeDamage(int damageOnCharacter);

        // Getters
        std::string getCharacterName() const;
        int getHealth() const;
        int getDamage() const;
        int getDefense() const;
        AttackType getAttackType() const;
        bool isAlive() const;
        std::string getCharacterName() const; // Returns the character's name


        // Combat virtual functions to be implemented by derived classes
        virtual void attack(Character& target) = 0;
        virtual void defend() = 0;

        // Additional methods related to character status
        void setAttackType(AttackType attackType);
};