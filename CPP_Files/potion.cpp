#include "../header/item.h"
#include "../header/character.h"
Potion::Potion(ItemType t, const string& name, const string& descript, int amount, double timeElapsed):Item(t,name, descript, timeElapsed), recoveryAmount(amount){}

void Potion::useItem(Character& player){
    player.increaseHealth(recoveryAmount);
}

Item* Potion::clone() const{
    return new Potion(getType(),getName(),getDescript(),recoveryAmount, getTime());
}

std::ostream& operator<<(ostream& out, const Potion& currentPotion){
    out << static_cast<const Item&>(currentPotion);
    out << "Recovery Amount: " << currentPotion.getRecoveryAmount() << std::endl;
    return out;
}

// Override serialize
std::string Potion::serialize() const {
    std::ostringstream oss;
    oss << static_cast<int>(type) << "\n"              // ItemType as integer
        << name << "\n"                                // Potion name
        << description << "\n"                         // Description
        << timeEarned << "\n"                          // Time earned
        << recoveryAmount;                             // Recovery amount
    return oss.str();
}

// Override deserialize
bool Potion::deserialize(const std::string& data) {
    std::istringstream iss(data);
    int typeInt, gradeInt;

    if (!(iss >> typeInt)) return false;
    if (static_cast<ItemType>(typeInt) != ItemType::POTION) return false;

    if (!(std::getline(iss >> std::ws, name) && iss >> gradeInt && std::getline(iss >> std::ws, description) &&
          iss >> timeEarned >> recoveryAmount)) {
        return false;
    }

    return true;
}

Potion& Potion::operator=(const Potion& otherPotion){
    if(this != &otherPotion){
        type = otherPotion.getType();
        name = otherPotion.getName();
        description = otherPotion.getDescript();
        timeEarned = otherPotion.getTime();
        recoveryAmount = otherPotion.getRecoveryAmount();
    }
    return *this;
}