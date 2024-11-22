#pragma once
#define CHARACTER_H
#include <string> // we need to include the string library to use the string data type

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
        AttackType currentAttackType; // New property to track the attack type

    public:
        Character(string name) : characterName(name), inventoryOfCharacter(), health(100),damage(0),defense(0),isDead(false){} 

        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }

        // Consider having the combat class handle damage calculations based on the two Character parameters passed to it
        Character(const std::string& name) : characterName(name), health(100),damage(0),defense(0),isDead(false){} 
        Character& operator=(const Character& other); // Added by Arya; copy assignment operator
        Character(const Character& other); // Added by Arya; copy constructor
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
       

        void setAttackType(AttackType attackType) { 
        currentAttackType = attackType; 
        }

        AttackType getAttackType() const { 
        return currentAttackType; 
        }

};