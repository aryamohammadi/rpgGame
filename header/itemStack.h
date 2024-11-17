#pragma once
#define ITEMSTACK_H
#include "../header/inventory.h"
#include "inventory.h"
#include <stdexcept>
class ItemStack{
    private:
        Item* item;
        int quantity;
    public:
        ItemStack(Item* item, int amount = 1):item(item), quantity(amount){
            if(amount <= 0){
                throw std::invalid_argument("amount " + std::to_string(amount) + " is invalid!");
            }
        }
        ~ItemStack(){delete item;}
        ItemStack& operator=(const ItemStack& rhs){
            if(this != &rhs){
                delete item;
                item = (rhs.item)->clone();
                quantity = rhs.quantity;
            }
            return *this;
        }

        void increaseQuantity(int amount){quantity += amount;}
        void decreaseQuantitty(int amount){quantity -= amount;}

        bool isItem(const Item& other) const {
            if(item == nullptr){
                return false;
            }
            return item->getName() == other.getName() && item->getType() == other.getType();
        }
    friend ostream& operator<<(ostream& out, const ItemStack& stack){
        if(stack.item != nullptr){
            out << *stack.item;
            out << "Quantity: " << std::to_string(stack.quantity) << std::endl;
        }
        return out;
    }
    friend void swap(ItemStack*& stack1, ItemStack*& stack2){
        ItemStack* stack1placeholder = stack1;

        stack1 = stack2;

        stack2 = stack1placeholder;
    }
    Item* getItem() {return item;}
    const Item* getItem() const {return item;}
};