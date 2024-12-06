#include "combat.h"
#include "Heap.h"
#include <iostream>
#include <vector>
#include <random>
#include <ostream>
using namespace std;

Combat::Combat(vector<Character*> fighters) : fightersAlive(fighters) {}

Combat::~Combat() = default;

void Combat::startBattle() { // Indenting this was quite nice - Jameel
    MaxHeap heap;
    //comment by arya:
    //FIXME: If fightersAlive is empty, accessing fightersAlive.front() causes undefined behavior. 
    //       Need to discuss if this should be checked beforehand
    //
    bool playerAlive = fightersAlive.front()->isAlive();//boolean checks that if the player in first index is alive
    //comment by arya:
    //FIXME: If fightersAlive.size() > 1 becomes false during execution, playerAlive won't be updated properly. 
    //       Also, when the player is dead and removed, the logic assumes enemies are still there.
    //       Need to review to make sure this is correct
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
                cout << "Choose an enemy to attack" << endl;
                int playerToAttack = playerDecidesWhoToAttack();
                fightersAlive.front()->attack(*fightersAlive.at(playerToAttack));
                //we need the actual player to decide who he wants to attack enemy1 or w - done
                //we have to output a list of valid players - done
                //still need to perform attack 
                
                //comment by Arya:
                //FIXME: isnt this for loop redundant? we already have a for loop in removePlayerFromHeap that
                //       loops through fightersAlive. 
                // Jameel - Alright if that's the case I'm getting rid of it, because this else statement has no if statement before it
                   
            }
        }
    }
}


int Combat::playerDecidesWhoToAttack(){
    cout << "Choose an enemy to attack" << endl;
    for(int i = 1; i < fightersAlive.size();i++){
        if(fightersAlive.at(i)->getHealth() > 0){
            cout << i << ": " << fightersAlive.at(i)->getName()
            << "health " << fightersAlive.at(i)->getHealth() << endl;
        }
    }
    int choiceToAttack;
    bool validChoice = false;
    //comment by arya:
    //FIXME: "Invalid Choice." always prints even if the user enters a valid choice. Need to fix.
    while(!(validChoice)){
        cin >> choiceToAttack;
        if (choiceToAttack > 0 && choiceToAttack < fightersAlive.size() && fightersAlive.at(choiceToAttack)->getHealth() > 0 && fightersAlive.at(choiceToAttack)->getName() == "Enemy"){
            validChoice = true;
        }
        cout << "Invalid Choice." << endl; //FIXME: we need to make this more descriptive.
    }
    return choiceToAttack;
}


void Combat::removePlayerFromHeap(string targetName) {
    for(int i = 0; i < fightersAlive.size();i++){
        if(fightersAlive.at(i)->getName() == targetName){
            swap(fightersAlive.at(i),fightersAlive.back());
            //comment by arya:
            //FIXME: wouldnt popback cause dangling pointers?
            //       if so, we can use unique_ptr to take care of that
            fightersAlive.pop_back();
        }
    }