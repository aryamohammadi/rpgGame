#pragma once
class Item;
#include "../header/character.h"
#include <string>
using std::string;
class Weapon : public Item {
public:
    enum WeaponType {
        Sword,
        Staff,
        Bow
    };

private:
    int damage;
    WeaponType weaponType;
    int speedEffect = 0;

public:
    Weapon():Item(){}
    Weapon(ItemType type, const std::string& name, Item::Grade itemGrade, const std::string& descript,
           int damage, WeaponType weaponType, double timeElapsed = -1.0);

    void useItem(Character& target) override;
    Item* clone() const override;
    WeaponType getWeaponType() const;
    int getSpeedEffect() const;
    int getDamage() const;
    void increaseDamage(int amount){damage += amount;}
    void decreaseDamage(int amount){damage -= amount;}
    friend std::ostream& operator<<(std::ostream& out, const Weapon& currentWeapon);

    std::string serialize() const;
    bool deserialize(const std::string& data);
};
