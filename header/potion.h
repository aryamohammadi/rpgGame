#pragma once

#include "../header/item.h"
#include <string>

using std::string;
class Character;

class Potion : public Item {
private:
    int recoveryAmount;

public:
    Potion(ItemType t = ItemType::POTION, const string& name = "Default Potion", Item::Grade itemGrade = Item::COMMON, const string& descript = "", int amount = 10, double timeElapsed = -1.0);
    void useItem(Character&) override;
    Item* clone() const override;
    int getRecoveryAmount() const;
    friend std::ostream& operator<<(std::ostream& out, const Potion& currentPotion);

    std::string serialize() const override;
    bool deserialize(const std::string& data) override;
};
