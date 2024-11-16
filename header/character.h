#pragma once
#define CHARACTER_H
#include "inventory.h"

class Character{
    private:
        std::string characterName;
        Inventory inventoryOfCharacter;
        int health;
        int damage;
        int defense;
        bool isDead;
        

    public:
        Character(string name) : characterName(name), inventoryOfCharacter(), health(100),attack(0),defense(0),isDead(false){} 

        void setHealth(int healthOfCharacter){ health = healthOfCharacter; }
        void setAttack(int attackOfCharacter){ attack = attackOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }
        virtual void attack() = 0;
        virtual void defend() = 0;

};