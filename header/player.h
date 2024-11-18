#include "character.h"
#include "combat.h"
#include <iostream>

class Player : public Character {
public:
    Player(const std::string& name) : Character(name) {}

    void attack() override {
        // Use the character's AttackType to determine damage
        int damageDealt = calculateDamage(getAttackType());
        std::cout << "Player attacks with " << damageDealt << " damage!\n";
    }

    void defend() override {
        std::cout << "Player defends!\n";
    }
    
};
