#include "../header/itemStack.h"
#include "../header/item.h"

ItemStack::ItemStack(Item* item, int amount) : item(item), quantity(amount) {
    if (amount <= 0) {
        throw std::invalid_argument("amount " + std::to_string(amount) + " is invalid!");
    }
}

ItemStack::~ItemStack() {
    delete item;
    item = nullptr;
}

ItemStack& ItemStack::operator=(const ItemStack& rhs) {
    if (this != &rhs) {
        delete item;
        item = (rhs.item)->clone();
        quantity = rhs.quantity;
    }
    return *this;
}

void ItemStack::increaseQuantity(int amount) {
    quantity += amount;
}

void ItemStack::decreaseQuantity(int amount) {
    quantity -= amount;
}

bool ItemStack::isItem(const Item& other) const {
    return item && item->getName() == other.getName() && item->getType() == other.getType();
}

std::ostream& operator<<(std::ostream& out, const ItemStack& stack) {
    if (stack.item) {
        out << *stack.item;
        out << "Quantity: " << stack.quantity << std::endl;
    }
    return out;
}

void swap(ItemStack*& stack1, ItemStack*& stack2) {
    ItemStack* temp = stack1;
    stack1 = stack2;
    stack2 = temp;
}

Item* ItemStack::getItem() {
    return item;
}

const Item* ItemStack::getItem() const {
    return item;
}
