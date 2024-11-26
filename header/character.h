#pragma once
#define CHARACTER_H
#include <string> // we need to include the string library to use the string data type
#include "inventory.h"  

#include "../header/AttackType.h"

#include "../header/weapon.h"
#include "../header/armour.h"
#include "../header/inventory.h"
class Character{
    private:
        std::string characterName;
        Inventory storage;
        Armour* armour;
        int health;
        int damage;
        int defense; 
        int speed = 0;
        bool isDead;
        AttackType currentAttackType; // track the attack type

    public:
        // Constructor
        Character(const std::string& name);

        // Copy constructor
        Character(const Character& other);

        // Copy assignment operator
        Character& operator=(const Character& other);

        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }

        // Consider having the combat class handle damage calculations based on the two Character parameters passed to it
        Character(const std::string& name) : characterName(name), health(100),damage(0),defense(0),isDead(false){} 
        void swap(Character& other) noexcept; // Added by Arya; swap function
                                              /* noexcept is an exception specifier that tells the compiler 
                                                 that this function will not throw any exceptions */
        
        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }
        void equipArmour(Armour* armour){
            if(this->armour == nullptr){
                this->armour = armour;
            }
            else{
                if(storage.itemFound(*armour) != -1){
                    storage.removeItem(*armour);
                }
                this->armour = armour;
            }
            defense += armour->getArmourStat();
        }
        void deEquipArmour(){
            
            storage.addItem(armour);
        }

        virtual void attack() = 0;
        virtual void defend() = 0;
       
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