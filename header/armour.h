#pragma once

#include "../header/item.h"
#include "../header/character.h"
#include <string>

using std::string;
class Character;

class Armour : public Item {
private:
    int armourStat;

public:
    Armour(ItemType t, const string& name, Grade itemGrade, const string& descript, int stat, double timeElapsed = -1.0);
    void useItem(Character&) override;
    Item* clone() const override;
    int getArmourStat() const;
    friend std::ostream& operator<<(std::ostream& out, const Armour& currentArmour);

    std::string serialize() const;
    bool deserialize(const std::string& data);
};
