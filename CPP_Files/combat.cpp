#include "combat.h"
#include <algorithm> // For std::remove_if

Combat::Combat(std::vector<Character>& fighters) : fightersAlive(fighters) {}

Combat::~Combat() = default;

void Combat::startBattle() {
    while (!hasBattleEnded()) {
        for (Character& fighter : fightersAlive) {
            if (fighter.isDead) continue;  // Skip the turn for dead characters.

            // Determine target based on strategy (e.g., lowest health, closest enemy)
            Character& target = selectTarget(fighter);

            // Perform attack and handle the outcome
            performAttack(fighter, target);

            // Check if the battle should end after each attack
            if (hasBattleEnded()) break;
        }
    }
}
void Combat::performAttack(Character& attacker, Character& defender){

};

void Combat::removePlayer(Character& playerToBeRemovedFromVector){
    
};


bool Combat::hasBattleEnded(){
    return (battleEnded);
}