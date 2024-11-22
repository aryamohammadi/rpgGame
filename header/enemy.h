#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include "combat.h"
#include <iostream>

class Enemy : public Character {
public:
    void attack() override {
        int damageDealt = calculateDamage(getAttackType());
        std::cout << "Enemy attacks with " << damageDealt << " damage!\n";
    }

    void defend() override {
        std::cout << "Enemy defends!\n";
    }
};

#endif // ENEMY_H
