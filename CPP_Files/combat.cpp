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
