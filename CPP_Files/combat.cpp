#include "combat.h"
#include <random> // For random number generation
#include <iostream>
#include <vector>
#include <random>
using namespace std:

Combat::Combat(vector<Character>& fighters) : fightersAlive(fighters) {}

Combat::~Combat() = default;

void Combat::startBattle() {
    if (fightersAlive.size() <= 1) {
        cout << "Not enough characters for a battle. Pick another option." << endl;
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
        throw runtime_error("No player found. Cannot start battle.");
    }
    if (!enemiesFound) {
        cout << "No enemies found. Pick another option";
        return;
    }

    cout << "Battle begins!" << endl;

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
    cout << attacker.getCharacterName() << "'s turn to attack!" << endl;

    Character* target = nullptr;

    // Check if the attacker is the player
    if (attacker.getCharacterName() == "Player") {
        // Display the list of valid targets (all alive enemies)
        cout << "Choose a target to attack:" << endl;
        vector<int> validTargets;
        for (int i = 0; i < fightersAlive.size(); ++i) {
            Character* potentialTarget = &fightersAlive[i];
            if (potentialTarget->getCharacterName() != "Player" && potentialTarget->isAlive()) {
                validTargets.push_back(i);
                cout << i << ": " << potentialTarget->getCharacterName() << endl;
            }
        }

        // Ensure there are valid targets
        if (validTargets.empty()) {
            cout << "No valid targets to attack. Skipping turn." << endl;
        }

        // Prompt the player for a target
        int targetIndex = -1;
        bool validChoice = false;
        while (!validChoice) {
            cout << "Enter the index of your target: " << endl;
            cin >> targetIndex;

            // Validate input
            if (targetIndex >= 0 && targetIndex < fightersAlive.size()) {
                Character* potentialTarget = &fightersAlive[targetIndex];
                if (potentialTarget->getCharacterName() != "Player" && potentialTarget->isAlive()) {
                    validChoice = true;
                    target = potentialTarget;
                }
                else {
                    cout << "Invalid choice: Target must not be yourself or already defeated." << endl;
                }
            }
            else {
                cout << "Invalid choice: Index out of range. Please select a valid target." << endl;
            }
        }    
    }
    else {
        // Enemy automatically targets the player
        for (int i = 0; i < fightersAlive.size(); ++i) {
            Character* potentialTarget = &fightersAlive[i];
            if (potentialTarget->getCharacterName() == "Player" && potentialTarget->isAlive()) {
                target = potentialTarget;
                break;
            }
        }

        // Announce the enemy is attacking the player
        if (target) {
            cout << attacker.getCharacterName() << " is attacking you!" << endl;
        }
    }

    // If no valid target found, skip the turn
    if (!target) {
        cout << "No valid target found. Skipping turn." << endl;
        return;
    }

    // Perform the attack
    int baseDamage = attacker.getDamage();
    int minDamage = baseDamage * 0.75;
    int maxDamage = baseDamage * 1.25;
    int damage = minDamage + (rand() % (maxDamage - minDamage + 1));


    // Apply damage
    target->takeDamage(damage);
    cout << attacker.getCharacterName() << " dealt " << damage
         << " damage to " << target->getCharacterName() << "!" << endl;


    // Check if the target is defeated
    if (!target->isAlive()) {
        cout << target->getCharacterName() << " has been defeated!" << endl;
        removePlayerFromHeap(target->getHeapIndex());
    }
}


void Combat::removePlayerFromHeap(int targetIndex) {
    if (targetIndex < 0 || targetIndex >= fightersAlive.size()) {
        throw runtime_error("Invalid index: Unable to remove character from heap.");
        return;
    }

    // Move the last element to the target index and pop the heap
    fightersAlive[targetIndex] = fightersAlive[fightersAlive.size() - 1]; // Replace with the last element
    fightersAlive.pop_back(); // Remove the last element

    // Restore the heap property
    if (targetIndex < fightersAlive.size()) { // Only re-heapify if there are elements left
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
