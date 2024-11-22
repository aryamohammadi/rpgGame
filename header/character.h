#pragma once

#include "../header/AttackType.h"
#include "../header/inventory.h"

class Armour;
class Character{
    private:
        std::string characterName;
        Inventory storage;
        Armour* armour;
        int health;
        int damage;
        int defense; 
        int speed;
        bool isDead;
        AttackType currentAttackType;
    public:
        Character(const std::string& name) : characterName(name), health(100),damage(0),defense(0), speed(0), isDead(false), armour(nullptr){} 

        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }
        void equipArmour(Armour* armour);
        void deEquipArmour();

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
