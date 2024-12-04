#pragma once

#include "../header/item.h"
#include <string>

using std::string;
class Character;

class Armour : public Item {
private:
    int armourStat;

public:
    Armour(ItemType t = ItemType::ARMOUR, const string& name = "Default Armour", Item::Grade itemGrade = Item::COMMON, const string& descript = "", int stat = 0, double timeElapsed = -1.0);
    void useItem(Character&) override;
    Item* clone() const override;
    int getArmourStat() const;
    friend std::ostream& operator<<(std::ostream& out, const Armour& currentArmour);

    std::string serialize() const override;
    bool deserialize(const std::string& data) override;
};
