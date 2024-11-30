
#include "../header/weapon.h"
#include "../header/character.h"
void Weapon::useItem(Character& target){target.takeDamage(damage);}

Weapon::Weapon(ItemType type, const string& name, Grade itemGrade, const string& descript, int durability, Weapon::WeaponType weaponType, double timeElapsed):Item(type,name,itemGrade, descript,timeElapsed), damage(damage), weaponType(weaponType){
    switch(weaponType){
        case Sword:
            speedEffect = 0;
            break;
        case Bow:
            speedEffect = -5;
            break;
        case Staff:
            speedEffect = -10;
            break;
        default:
            throw std::invalid_argument("WeaponType doesn't exist!");
    }
}

Item* Weapon::clone() const {
    return new Weapon(getType(), getName(),getGrade(),getDescript(), damage, weaponType, getTime());
}
std::ostream operator<<(ostream& out, const Weapon& currentWeapon){
    out << static_cast<const Item&>(currentWeapon);
    out << "Damage: " << currentWeapon.getDamage() << std::endl;
    out << "Weapon Type: " << currentWeapon.getWeaponType() << std::endl;
    return out;
}