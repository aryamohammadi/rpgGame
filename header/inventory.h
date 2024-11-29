#pragma once

#include <vector>
#include "../header/itemStack.h"

#include "../header/item.h"
#include "../header/itemType.h"
#include "../header/compareBy.h"
using std::string;
class Inventory{
    private:
        std::vector<ItemStack*> items; 
        int size;
        int capacity;

        void reorganizeItems();
        void clear(){
            for(ItemStack*& x : items){
                delete x;
                x = nullptr;
            }
            size = 0;
            capacity = 10;
        }
    public:
        Inventory(int capacity = 10):size(0), capacity(capacity), items(capacity){items.reserve(capacity);}
        ~Inventory(){clear();}
        Inventory(const Inventory& inventory2);
        Inventory& operator=(const Inventory& rhs);

        void addItem(Item* item);
        void addItem(Item* item, int quantity);

        void removeItem(const Item& item);
        void removeItem(const string& name);
        void removeItem(const string& name, ItemType t);

        int itemFound(const Item* item) const;
        int itemFound(const Item& item) const;  //given index
        int itemFound(const string& name) const; //given name
        int itemFound(const string& name, ItemType t) const; //given name and type
        int itemFound(int index) const;

        const Item* getItem(int index) const{return (items.at(index))->getItem();}
        Item* getItem(int index){return (items.at(index))->getItem();}

        bool sizeGreaterThanOrEqualToCapacity() const {return size >= capacity;}
        bool isEmpty() const {return size == 0;}
        int itemsWithName(const string& name) const;

        void increaseCapacity(int amount){capacity += amount;}

        void sortAlphabetically();
        void sortByAscendingGrade();
        void sortByDescendingGrade();
        void makeLatestFirst();
        void makeOldestFirst();

       friend std::ostream& operator<<(std::ostream& out, const Inventory& rhs);
       std::ostream& outputWeapons(std::ostream& out) const;
};
