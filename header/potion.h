#pragma once

class Item;
#include "../header/character.h"
#include <string>

using std::string;
class Potion : public Item {
private:
    int recoveryAmount;

public:
    Potion(ItemType t, const string& name, Grade itemGrade, const string& descript, int amount, double timeElapsed = -1.0);
    void useItem(Character&) override;
    Item* clone() const override;
    int getRecoveryAmount() const;
    friend std::ostream& operator<<(std::ostream& out, const Potion& currentPotion);

    std::string serialize() const;
    bool deserialize(const std::string& data);
};
