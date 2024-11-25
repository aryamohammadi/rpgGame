#ifndef COMBAT_H
#define COMBAT_H

#include "character.h"
#include "Heap.h"
#include <vector>

// Class Combat manages a battle scenario between multiple characters.
class Combat{
    private:
        MaxHeap<Character*> fighterHeap;  // MaxHeap to determine the order of attack

        bool battleEnded = false; // Flag to indicate if the battle has ended
        std::vector<Character>& fightersAlive;
        
        // Removes a defeated character from fightersAlive.
        void removePlayer(Character& playerToBeRemovedFromVector);

        // Helper function to select a target for a character to attack
        Character& selectTarget(Character& attacker);

    public:
        Combat(std::vector<Character>& fighters); // Initializes the combat with fighters.
        Combat(const Combat&) = delete; // Prevent copying of the combat instance.
        Combat& operator=(const Combat&) = delete; // Delete copy assignment
        ~Combat();
        
        void startBattle(); // Initiates and manages the combat loop.
        bool isPlayerDead(); // Checks if the player is dead.
        bool areBothEnemiesDead(); // Checks if all enemies are defeated.
        bool isAtLeast1EnemieAlive(); // Checks if at least one enemy is still fighting.
        void performAttack(Character& attacker, Character& target); // Performs an attack between two characters.
        bool hasBattleEnded(); // Checks if the battle has ended.
};
#endif // COMBAT_H


//declare combat object
//pass in a vector of character + enemies in the constructor through the vector

//in main im guessing that they'll have options. do you want to start the
//first level
//they'll click yes and the function combat.startfight() will be called
//combat.startfight();

//in this function
//ill call create an object of the maxheap and  pass in the vector.
//itll decide who attacks first and im guessing the player or enemie or index will be returned to see
//who will attack
//we'll have a loop that loops around so everyone attacks
//this will happen until the player dies or theirs no more enemies
//once 1 person remains then the loop will exit out