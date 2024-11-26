#include "combat.h"
#include <random> // For random number generation


Combat::Combat(std::vector<Character>& fighters) : fightersAlive(fighters) {}

Combat::~Combat() = default;


//Jessy will reimplement this function
// void Combat::startBattle() { 
    // while (!hasBattleEnded()) {
    //     for (int i = 0; i < fightersAlive.size(); ++i) {
    //         Character& fighter = fightersAlive[i]; // Get a reference to the current fighter
    //         if (fighter.isAlive()) { // Only allow alive characters to attack
    //             Character& target = selectTarget(fighter); // Select a target for the current fighter
    //             performAttack(fighter, target);  // Perform the attack
    //             if (hasBattleEnded()) { // Check if the battle has ended
    //                 battleEnded = true;
    //                 return; // Exit the function immediately
    //             }
    //         }
    //     }
    // }
}

//!!!!!!!!!!
//FIXME: We have to implement getCharacterName() in the Character class
//!!!!!!!!!!

void Combat::performAttack(Character& attacker) {
    std::cout << attacker.getCharacterName() << "'s turn to attack!\n"; 

    // Display the list of targets
    std::cout << "Choose a target to attack:\n";
    for (int i = 0; i < fighterHeap.size(); ++i) { // Display all targets
        Character* target = fighterHeap[i];
        if (target->getCharacterName() != attacker.getCharacterName() && target->isAlive()) {
            std::cout << i << ": " << target->getCharacterName() << "\n"; // Display the target
        }
    }

    // Prompt user for a target index
    int targetIndex = -1; // set equal to -1 to avoid undefined behavior
    bool validChoice = false; // Flag to indicate if the choice is valid
    while (!validChoice) { // Loop until a valid choice is made
        std::cout << "Enter the index of your target: " << std::endl;
        std::cin >> targetIndex;
        std::cout << std::endl;
        
        // Validate the target
        if (targetIndex < 0 || targetIndex >= fighterHeap.size()) {
            std::cout << "Invalid choice: Index out of range. Please select a valid target.\n";
        }
        else if (fighterHeap[targetIndex].getCharacterName() == attacker.getCharacterName()) {
            std::cout << "Invalid choice: You cannot target yourself.\n";
        }
        else if (!fighterHeap[targetIndex].isAlive()) {
            std::cout << "Invalid choice: Target is already defeated.\n";
        }
        else {
            validChoice = true; // All conditions are met
        }
    }

    // Perform attack on the selected target
    Character* defender = fighterHeap[targetIndex];
    
    // randomization of damage
    int baseDamage = attacker.getDamage();
    int minDamage = baseDamage * 0.75; // 75% of base damage
    int maxDamage = baseDamage * 1.25; // 125% of base damage
    int damage = minDamage + (rand() % (maxDamage - minDamage + 1)); // Random damage between min and max
    
    // Ensure damage is not negative or zero
    if (damage > 0) { // Damage is positive
        defender->takeDamage(damage);
        std::cout << attacker.getCharacterName() << " dealt " << damage
                  << " damage to " << defender->getCharacterName() << "!\n";
    }
    else { // Damage is zero or negative
        std::cout << attacker.getCharacterName() << " failed to deal damage to "
                  << defender->getCharacterName() << ".\n";
    }

    // Check if the defender is dead
    if (!defender->isAlive()) { // Defender is defeated
        std::cout << defender->getCharacterName() << " has been defeated!\n";
        removePlayerFromHeap(targetIndex);
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
