#pragma once

#include <stdexcept>
#include <ostream>
#include <sstream>
#include "item.h"
#include "itemType.h"
#include <memory>
using std::make_unique;
using std::unique_ptr;
class Item;

class ItemStack {
private:
    unique_ptr<Item> currentItem;
    int quantity;

public:
    ItemStack(std::unique_ptr<Item> newItem, int amount = 1);
    ~ItemStack();
    ItemStack(const ItemStack& other);
    ItemStack& operator=(const ItemStack& rhs);

    void increaseQuantity(int amount);
    void decreaseQuantity(int amount);
    int currentQuantity() const{return quantity;}

    bool isItem(const Item& other) const;
    friend std::ostream& operator<<(std::ostream& out, const ItemStack& stack);
    friend void swap(ItemStack*& stack1, ItemStack*& stack2);

    Item* getItem();
    const Item* getItem() const;

    std::string serialize() const;
    bool deserialize(const std::string& data);
};
