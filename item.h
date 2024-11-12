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
        ItemType type;
        string grade;
        string description;
        time_t timeEarned;
    public:
        Item(ItemType t = WEAPON, const string& name, const string& grade, const string& descript, time_t time = time(nullptr)): type(t), name(name), grade(grade), description(description), timeEarned(time){}

        virtual void useItem() = 0;
};