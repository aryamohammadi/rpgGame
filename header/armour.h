#pragma once
#define ARMOUR_H

#include "../header/item.h"

class Armour : public Item{
    private:
        int armourStat = 0;
    public:
        Armour(ItemType t = ItemType::ARMOUR, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0, int stat):Item(t,name,itemGrade,descript,timeElapsed), armourStat(stat){}
        void useItem(Character& user) override{
            user.equipArmour(this);
        }
        int getArmourStat() const {return armourStat;}
};