
#include "../header/weapon.h"

void Weapon::useItem(Character& target){target.takeDamage(damage);}

Weapon::Weapon(ItemType type = ItemType::WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0, int durability = 100, WeaponType weaponType = WeaponType::Sword):Item(type,name,itemGrade, descript,timeElapsed), damage(damage), weaponType(weaponType){}

Item* Weapon::clone() const {
    return new Weapon(getType(), getName(),getGrade(),getDescript(), getTime(), damage, weaponType);
}
