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

// Serialize
std::string ItemStack::serialize() const {
    std::ostringstream oss;
    oss << (item ? item->serialize() : "null") << "\n" << quantity;
    return oss.str();
}

// Deserialize
bool ItemStack::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string itemData;

    // Deserialize the item data
    if (!std::getline(iss, itemData)) return false;

    if (itemData == "null") {
        item = nullptr;
    } else {
        std::istringstream itemStream(itemData);
        int itemType;
        if (!(itemStream >> itemType)) return false;

        switch (static_cast<ItemType>(itemType)) {
            case ItemType::WEAPON:
                item = new Weapon();
                break;
            case ItemType::ARMOUR:
                item = new Armour();
                break;
            case ItemType::POTION:
                item = new Potion();
                break;
            default:
                return false;
        }

        if (!item->deserialize(itemData)) {
            delete item;
            item = nullptr;
            return false;
        }
    }

    // Deserialize the quantity
    if (!(iss >> quantity)) {
        delete item;
        item = nullptr;
        return false;
    }

    return true;
}
