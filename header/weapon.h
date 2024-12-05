#pragma once
#include "../header/item.h"
#include "../header/character.h"
#include <string>
using std::string;
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
        int speedEffect = 0;
    public:
        Weapon(ItemType type, const string& name, const string& descript, int damage, WeaponType weaponType, double timeElapsed = -1.0);
        void useItem(Character& target) override;
        Item* clone() const override;
        WeaponType getWeaponType() const {return weaponType;}
        int getSpeedEffect() const {return speedEffect;}
        int getDamage() const {return damage;}
        void increaseDamage(int amount){damage += amount;}
        void decreaseDamage(int amount){damage -= amount;}
        friend std::ostream& operator<<(ostream& out, const Weapon& currentWeapon);
        void setWeaponType(Weapon::WeaponType newType) { weaponType == newType; }
  
        std::string serialize() const;
        bool deserialize(const std::string& data);
  
        friend std::ostream& operator<<(std::ostream& out, const Weapon& currentWeapon);
};