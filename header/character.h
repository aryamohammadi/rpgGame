#pragma once
#define CHARACTER_H

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

    public:
        Character(const std::string& name) : characterName(name), health(100),damage(0),defense(0),isDead(false){} 

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