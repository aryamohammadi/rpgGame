#pragma once
#define CHARACTER_H

#include "../header/AttackType.h"
class Inventory;
class Character{
    private:
        std::string characterName;
        Inventory inventoryOfCharacter();
        int health;
        int damage;
        int defense;
        bool isDead;

    public:
        Character(const std::string& name) : characterName(name), health(100),damage(0),defense(0),isDead(false){} 

        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }
        virtual void attack() = 0;
        virtual void defend() = 0;
    
    private:
        AttackType currentAttackType; // New property to track the attack type
    
    public:
        void setAttackType(AttackType attackType) { 
        currentAttackType = attackType; 
        }

        AttackType getAttackType() const { 
        return currentAttackType; 
        }

};