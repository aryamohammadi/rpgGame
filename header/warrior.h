#pragma once
#include "character.h"

class Warrior:public Character {
    private:
        int level;
        int experience;
        int currency;
    public:
        Warrior(): level(0), experience(0), currency(0), Character("defaut"){}//default constructor
        Warrior(string name): level(0),experience(0),currency(0), Character(name){}//overloaded constructor
        ~Warrior();//destructor, not needed because no memory is allocated at this moment
        void levelUp();
        void changeCurrency(int amount);
};
