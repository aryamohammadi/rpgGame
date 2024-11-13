#pragma once
#define INVENTORY_H
#include "item.h"

class Inventory{
    private:
        vector<Item*> items; 
        int size;
        int capacity;
    public:
        Inventory():size(0){}
        ~Inventory(){
            for(Item* x : items){
                delete x;
            }
        }
        Inventory(Inventory& inventory2);
        Inventory& operator=(const Inventory& rhs);

        void addItem(Item* item);
        void removeItem(const string& name);
        bool itemFound(const string& name);

        void increaseCapacity(int amount){capacity += amount;}

        void sortAlphabetically();
        void sortByGrade();
        void sortByTypes();
        void makeLatestFirst();
        void makeOldestFirst();
};