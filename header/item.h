#pragma once

#include <iostream>
#include <ostream>
#include <vector>
#include <ctime>
#include <string>
#include "../header/itemType.h"
#include "../header/character.h"

class Character;

using std::string;
using std::ostream;
using std::vector;

static auto programStartTime = std::chrono::steady_clock::now();

class Item {
public:
    enum Grade {
        COMMON,
        UNCOMMON,
        RARE,
        EPIC,
        LEGENDARY
    };

protected:
    string name;
    const vector<string> types{"WEAPON", "ARMOR", "POTION"};
    const vector<string> grades{"COMMON", "UNCOMMON", "RARE", "EPIC", "LEGENDARY"};
    ItemType type;
    string description;
    double timeEarned;
    Grade itemGrade;

public:
    Item(ItemType t = ItemType::WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0);
    Item(const Item& other) = delete;
    Item& operator=(const Item& other) = delete;
    virtual ~Item();

    string getName() const;
    string getDescript() const;
    double getTime() const;
    Item::Grade getGrade() const;
    ItemType getType() const;
    string determineType(ItemType type) const;
    string determineGrade(int index) const;

    virtual void useItem(Character&) = 0;
    virtual Item* clone() const = 0;
    friend void swap(Item*& item1, Item*& item2);

    virtual std::string serialize() const;
    virtual bool deserialize(const string& data);
};
ostream& operator<<(ostream& out, const Item& item);