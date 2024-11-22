#pragma once

#include <stdexcept>
#include <ostream>
class Item;
class ItemStack{
    private:
        Item* item;
        int quantity;
    public:
        ItemStack(Item* item, int amount = 1);
        ~ItemStack();
        ItemStack& operator=(const ItemStack& rhs);

        void increaseQuantity(int amount);
        void decreaseQuantity(int amount);

        bool isItem(const Item& other) const;
        friend std::ostream& operator<<(std::ostream& out, const ItemStack& stack);
        friend void swap(ItemStack*& stack1, ItemStack*& stack2);
        Item* getItem();
        const Item* getItem() const;
};
