#include "../header/itemStack.h"
#include "../header/item.h"
#include "../header/weapon.h"
#include "../header/armour.h"
#include "../header/potion.h"
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
    if(item->getName() == other.getName() && item->getType() == other.getType()){
        
        switch(other.getType()){
            case ItemType::WEAPON:{
                const Weapon& currentWeapon = dynamic_cast<const Weapon&>(other);
                if(currentWeapon.getDamage() == dynamic_cast<Weapon*>(item)->getDamage()){
                    return true;
                }
                return false;
            }
            case ItemType::ARMOUR:{
                const Armour& currentArmour = dynamic_cast<const Armour&>(other);
                if(currentArmour.getArmourStat() == dynamic_cast<Armour*>(item)->getArmourStat()){
                    return true;
                }
                return false;
            }
            case ItemType::POTION:{
                const Potion& currentPotion = dynamic_cast<const Potion&>(other);
                if(currentPotion.getRecoveryAmount() == dynamic_cast<Potion*>(item)->getRecoveryAmount()){
                    return true;
                }
                return false;
            }
        }
    }
    return false;
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
