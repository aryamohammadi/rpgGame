#ifndef COMBAT_H
#define COMBAT_H

#include "AttackType.h"
#include "character.h"

class Combat{
    private:
        bool battleEnded = false;
        vector<Character>&fightersAlive;
        void removePlayer(Character& playerToBeRemovedFromVector);
    public:
        Combat(vector<Character>&fighters):fightersAlive(fighters){}
        Combat(const Combat&) = delete; // Delete copy constructor
        Combat& operator=(const Combat&) = delete; // Delete copy assignment
        ~Combat() = default; 

        void startBattle();
        bool isPlayerDead();
        bool areBothEnemiesDead();
        bool isAtLeast1EnemieAlive();
        void performAttack(Character& attacker, Character& target);
        bool hasBattleEnded();
};








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