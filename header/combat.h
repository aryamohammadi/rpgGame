#ifndef COMBAT_H
#define COMBAT_H

#include "character.h"
#include "Heap.h"
#include <vector>

// Class Combat manages a battle scenario between multiple characters.
class Combat{
    private:
        //MaxHeap<Character*> fighterHeap;  // MaxHeap to determine the order of attack

        bool battleEnded = false; // Flag to indicate if the battle has ended
        std::vector<Character&> fightersAlive;
        
        // Removes a defeated character from fightersAlive.
        void removePlayer(Character& playerToBeRemovedFromVector);

        // Helper function to select a target for a character to attack
        Character& selectTarget(Character& attacker);

    public:
        Combat(std::vector<Character&> fighters); // Initializes the combat with fighters.
        Combat(const Combat&) = delete; // Prevent copying of the combat instance.
        Combat& operator=(const Combat&) = delete; // Delete copy assignment
        ~Combat();
        
        void startBattle(); // Initiates and manages the combat loop.
        bool isPlayerDead(); // Checks if the player is dead.
        bool areBothEnemiesDead(); // Checks if all enemies are defeated.
        bool isAtLeast1EnemieAlive(); // Checks if at least one enemy is still fighting.
        void performAttack(Character& attacker); // Performs an attack between characters.
        bool hasBattleEnded(); // Checks if the battle has ended.
        void Combat::removePlayerFromHeap(int targetIndex);

};
#endif // COMBAT_H

