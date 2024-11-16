#pragma once
#define ITEM_H
#include <iostream>
#include <ostream>
#include <vector>
#include <ctime>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
using std::string;
using std::ostream;
using std::vector;
class Item{
    public:
        enum Grade{ //possible grades we can have
            COMMON,
            UNCOMMON,
            RARE,
            EPIC,
            LEGENDARY
        };
        enum ItemType{ //possible items we can have
            WEAPON,
            ARMOR,
            FOOD,
            POTION
        };
    private:
        string name;
        vector<string> types{"WEAPON", "ARMOR", "FOOD", "POTION"};
        vector<string> grades{"COMMON","UNCOMMON","RARE","EPIC","LEGENDARY"};
        ItemType type;
        string description;
        time_t timeEarned;
        Grade itemGrade;
    public:
        Item(ItemType t = WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", time_t time = time(nullptr)): type(t), name(name), itemGrade(itemGrade), description(descript), timeEarned(time){}

        Item(const Item& other) = delete;
        Item& operator=(const Item& other) = delete;
        virtual ~Item(){} //allows inherited items to delete Item

        string getName() const {return name;}
        string getDescript() const {return description;}
        time_t getTime() const {return timeEarned;}
        int getGrade() const {return itemGrade;}
        int getType() const {return type;}

        string determineType(int index) const;
        string determineGrade(int index) const;
        virtual void useItem() = 0;
        virtual Item* clone() const = 0;
        friend void swap(Item*& item1, Item*& item2);
};
ostream& operator<<(ostream& out, const Item& item);

class MockItem: public Item{
    public:
        MockItem(ItemType t = WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", time_t time = time(nullptr)):Item(t,name,itemGrade,descript, time){}
        MOCK_METHOD(void, useItem,(),(override));
        MOCK_CONST_METHOD0(clone, MockItem*());
};
void swap(MockItem*& item1, MockItem*& item2){
    MockItem* item1Placeholder = item1;

    item1 = item2;

    item2 = item1Placeholder;
}