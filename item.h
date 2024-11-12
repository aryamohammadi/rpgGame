#pragma once
#include <iostream>
#include <ostream>
#include <ctime>
using std::string;

class Item{
    private:
        string name;
        enum ItemType{ //possible items we can have
            WEAPON,
            ARMOR,
            Food,
            POTION
        }; 
        enum Grade{
            COMMON,
            UNCOMMON,
            RARE,
            EPIC,
            LEGENDARY
        };
        ItemType type;
        string description;
        time_t timeEarned;
        Grade itemGrade;
    public:
        Item(ItemType t = WEAPON, const string& name, Grade itemGrade = COMMON, const string& descript, time_t time = time(nullptr)): type(t), name(name), itemGrade(itemGrade), description(description), timeEarned(time){}

        virtual void useItem() = 0;
};