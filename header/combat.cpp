#include "combat.h"

void Combat::performAttack(Character& attacker, Character& defender){

};

void Combat::removePlayer(Character& playerToBeRemovedFromVector){
    
};

bool Combat::isPlayerDead(){
    if(fightersAlive.at(0).health > 0){
        return true;
    }
}

bool Combat::areBothEnemiesDead(){
    if (fightersAlive.at(1).health > 0 && fightersAlive.at(2).health > 0){
        return true;
    }
}

void Combat::startBattle(){

    
    while(!battleEnded){
        if(isPlayerDead() ||areBothEnemiesDead){
            battleEnded = true;
            break;
        }

    }
    
}

bool Combat::hasBattleEnded(){
    return (battleEnded);
}