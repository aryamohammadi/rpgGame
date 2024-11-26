#include "combat.h"
#include <random> // For random number generation
#include <iostream>
#include <vector>


Combat::Combat(std::vector<Character>& fighters) : fightersAlive(fighters) {}

Combat::~Combat() = default;

void Combat::startBattle() {
    if (fightersAlive.size() <= 1) {
        std::cout << "Not enough characters for a battle. Pick another option. \n";
        return;
    }

    // Make sure heap is sorted based on speed
    //heapifyAll();

    // Validate presence of player and enemies
    bool playerFound = false;
    bool enemiesFound = false;

    for (int i = 0; i < fightersAlive.size(); ++i) {
    Character& fighter = fightersAlive[i];
        if (fighter.getCharacterName() == "Player") {
            playerFound = true;
        } else if (fighter.isAlive()) {
            enemiesFound = true;
        }
        if (playerFound && enemiesFound) break;
    }

    if (!playerFound) {
        throw std::runtime_error("No player found. Cannot start battle.");
    }
    if (!enemiesFound) {
        std::cout << "No enemies found. Pick another option";
        return;
    }

    std::cout << "Battle begins!\n";

    // Battle loop
    while (!hasBattleEnded()) {
        // Pop the top of the heap (fastest attacker)
       // Character* attacker = getFastestFromHeap();

    }
}

//bool isalive function //has if it a chaster
//if the player is alove and check if its an enemeny. 
//if figher is a player

//get character name 
//!!!!!!!!!!
//FIXME: We have to implement getCharacterName() in the Character class
//!!!!!!!!!!

void Combat::performAttack(Character& attacker) {
   std::cout << attacker.getCharacterName() << "'s turn to attack!" << endl;


   Character* target = nullptr;


   // Check if the attacker is the player
   if (attacker.getCharacterName() == "Player") {
       // Display the list of valid targets (all alive enemies)
       cout << "Choose a target to attack:" <<endl;
       vector<int> validTargets;
       for (int i = 0; i < fightersAlive.size(); ++i) {
           Character* potentialTarget = fightersAlive[i];
           if (potentialTarget->getCharacterName() != "Player" && potentialTarget->isAlive()) {
               validTargets.push_back(i);
               std::cout << i << ": " << potentialTarget->getCharacterName() << endl;
           }
       }


       // Ensure there are valid targets
       if (validTargets.empty()) {
           cout << "No valid targets to attack. Skipping turn.\n";
           return;
       }


       // Prompt the player for a target
       int targetIndex = -1;
       bool validChoice = false;
       while (!validChoice) {
           std::cout << "Enter the index of your target: ";
           std::cin >> targetIndex;


           // Validate input
           if (targetIndex >= 0 && targetIndex < fighterHeap.size()) {
               Character* potentialTarget = fighterHeap[targetIndex];
               if (potentialTarget->getCharacterName() != "Player" && potentialTarget->isAlive()) {
                   validChoice = true;
                   target = potentialTarget;
               }
               else {
                   std::cout << "Invalid choice: Target must not be yourself or already defeated.\n";
               }
           }
           else {
               std::cout << "Invalid choice: Index out of range. Please select a valid target.\n";
           }
       }
   }
   else {
       // Enemy automatically targets the player
       for (int i = 0; i < fighterHeap.size(); ++i) {
           Character* potentialTarget = fighterHeap[i];
           if (potentialTarget->getCharacterName() == "Player" && potentialTarget->isAlive()) {
               target = potentialTarget;
               break;
           }
       }


       // Announce the enemy is attacking the player
       if (target) {
           std::cout << attacker.getCharacterName() << " is attacking you!\n";
       }
   }


   // If no valid target found, skip the turn
   if (!target) {
       std::cout << "No valid target found. Skipping turn.\n";
       return;
   }


   // Perform the attack
   int baseDamage = attacker.getDamage();
   int minDamage = baseDamage * 0.75;
   int maxDamage = baseDamage * 1.25;
   int damage = minDamage + (rand() % (maxDamage - minDamage + 1));


   // Apply damage
   target->takeDamage(damage);
   std::cout << attacker.getCharacterName() << " dealt " << damage
             << " damage to " << target->getCharacterName() << "!\n";


   // Check if the target is defeated
   if (!target->isAlive()) {
       std::cout << target->getCharacterName() << " has been defeated!\n";
       removePlayerFromHeap(target->getHeapIndex());
   }
}


void Combat::removePlayerFromHeap(int targetIndex) {
    if (targetIndex < 0 || targetIndex >= fighterHeap.size()) {
        throw std::runtime_error("Invalid index: Unable to remove character from heap.");
        return;
    }

    // Move the last element to the target index and pop the heap
    fighterHeap[targetIndex] = fighterHeap[fighterHeap.size() - 1]; // Replace with the last element
    fighterHeap.pop_back(); // Remove the last element

    // Restore the heap property
    if (targetIndex < fighterHeap.size()) { // Only re-heapify if there are elements left
        heapifyDown(targetIndex); // Push the element down to its correct position
        heapifyUp(targetIndex);   // Or pull it up if needed
    }
}

// check if the battle has ended
bool Combat::hasBattleEnded() {
    bool isPlayerAlive = false;
    bool areEnemiesAlive = false;

    for (int i = 0; i < fightersAlive.size(); ++i) {
        if (fightersAlive[i].isAlive()) {
            if (fightersAlive[i].getCharacterName() == "Player") {
                isPlayerAlive = true;
            } else {
                areEnemiesAlive = true; // At least one enemy is alive
            }
        }
        if (isPlayerAlive && areEnemiesAlive) {
            return false; // Battle continues
        }
    }

    // Battle ends if player is dead or all enemies are defeated
    if (!isPlayerAlive) {
        return true; // Player is dead, battle ends
    }
    if (!areEnemiesAlive) {
        return true; // All enemies are dead, battle ends
    }
    return false; // Battle continues
}
