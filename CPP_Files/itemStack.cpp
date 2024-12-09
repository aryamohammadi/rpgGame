#include "../header/itemStack.h"
#include "../header/item.h"
ItemStack::ItemStack(std::unique_ptr<Item> newItem, int amount):quantity(amount){
    if (amount <= 0) {
        throw std::invalid_argument("amount " + std::to_string(amount) + " is invalid!");
    }
    currentItem = move(newItem);
}

ItemStack::~ItemStack(){}
ItemStack::ItemStack(const ItemStack& other){
    if(&other == nullptr){
        throw std::runtime_error("Nullptr");
    }
    if(other.currentItem != nullptr){
        currentItem = other.currentItem->cloneUnique();
    }else{
        currentItem.reset();  // Initialize with nullptr if other has no item
    }
    quantity = other.quantity;
}
ItemStack& ItemStack::operator=(const ItemStack& rhs) {
    if(this != &rhs){

        if(rhs.currentItem != nullptr){
            currentItem = rhs.currentItem->cloneUnique();
        }else{
            currentItem.reset();  // Reset currentItem to nullptr if rhs has no item
        }
        quantity = rhs.quantity;
    }
    return *this;
}

void ItemStack::increaseQuantity(int amount) {
    quantity += amount;
}

void ItemStack::decreaseQuantity(int amount) {
    if(amount > quantity){
        throw std::invalid_argument("decreaseQuantity: amount larger than quantity!");
    }
    if(amount < 0){
        throw std::invalid_argument("decreaseQuantity: amount negative!");
    }
    quantity -= amount;
}

bool ItemStack::isItem(const Item& other) const {
    if(currentItem == nullptr){
        return false; // Early return if currentItem is null
    }

    // Check if name and type match
    if (currentItem->getName() == other.getName() && currentItem->getType() == other.getType()){
        switch(other.getType()){
            case ItemType::WEAPON:{
                const Weapon* currentWeapon = dynamic_cast<const Weapon*>(&other);
                const Weapon* storedWeapon = dynamic_cast<Weapon*>(currentItem.get());
                // Compare damage for weapons
                return (currentWeapon != nullptr && storedWeapon != nullptr && currentWeapon->getDamage() == storedWeapon->getDamage());
            }
            case ItemType::ARMOUR:{
                const Armour* currentArmour = dynamic_cast<const Armour*>(&other);
                const Armour* storedArmour = dynamic_cast<Armour*>(currentItem.get());
                // Compare armour stats
                return (currentArmour != nullptr && storedArmour != nullptr && currentArmour->getArmourStat() == storedArmour->getArmourStat());
            }
            case ItemType::POTION:{
                const Potion* currentPotion = dynamic_cast<const Potion*>(&other);
                const Potion* storedPotion = dynamic_cast<Potion*>(currentItem.get());
                // Compare recovery amount for potions
                return (currentPotion != nullptr && storedPotion != nullptr && currentPotion->getRecoveryAmount() == storedPotion->getRecoveryAmount());
            }
        }
    }
    return false; // If no conditions matched, return false
}


std::ostream& operator<<(std::ostream& out, const ItemStack& stack) {
    if (stack.currentItem) {
        out << *stack.currentItem;
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
    return currentItem.get();
}

const Item* ItemStack::getItem() const {
    return currentItem.get();
}

// Serialize
std::string ItemStack::serialize() const {
    std::ostringstream oss;
    oss << (currentItem ? currentItem->serialize() : "null") << "\n" << quantity;
    return oss.str();
}

// Deserialize
bool ItemStack::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string itemData;

    // Deserialize the item data
    if (!std::getline(iss, itemData)) return false;

    if (itemData == "null") {
        currentItem.release();
    } else {
        std::istringstream itemStream(itemData);
        int itemType;
        if (!(itemStream >> itemType)) return false;

        switch (static_cast<ItemType>(itemType)) {
            case ItemType::WEAPON:
                currentItem = make_unique<Weapon>();
                break;
            case ItemType::ARMOUR:
                currentItem = make_unique<Armour>();
                break;
            case ItemType::POTION:
                currentItem = make_unique<Potion>();
                break;
            default:
                return false;
        }

        if (!currentItem->deserialize(itemData)) {
            currentItem.reset();
            return false;
        }
    }

    // Deserialize the quantity
    if (!(iss >> quantity)) {
        currentItem.reset();
        return false;
    }

    return true;
}