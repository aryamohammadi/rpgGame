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
        Item* weapon;
        int health;
        int damage;
        int defense; 
        int speed;
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
        void setDamage(int damageOfCharacter){ damage = damageOfCharacter; }
        void takeDamage(int damageOnCharacter){ health-= damageOnCharacter; }
        void equipArmour(Armour* armour);
        void deEquipArmour();
    
    public:
        void setAttackType(AttackType attackType) { 
            currentAttackType = attackType; 
        }

        AttackType getAttackType() const { 
            return currentAttackType; 
        }

};
