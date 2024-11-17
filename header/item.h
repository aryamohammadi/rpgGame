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

// Define a static start time for the program
static auto programStartTime = std::chrono::steady_clock::now();

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
            ARMOUR,
            POTION
        };
    protected:
        string name;
        const vector<string> types{"WEAPON", "ARMOR", "FOOD", "POTION"};
        const vector<string> grades{"COMMON","UNCOMMON","RARE","EPIC","LEGENDARY"};
        ItemType type;
        string description;
        double timeEarned;
        Grade itemGrade;
    public:
        Item(ItemType t = WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0): type(t), name(name), itemGrade(itemGrade), description(descript){
            if(timeElapsed < 0){
                auto now = std::chrono::steady_clock::now();
                std::chrono::duration<double> duration = now - programStartTime;
                timeEarned = duration.count();  // Store elapsed time in seconds as double
            }
            else{
                timeEarned = timeElapsed;
            }            
        }

        Item(const Item& other) = delete;
        Item& operator=(const Item& other) = delete;
        virtual ~Item(){} //allows inherited items to delete Item

        string getName() const {return name;}
        string getDescript() const {return description;}
        double getTime() const {return timeEarned;}
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
        MockItem(ItemType t = WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0):Item(t,name,itemGrade,descript, timeElapsed){}
        MOCK_METHOD(void, useItem,(),(override));
        Item* clone() const override{
            return new MockItem(type, name, itemGrade, description, timeEarned);
        }
        friend void swap(MockItem*& item1, MockItem*& item2){
            MockItem* item1Placeholder = item1;

            item1 = item2;

            item2 = item1Placeholder;
    }
};