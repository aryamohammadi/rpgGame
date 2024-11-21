#pragma once
#define WEAPON_H

#include "../header/item.h"

class Weapon : public Item{
    public:
        enum WeaponType{
            Sword,
            Staff,
            Bow
        };
    private:
        int durability;
        int damage;
        WeaponType type;
    public:
        Weapon(ItemType t = WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0, int durability, int damage, WeaponType type):Item(t,name,itemGrade, descript,timeElapsed), durability(durability), damage(damage), type(type){}
        void useItem(Character& target) override{target.takeDamage(damage);}
        Item* clone() const override{
            return new Weapon(getType(), getName(),getGrade(),getDescript(), getTime(), durability, damage, type);
        }

};