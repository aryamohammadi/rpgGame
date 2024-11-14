#pragma once
#define INVENTORY_H
#include "item.h"
#include "itemStack.h"
class Inventory{
    private:
        vector<ItemStack*> items; 
        int size;
        int capacity;

        void reorganizeItems();
    public:
        Inventory(int capacity = 10):size(0), capacity(capacity), items(capacity){items.reserve(capacity);}
        ~Inventory(){
            for(ItemStack* x : items){
                delete x;
            }
        }
        Inventory(Inventory& inventory2);
        Inventory& operator=(const Inventory& rhs);

        void addItem(Item* item);
        void addItem(Item* item, int quantity);

        void removeItem(const Item& item);
        void removeItem(const string& name);
        void removeItem(const string& name, Item::ItemType t);

        int itemFound(const Item& item) const;  //given index
        int itemFound(const string& name) const; //given name
        int itemFound(const string& name, Item::ItemType t) const; //given name and type

        bool sizeGreaterThanOrEqualToCapacity() const {return size >= capacity;}
        bool isEmpty() const {return size == 0;}
        int itemsWithName(const string& name) const;

        void increaseCapacity(int amount){capacity += amount;}

        void sortAlphabetically();
        void sortByGrade();
        void sortByTypes();
        void makeLatestFirst();
        void makeOldestFirst();

       friend ostream& operator<<(ostream& out, const Inventory& rhs);
};