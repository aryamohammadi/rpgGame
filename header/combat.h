#ifndef COMBAT_H
#define COMBAT_H

#include "AttackType.h"
#include "../header/character.h"
#include <vector>
#include "character.h"
#include "Heap.h"

using std::vector;
// Class Combat manages a battle scenario between multiple characters.

class Combat{
    private:
        //MaxHeap<Character*> fighterHeap;  // MaxHeap to determine the order of attack

        bool battleEnded = false; // Flag to indicate if the battle has ended
        std::vector<Character*> fightersAlive;
        
        // Removes a defeated character from fightersAlive.

        // Helper function to select a target for a character to attack
        Character& selectTarget(Character& attacker);

    public:
        Combat(std::vector<Character*> fighters); // Initializes the combat with fighters.
        Combat(const Combat&) = delete; // Prevent copying of the combat instance.
        Combat& operator=(const Combat&) = delete; // Delete copy assignment
        ~Combat();
        
        void startBattle(); // Initiates and manages the combat loop.
        void removePlayerFromHeap(string targetName);
        int playerDecidesWhoToAttack();
        void removePlayerFromHeap(int targetIndex);
        bool isAtLeast1EnemieAlive() const;
        bool isPlayerDead() const;
};
#endif // COMBAT_H

