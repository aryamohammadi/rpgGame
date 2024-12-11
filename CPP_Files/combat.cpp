#include "../header/combat.h"
#include "../header/Heap.h"
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
                int playerToAttack = playerDecidesWhoToAttack();
                fightersAlive.front()->attack(*fightersAlive.at(playerToAttack));
            }
        }
    }
}


int Combat::playerDecidesWhoToAttack(){
    cout << "Choose an enemy to attack" << endl;
    cout << endl;
    for(int i = 1; i < fightersAlive.size();i++){
        if(fightersAlive.at(i)->getHealth() > 0){
            cout << "Enemies available to attack" << endl;
        
            cout << "Enemy: " << i << ": "
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
}

bool Combat::isAtLeast1EnemieAlive() const{
    return fightersAlive.size() > 1;
}
bool Combat::isPlayerDead() const{
    return !fightersAlive.front()->isAlive();
}