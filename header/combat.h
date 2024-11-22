#ifndef COMBAT_H
#define COMBAT_H

#include "AttackType.h"
#include "../header/character.h"
#include <vector>
using std::vector;
class Combat{
    private:
        bool battleEnded();
        vector<Character>&fightersAlive;
        void removePlayer(Character& playerToBeRemovedFromVector);
    public:
        Combat(vector<Character>&fighters):fightersAlive(fighters){}
        Combat(const Combat&) = delete; // Delete copy constructor
        Combat& operator=(const Combat&) = delete; // Delete copy assignment
        ~Combat() = default; 

        void startBattle();
        void performAttack(Character& attacker, Character& target);
        bool hasBattleEnded();
};

#endif