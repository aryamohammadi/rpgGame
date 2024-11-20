#pragma once
#define WEAPON_H

#include "../header/item.h"

class Weapon : public Item{
    private:
        int durability;
        int damage;
    public:
        Weapon(ItemType t = WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0, int durability, int damage):Item(t,name,itemGrade, descript,timeElapsed), durability(durability), damage(damage){}
        void useItem(Character& target) override{target.takeDamage(damage);}
        Item* clone() const override{
            return new Weapon(getType(), getName(),getGrade(),getDescript(), getTime(), durability, damage);
        }

};