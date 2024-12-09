#pragma once
#include <iostream>
#include <vector>
#include <memory>
class Item;
class ItemStack;
#include "../header/itemStack.h"
#include "../header/itemType.h"
#include "../header/compareBy.h"
using std::string;
using std::make_unique;
using std::unique_ptr;
class Inventory {
private:
    std::vector<unique_ptr<ItemStack>> items;
    int size = 0;
    int capacity;

    void reorganizeItems();
    void clear();
    void resize();
public:
    Inventory(int capacity = 10):capacity(capacity){}
    ~Inventory(){clear();}
    Inventory(const Inventory& inventory2);
    Inventory& operator=(const Inventory& rhs);

    void addItem(Item* item);
    void addItem(Item* item, int quantity);

    void removeItem(const Item& item);
    void removeItem(const string& name);
    void removeItem(const string& name, ItemType t);

    int itemFound(const Item* item) const;
    int itemFound(const Item& item) const;
    int itemFound(const string& name) const;
    int itemFound(const string& name, ItemType t) const;
    int itemFound(int index) const;

    const Item* getItem(int index) const;
    Item* getItem(int index);

    bool sizeGreaterThanOrEqualToCapacity() const{return size >= capacity;}
    bool isEmpty() const{return size == 0;}
    int itemsWithName(const string& name) const;

    void increaseCapacity(int amount){capacity += amount;}

    void sortAlphabetically();
    void makeLatestFirst();
    void makeOldestFirst();

    friend std::ostream& operator<<(std::ostream& out, const Inventory& rhs);
    std::ostream& outputWeapons(std::ostream& out) const;

    std::string serialize() const;
    bool deserialize(const std::string& data);
};
