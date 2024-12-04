
#include "../header/item.h"
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
std::ostream& operator<<(ostream& out, const Weapon& currentWeapon){
    out << static_cast<const Item&>(currentWeapon);
    out << "Damage: " << currentWeapon.getDamage() << std::endl;
    out << "Weapon Type: " << currentWeapon.getWeaponType() << std::endl;
    return out;
}

// Serialize Weapon object
std::string Weapon::serialize() const {
    std::ostringstream oss;
    oss << static_cast<int>(type) << "\n"              // ItemType as integer
        << name << "\n"                                // Weapon name
        << static_cast<int>(itemGrade) << "\n"         // Grade as integer
        << description << "\n"                         // Weapon description
        << timeEarned << "\n"                          // Time earned
        << damage << "\n"                              // Weapon damage
        << static_cast<int>(weaponType) << "\n"        // Weapon type as integer
        << speedEffect;                                // Speed effect
    return oss.str();
}

// Deserialize Weapon object
bool Weapon::deserialize(const std::string& data) {
    std::istringstream iss(data);
    int typeInt, gradeInt, weaponTypeInt;

    if (!(iss >> typeInt)) return false;
    if (static_cast<ItemType>(typeInt) != ItemType::WEAPON) return false;

    if (!(std::getline(iss >> std::ws, name) && iss >> gradeInt && std::getline(iss >> std::ws, description) &&
          iss >> timeEarned >> damage >> weaponTypeInt >> speedEffect)) {
        return false;
    }

    itemGrade = static_cast<Grade>(gradeInt);
    weaponType = static_cast<WeaponType>(weaponTypeInt);
    return true;
}