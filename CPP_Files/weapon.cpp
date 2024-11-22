
#include "../header/weapon.h"

void Weapon::useItem(Character& target){target.takeDamage(damage);}

Weapon::Weapon(ItemType t = ItemType::WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0, int durability = 100, WeaponType type = WeaponType::Sword):Item(t,name,itemGrade, descript,timeElapsed), damage(damage), type(type){}

Item* Weapon::clone() const {
    return new Weapon(getType(), getName(),getGrade(),getDescript(), getTime(), damage, type);
}
