#pragma once

#include "../header/itemType.h"
#include "../header/item.h"
#include <string>
using std::string;
class Character;

class Armour : public Item{
    private:
        int armourStat = 0;
    public:
        Armour(ItemType t, const string& name, Item::Grade itemGrade, const string& descript, double timeElapsed = -1.0, int stat);
        void useItem(Character&) override;
        Item* clone() const override;
        int getArmourStat() const {return armourStat;}
};