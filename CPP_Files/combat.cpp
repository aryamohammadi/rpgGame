#include "combat.h"
#include "Heap.h"
#include <random> // For random number generation
#include <iostream>
#include <vector>
#include <random>
#include <ostream>
using namespace std;

Combat::Combat(vector<Character*> fighters) : fightersAlive(fighters) {}

Combat::~Combat() = default;

void Combat::startBattle() { // Indenting this was quite nice - Jameel
    MaxHeap heap;
    bool playerAlive = fightersAlive.front()->isAlive();//boolean checks that if the player in first index is alive
        while(playerAlive && fightersAlive.size() > 1){// this makes sure that the loop will only run if there are enemies and a playerAlive
            vector<Character*> turnOrder = fightersAlive;
            heap.heapsort(turnOrder);
            for(int i = 0; i < turnOrder.size();i++){
                if(turnOrder.at(i)->getName().find("Enemy")!= string::npos){
                    turnOrder.at(i)->attack(*fightersAlive.front());
                    //attack first index of fightersAlive vector(need to implement this);
                    if(fightersAlive.at(0)->getHealth() <= 0){//check if player health is not 0. if its 0 set playerAliveToFalse otherwise do nothing
                        delete fightersAlive.at(0);
                        playerAlive = false;
                    }
                }
                else {
                    std::cout << "Choose an enemy to attack" << endl;
                    int playerToAttack = playerDecidesWhoToAttack();
                    fightersAlive.front()->attack(*fightersAlive.at(playerToAttack));
                    //we need the actual player to decide who he wants to attack enemy1 or w - done
                    //we have to output a list of valid players - done
                    //still need to perform attack 

                for (int i = 0; i < fightersAlive.size(); ++i) {
                    Character* fighter = fightersAlive[i];
                    if (fighter->getCharacterName() == "Player") {
                        // playerFound = true;
                    } 
                    else if (fighter->isAlive()) {
                        // enemiesFound = true;
                        //after we have to check if the enemy is dead or not. if it is remove it from the fighters alive
                        if(fightersAlive.at(playerToAttack)->getHealth() <= 0){
                            removePlayerFromHeap(fightersAlive.at(i)->getName());
                        }
                    }
                }   
            }
        }
    }
}

int Combat::playerDecidesWhoToAttack(){
    std::cout << "Choose an enemy to attack" << endl;
    for(int i = 1; i < fightersAlive.size();i++){
        if(fightersAlive.at(i)->getHealth() > 0){
            std::cout << i << ": " << fightersAlive.at(i)->getName()
            << "health " << fightersAlive.at(i)->getHealth() << endl;
        }
    }
    int choiceToAttack;
    bool validChoice = false;
    while(!(validChoice)){
        cin >> choiceToAttack;
        if (choiceToAttack > 0 && choiceToAttack < fightersAlive.size() && fightersAlive.at(choiceToAttack)->getHealth() > 0 && fightersAlive.at(choiceToAttack)->getName() == "Enemy"){
            validChoice = true;
        }
        cout << "Invalid Choice." << endl;
    }
    return choiceToAttack;
}

void Combat::removePlayerFromHeap(string targetName) {
    for(int i = 0; i < fightersAlive.size();i++){
        if(fightersAlive.at(i)->getName() == targetName){
            swap(fightersAlive.at(i),fightersAlive.back());
            fightersAlive.pop_back();
        }
    }
}


/* void Combat::performAttack(Character& attacker) { // Why was this commented?
    cout << attacker.getCharacterName() << "'s turn to attack!" << endl;


    Character* target = nullptr;

    // Check if the attacker is the player
    if (attacker.getCharacterName() == "Player") {
        // Display the list of valid targets (all alive enemies)
        cout << "Choose a target to attack:" << endl;
        vector<int> validTargets;
        for (int i = 0; i < fightersAlive.size(); ++i) {
            Character* potentialTarget = fightersAlive[i];
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
                Character* potentialTarget = fightersAlive[targetIndex];
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
            Character* potentialTarget = fightersAlive[i];
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
    } */

    // // Perform the attack
    // int baseDamage = attacker.getDamage();
    // int minDamage = baseDamage * 0.75;
    // int maxDamage = baseDamage * 1.25;
    // int damage = minDamage + (rand() % (maxDamage - minDamage + 1));


    // // Apply damage
    // target->takeDamage(damage);
    // cout << attacker.getCharacterName() << " dealt " << damage
    //      << " damage to " << target->getCharacterName() << "!" << endl;


    // Check if the target is defeated
   /// if (!target->isAlive()) {
   //     cout << target->getCharacterName() << " has been defeated!" << endl;
     //   removePlayerFromHeap(target->getHeapIndex());
  //  }
//} 
/* 
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
        heapifyDown(,targetIndex); // Push the element down to its correct position
        heapifyUp(targetIndex);   // Or pull it up if needed
    }
}
 */
// check if the battle has ended
/* bool Combat::hasBattleEnded() {
    bool isPlayerAlive = false;
    bool areEnemiesAlive = false;

    for (int i = 0; i < fightersAlive.size(); ++i) {
        if (fightersAlive[i]->isAlive()) {
            if (fightersAlive[i]->getCharacterName() == "Player") {
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
} */