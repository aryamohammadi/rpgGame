#include "character.h"

class Combat{
    private:
        bool battleEnded();
        vector<Character>&fightersAlive;
        void removePlayer(Character& playerToBeRemovedFromVector);
    public:
        Combat(vector<Character>&fighters):fightersAlive(fighters){}
        //copy constructor
        //copy assignment
        //destructor

        void startBattle();
        void performAttack(Character& attacker, Character& target);
        bool hasBattleEnded();
};