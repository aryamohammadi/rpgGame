#include "../header/character.h"
#include "../header/armour.h"
#include <utility> // For std::swap

// Copy operator
Character::Character(const Character& other)
    : characterName(other.characterName), 
    health(other.health), 
    damage(other.damage), 
    defense(other.defense), 
    isDead(other.isDead), 
    currentAttackType(other.currentAttackType) {
}

// Copy assignment constructor
Character& Character::operator=(const Character& other) {
    if (this != &other) {
        Character temp(other);
        swap(temp);
    }
    return *this;
}

// Swap function
void Character::swap(Character& other) noexcept {
    using std::swap;
    swap(characterName, other.characterName);
    swap(health, other.health);
    swap(damage, other.damage);
    swap(defense, other.defense);
    swap(isDead, other.isDead);
    swap(currentAttackType, other.currentAttackType);
}

void Character::equipArmour(Armour* armour){
    if(this->armour == nullptr){
        this->armour = armour;
    }
    else{
        if(storage.itemFound(*armour) != -1){
            storage.removeItem(*armour);
        }
        this->armour = armour;
    }
    defense += armour->getArmourStat();
}

void Character::deEquipArmour() {
    if (armour != nullptr) {
        defense -= armour->getArmourStat();
        storage.addItem(armour);           
        armour = nullptr;                  
    }
}