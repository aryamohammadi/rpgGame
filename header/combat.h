#ifndef COMBAT_H
#define COMBAT_H

#include "AttackType.h"

int calculateDamage(AttackType attackType) {
    if (attackType == AttackType::Ranged) {
        return 15;  // Higher damage for ranged attacks
    } else if (attackType == AttackType::Melee) {
        return 10;  // Moderate damage for melee attacks
    } else if (attackType == AttackType::Brawl) {
        return 5;   // Lower damage for brawling attacks
    } else { 
        return 0;   // Return 0 if the attack type is invalid
    }
}

#endif