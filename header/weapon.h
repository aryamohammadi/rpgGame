#pragma once
#include "../header/item.h"

class Weapon : public Item {
    public:
        enum WeaponType{
            Sword,
            Staff,
            Bow
        };
    private:
        int damage;
        WeaponType weaponType;
        int speedEffect;
    public:
        Weapon(ItemType type, const string& name, Grade itemGrade, const string& descript, int damage, WeaponType weaponType, double timeElapsed = -1.0);
        void useItem(Character& target) override;
        Item* clone() const override;
        WeaponType getWeaponType() const {return weaponType;}
        int getSpeedEffect() const {return speedEffect;}
        int getDamage() const {return damage;}
};