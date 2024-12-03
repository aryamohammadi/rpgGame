#pragma once

#include <stdexcept>
#include <ostream>
#include <sstream>
#include "item.h"
#include "weapon.h"
#include "armour.h"
#include "potion.h"
#include "itemType.h"

class Item;

class ItemStack {
private:
    Item* item;
    int quantity;

public:
    ItemStack(Item* item, int amount = 1);
    ~ItemStack();

    ItemStack& operator=(const ItemStack& rhs);

    void increaseQuantity(int amount);
    void decreaseQuantity(int amount);
    int currentQuantity() const;

    bool isItem(const Item& other) const;
    friend std::ostream& operator<<(std::ostream& out, const ItemStack& stack);
    friend void swap(ItemStack*& stack1, ItemStack*& stack2);

    Item* getItem();
    const Item* getItem() const;

    std::string serialize() const;
    bool deserialize(const std::string& data);
};
