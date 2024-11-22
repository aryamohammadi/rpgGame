#pragma once
#define WEAPON_H
#include "../header/item.h"
#include "../header/character.h"

class Weapon : public Item {
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
        Weapon(ItemType t, const string& name, Grade itemGrade, const string& descript, double timeElapsed, int durability, int damage, WeaponType type);
        void useItem(Character& target) override;
        Item* clone() const override;

};