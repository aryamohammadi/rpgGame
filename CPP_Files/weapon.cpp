
#include "../header/weapon.h"
#include "../header/itemType.h"
void Weapon::useItem(Character& target){target.takeDamage(damage);}

Weapon::Weapon(ItemType t = ItemType::WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0, int durability, int damage, WeaponType type):Item(t,name,itemGrade, descript,timeElapsed), durability(durability), damage(damage), type(type){}

Item* Weapon::clone() const {
    return new Weapon(getType(), getName(),getGrade(),getDescript(), getTime(), durability, damage, type);
}
