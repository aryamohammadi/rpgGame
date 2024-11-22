#pragma once


#include "../header/item.h"
#include <string>
using std::string;
class Character;

class Armour : public Item{
    private:
        int armourStat;
    public:
        Armour(ItemType t, const string& name, Item::Grade itemGrade, const string& descript, double timeElapsed, int stat);
        void useItem(Character&) override;
        Item* clone() const override;
        int getArmourStat() const {return armourStat;}
};