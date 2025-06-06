#include "../header/item.h"
#include "../header/character.h"
    Armour::Armour(ItemType t, const string& name, const string& descript, int stat, double timeElapsed):Item(t,name,descript,timeElapsed), armourStat(stat){}

    void Armour::useItem(Character& target){
        target.equipArmour(this);
    }

    Item* Armour::clone() const{
        return new Armour(*this);
    }

std::ostream& operator<<(std::ostream& out, const Armour& currentArmour){
    out << static_cast<const Item&>(currentArmour);
    out << "Armour Stat: " << currentArmour.getArmourStat() << std::endl;
    return out;
}

// Override serialize
std::string Armour::serialize() const {
    std::ostringstream oss;
    oss << static_cast<int>(type) << "\n" // ItemType as integer
        << name << "\n"
        << description << "\n"
        << timeEarned << "\n"
        << armourStat; // Armour stat
    return oss.str();
}

// Override deserialize
bool Armour::deserialize(const std::string& data) {
    std::istringstream iss(data);
    int typeInt, gradeInt;

    if (!(iss >> typeInt)) return false;
    if (static_cast<ItemType>(typeInt) != ItemType::ARMOUR) return false;

    if (!(std::getline(iss >> std::ws, name) && iss >> gradeInt && std::getline(iss >> std::ws, description) &&
          iss >> timeEarned >> armourStat)) {
        return false;
    }

    return true;
}

Armour& Armour::operator=(const Armour& otherArmour){
    if(this != &otherArmour){
        type = otherArmour.getType();
        name = otherArmour.getName();
        description = otherArmour.getDescript();
        timeEarned = otherArmour.getTime();
        armourStat = otherArmour.getArmourStat();
    }
    return *this;
}

std::unique_ptr<Item> Armour::cloneUnique() const {
    return std::make_unique<Armour>(*this);  
}
