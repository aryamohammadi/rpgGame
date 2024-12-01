#pragma once

#include "../header/item.h"
#include <string>
using std::string;
class Character;

class Potion : public Item{
    private:
        int recoveryAmount;
    public:
        Potion(ItemType t, const string& name, Item::Grade itemGrade, const string& descript, int amount, double timeElapsed = 1.0);
        void useItem(Character&) override;
        Item* clone() const override;
        int getRecoveryAmount() const {return recoveryAmount;}
        friend std::ostream& operator<<(ostream& out, const Potion& currentPotion);
};