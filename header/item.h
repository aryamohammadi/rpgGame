#pragma once

#include <iostream>
#include <ostream>
#include <vector>
#include <ctime>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include "../header/itemType.h"
#include "../header/character.h"
class Character; // What's the purpose of this? This doesn't seem to do anything. - Jameel

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
    protected:
        string name;
        const vector<string> types{"WEAPON", "ARMOR", "POTION"};
        const vector<string> grades{"COMMON","UNCOMMON","RARE","EPIC","LEGENDARY"};
        ItemType type;
        string description;
        double timeEarned;
        Grade itemGrade;
    public:
        Item(ItemType t = ItemType::WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0): type(t), name(name), itemGrade(itemGrade), description(descript){
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
        virtual ~Item() = default; //allows inherited items to delete Item

        string getName() const {return name;}
        string getDescript() const {return description;}
        double getTime() const {return timeEarned;}
        Item::Grade getGrade() const {return itemGrade;}
        ItemType getType() const {return type;}
        string determineType(ItemType type) const;
        string determineGrade(int index) const;

        virtual void useItem(Character&) = 0;
        virtual Item* clone() const = 0;
        friend void swap(Item*& item1, Item*& item2);
};
ostream& operator<<(ostream& out, const Item& item);

class MockItem: public Item{
    public:
        MockItem(ItemType t = ItemType::WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0):Item(t,name,itemGrade,descript, timeElapsed){}
        MOCK_METHOD(void, useItem,(Character&),(override));
        Item* clone() const override{
            return new MockItem(type, name, itemGrade, description, timeEarned);
        }
        friend void swap(MockItem*& item1, MockItem*& item2){
            MockItem* item1Placeholder = item1;

            item1 = item2;

            item2 = item1Placeholder;
    }
};
