
#include "../header/item.h"
#include "../header/character.h"
void Weapon::useItem(Character& target){target.takeDamage(damage);}

Weapon::Weapon(ItemType type, const string& name, const string& descript, int durability, Weapon::WeaponType weaponType, double timeElapsed)
    : Item(type, name, descript, timeElapsed), damage(durability), weaponType(weaponType) { 
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
    return new Weapon(*this);
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

    weaponType = static_cast<WeaponType>(weaponTypeInt);
    return true;
}

Weapon& Weapon::operator=(const Weapon& otherWeapon){
    if(this != &otherWeapon){
        type = otherWeapon.getType();
        name = otherWeapon.getName();
        description = otherWeapon.getDescript();
        timeEarned = otherWeapon.getTime();
        weaponType = otherWeapon.getWeaponType();
        speedEffect = otherWeapon.getSpeedEffect();
        damage = otherWeapon.getDamage();
    }
    return *this;
}

std::unique_ptr<Item> Weapon::cloneUnique() const {
    return std::make_unique<Weapon>(*this);  
}
