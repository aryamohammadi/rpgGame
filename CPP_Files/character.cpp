#include "../header/character.h"
#include <utility> // For std::swap

// Copy operator
Character::Character(const Character& other)
    : characterName(other.characterName),
      inventoryOfCharacter(other.inventoryOfCharacter), //  FIXME: this needs to be reviewd and fixed
      health(other.health),
      damage(other.damage),
      defense(other.defense),
      isDead(other.isDead),
      currentAttackType(other.currentAttackType) {
}


// Copy assignment operator
Character& Character::operator=(const Character& other) {
    if (this != &other) {
        Character temp(other); // Utilizing the copy constructor in the temporary instance
        swap(temp); // Swapping *this with temp
    }
    return *this;
}

// Swap function
void Character::swap(Character& other) noexcept {
    using std::swap;
    swap(characterName, other.characterName);
    swap(inventoryOfCharacter, other.inventoryOfCharacter); //FIXME: this needs to be reviewed and fixed
    swap(health, other.health);
    swap(damage, other.damage);
    swap(defense, other.defense);
    swap(isDead, other.isDead);
    swap(currentAttackType, other.currentAttackType);
}

std::string Character::getCharacterName() const {
    return characterName;
}