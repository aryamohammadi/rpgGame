#pragma once

#include <vector>
#include "../header/item.h"
#include "../header/itemStack.h"
#include "../header/itemType.h"
#include "../header/compareBy.h"
using std::string;

class Inventory {
private:
    std::vector<ItemStack*> items;
    int size;
    int capacity;

    void reorganizeItems();
    void clear();

public:
    Inventory(int capacity = 10);
    ~Inventory();
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

    bool sizeGreaterThanOrEqualToCapacity() const;
    bool isEmpty() const;
    int itemsWithName(const string& name) const;

    void increaseCapacity(int amount);

    void sortAlphabetically();
    void sortByAscendingGrade();
    void sortByDescendingGrade();
    void makeLatestFirst();
    void makeOldestFirst();

    friend std::ostream& operator<<(std::ostream& out, const Inventory& rhs);
    std::ostream& outputWeapons(std::ostream& out) const;

    std::string serialize() const;
    bool deserialize(const std::string& data);
};
