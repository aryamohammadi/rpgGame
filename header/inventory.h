#pragma once
#define INVENTORY_H
#include "../header/item.h"

class Inventory{
    private:
        vector<Item*> items; 
        int size;
        int capacity;

        void reorganizeItems();
    public:
        Inventory(int capacity = 10):size(0), capacity(capacity), items(capacity){items.reserve(capacity);}
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
        bool sizeGreaterThanOrEqualToCapacity() const {return size >= capacity;}
        bool isEmpty() const {return size == 0;}

        void increaseCapacity(int amount){capacity += amount;}

        void sortAlphabetically();
        void sortByGrade();
        void sortByTypes();
        void makeLatestFirst();
        void makeOldestFirst();

       friend ostream& operator<<(ostream& out, const Inventory& rhs);
};