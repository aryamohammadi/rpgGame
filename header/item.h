#pragma once

#include <iostream>
#include <ostream>
#include <vector>
#include <ctime>
#include <string>
#include <chrono>
#include "../header/itemType.h"
#include "../header/character.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Character;
using std::string;
using std::ostream;
using std::vector;

static auto programStartTime = std::chrono::steady_clock::now();

class Item{
    public:
//         enum Grade{ //possible grades we can have
//             COMMON,
//             UNCOMMON,
//             RARE,
//             EPIC,
//             LEGENDARY
//         };
    protected:
        string name;
        const vector<string> types{"WEAPON", "ARMOR", "POTION"};
//         const vector<string> grades{"COMMON","UNCOMMON","RARE","EPIC","LEGENDARY"};
        ItemType type;
        string description;
        double timeEarned;
    public:
        Item(ItemType t = ItemType::WEAPON, const string& name = "", const string& descript = "", double timeElapsed = -1.0): type(t), name(name), description(descript){
            if(timeElapsed < 0){
                auto now = std::chrono::steady_clock::now();
                std::chrono::duration<double> duration = now - programStartTime;
                timeEarned = duration.count();  // Store elapsed time in seconds as double
            }
            else{
                timeEarned = timeElapsed;items.clear();
            }            
        }

class Item {
public:
// enum Grade {
//     COMMON,
//     UNCOMMON,
//     RARE,
//     EPIC,
//     LEGENDARY
// };
protected:
    string name;
    const vector<string> types{"WEAPON", "ARMOR", "POTION"};
//     const vector<string> grades{"COMMON", "UNCOMMON", "RARE", "EPIC", "LEGENDARY"};
    ItemType type;
    string description;
    double timeEarned;

public:
    Item(ItemType t = ItemType::WEAPON, const string& name = "", const string& descript = "", double timeElapsed = -1.0);
    Item(const Item& other) = delete;
    Item& operator=(const Item& other) = delete;
    virtual ~Item();

    string getName() const;
    string getDescript() const;
    double getTime() const;
    ItemType getType() const;
    string determineType(ItemType type) const;

    virtual void useItem(Character&) = 0;
    virtual Item* clone() const = 0;
    friend void swap(Item*& item1, Item*& item2);

    virtual std::string serialize() const;
    virtual bool deserialize(const string& data);
};
ostream& operator<<(ostream& out, const Item& item);


// Matthew says to merge MockItem back
class MockItem: public Item{
    public:
        MockItem(ItemType t = ItemType::WEAPON, const string& name = "", const string& descript = "", double timeElapsed = -1.0):Item(t,name,itemGrade,descript, timeElapsed){}
        MOCK_METHOD(void, useItem,(Character&),(override));
        MOCK_METHOD(std::string, serialize, (), (const, override));
        MOCK_METHOD(bool,deserialize,(const string&), (override));
        Item* clone() const override{
            return new MockItem(type, name, itemGrade, description, timeEarned);
        }
        friend void swap(MockItem*& item1, MockItem*& item2){
            MockItem* item1Placeholder = item1;

            item1 = item2;

            item2 = item1Placeholder;
    }
};