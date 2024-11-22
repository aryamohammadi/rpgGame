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
    public:
        Weapon(ItemType type, const string& name, Grade itemGrade, const string& descript, double timeElapsed, int damage, WeaponType weaponType);
        void useItem(Character& target) override;
        Item* clone() const override;

};