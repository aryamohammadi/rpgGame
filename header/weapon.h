#pragma once
#include "../header/item.h"

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
    int speedEffect;

public:
    Weapon(ItemType type = ItemType::WEAPON, const string& name = "Training Sword", Grade itemGrade = COMMON, const string& descript = "",
           int damage = 10, WeaponType weaponType = Sword, int speedEffect = 0, double timeElapsed = -1.0);

    void useItem(Character& target) override;
    Item* clone() const override;
    WeaponType getWeaponType() const;
    int getSpeedEffect() const;
    int getDamage() const;
    friend std::ostream& operator<<(std::ostream& out, const Weapon& currentWeapon);

    std::string serialize() const override;
    bool deserialize(const std::string& data) override;
};
