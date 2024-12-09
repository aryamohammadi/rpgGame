#include "../header/inventory.h"
#include "../header/item.h"
#include "../header/itemStack.h"
#include "../header/sort.h"
#include "../header/insertionSort.h"
#include "../header/mergeSort.h"

#include <stdexcept>
using std::endl;
using std::to_string;
using std::exception;
Inventory::Inventory(const Inventory& inventory2){
    *this = inventory2;
}

Inventory& Inventory::operator=(const Inventory& rhs){
    if(this != &rhs){
        clear();
        items.resize(rhs.capacity);
        size = rhs.size;
        for(unsigned i = 0; i < rhs.size; i++){
            if(rhs.items[i] == nullptr || rhs.items[i]->getItem() == nullptr){
                size --;
                items[i] = nullptr;
                continue;
            }
            items[i] = make_unique<ItemStack>(*rhs.items[i]);
        }
        capacity = rhs.capacity;
    }
    return *this;
}
int Inventory::itemFound(const Item* item) const{
    if(isEmpty() || item == nullptr){
        return -1;
    }
    for(unsigned i = 0; i < size; i++){
        if(items[i] != nullptr && items[i]->isItem(*item)){
            return i;
        }
    }
    return -1;
}
int Inventory::itemFound(const Item& item) const {
    if(isEmpty()){
        return -1;
    }
    for(unsigned i = 0; i < size; i++){
        if(items[i] != nullptr && items[i]->isItem(item)){
            return i;
        }
    }
    return -1;
}

int Inventory::itemFound(const std::string& name) const {
    if(isEmpty()){
        return -1;
    }
    for(unsigned i = 0; i < size; i ++){
        if(items[i]->getItem()->getName() == name){
            return i;
        }
    }
    return -1;
}

int Inventory::itemFound(const std::string& name, ItemType t) const {
    if(isEmpty()){
        return -1;
    }
    for(unsigned i = 0; i < size; i ++){
        if(items[i] != nullptr && items[i]->getItem() != nullptr && items[i]->getItem()->getName() == name && items[i]->getItem()->getType() == t){
            return i;
        }
    }
    return -1;
}

int Inventory::itemFound(int index) const{
    if(index < 0 || index >= size || isEmpty()){
        return -1;
    }
    return index;
}

void Inventory::addItem(Item* item){
    if(sizeGreaterThanOrEqualToCapacity()){
        resize();
    }
    if(itemFound(item) != -1){
        items.at(itemFound(item))->increaseQuantity(1);
    }
    else{
        // Clone the item using its clone method
        switch(item->getType()){
            case ItemType::POTION:{
                Potion* currentPotion = dynamic_cast<Potion*>(item);
                if(currentPotion == nullptr){
                    throw std::runtime_error("Potion failed dynamic cast!");
                }
                unique_ptr<Item> clonePotion = currentPotion->cloneUnique();
                items.push_back(make_unique<ItemStack>(move(clonePotion)));
                break;
            }
            case ItemType::WEAPON:{
                Weapon* currentWeapon = dynamic_cast<Weapon*>(item);
                if(currentWeapon == nullptr){
                    throw std::runtime_error("Weapon failed dynamic cast!");
                }
                unique_ptr<Item> cloneWeapon = currentWeapon->cloneUnique();
                items.push_back(make_unique<ItemStack>(move(cloneWeapon)));                
            }
            break;
            case ItemType::ARMOUR:{
                Armour* currentArmour = dynamic_cast<Armour*>(item);
                if(currentArmour == nullptr){
                    throw std::runtime_error("Armour failed dynamic cast!");
                }
                unique_ptr<Item> cloneArmour = currentArmour->cloneUnique();
                items.push_back(make_unique<ItemStack>(move(cloneArmour)));     
            }
            break;
            default:{
                MockItem* currentMock = dynamic_cast<MockItem*>(item);
                if(currentMock == nullptr){
                    throw std::runtime_error("Mock failed dynamic cast!");
                }
                unique_ptr<Item> cloneMock = currentMock->cloneUnique();
                items.push_back(make_unique<ItemStack>(move(cloneMock)));                
            }
            break;
        }
        size++;
    }
}


void Inventory::addItem(Item* item, int quantity){
    if(sizeGreaterThanOrEqualToCapacity()){
        resize();
    }
    if(itemFound(item) != -1){
        items.at(itemFound(item))->increaseQuantity(1);
    }
    else{
        // Clone the item using its clone method
        switch(item->getType()){
            case ItemType::POTION:{
                Potion* currentPotion = dynamic_cast<Potion*>(item);
                if(currentPotion == nullptr){
                    throw std::runtime_error("Potion failed dynamic cast!");
                }
                unique_ptr<Item> clonePotion = currentPotion->cloneUnique();
                items.push_back(make_unique<ItemStack>(move(clonePotion), quantity));
                break;
            }
            case ItemType::WEAPON:{
                Weapon* currentWeapon = dynamic_cast<Weapon*>(item);
                if(currentWeapon == nullptr){
                    throw std::runtime_error("Weapon failed dynamic cast!");
                }
                unique_ptr<Item> cloneWeapon = currentWeapon->cloneUnique();
                items.push_back(make_unique<ItemStack>(move(cloneWeapon), quantity));                
            }
            break;
            case ItemType::ARMOUR:{
                Armour* currentArmour = dynamic_cast<Armour*>(item);
                if(currentArmour == nullptr){
                    throw std::runtime_error("Armour failed dynamic cast!");
                }
                unique_ptr<Item> cloneArmour = currentArmour->cloneUnique();
                items.push_back(make_unique<ItemStack>(move(cloneArmour), quantity));     
            }
            break;
            default:{
                MockItem* currentMock = dynamic_cast<MockItem*>(item);
                if(currentMock == nullptr){
                    throw std::runtime_error("Mock failed dynamic cast!");
                }
                unique_ptr<Item> cloneMock = currentMock->cloneUnique();
                items.push_back(make_unique<ItemStack>(move(cloneMock), quantity));                
            }
            break;
        }
        size++;
    }
}

int Inventory::itemsWithName(const std::string& name) const{
    if(itemFound(name) == -1){
        return 0;
    }
    int count = 0;
    for(unsigned i = 0; i < size; i++){
        if(items[i] != nullptr && items[i]->getItem() != nullptr && items[i]->getItem()->getName() == name){
            count ++;
        }
    }
    return count;
}

void Inventory::reorganizeItems(){
    int currentIndex = 0;
    // Iterate through the items to move nullptr elements to the back
    while(currentIndex < size){
        // If the current item is nullptr, swap with the next non-null item
        if(items[currentIndex] == nullptr){
            int nextIndex = currentIndex + 1;
            // Find the next non-null item
            while(nextIndex < size && items[nextIndex] == nullptr) {
                nextIndex++;
            }

            if(nextIndex < size){
                // Swap nullptr with the next valid item
                swap(items[currentIndex], items[nextIndex]);
            }
        }
        currentIndex++;
    }
}



std::ostream& operator<<(std::ostream& out, const Inventory& rhs){
    if(rhs.isEmpty()){
        return out;
    }
    for(unsigned i = 0; i < rhs.size; i++){
        if(rhs.items[i] != nullptr){
            out << "Item " << i << ':' << std::endl;
            out << *rhs.items[i] << endl;
        }
    }
    return out;
}

void Inventory::sortAlphabetically(){
    MergeSort s(CompareBy::Name);
    s.sort(items, SortOrder::Ascending);
}

void Inventory::makeLatestFirst(){
    MergeSort s(CompareBy::Time);
    s.sort(items, SortOrder::Descending);
}

void Inventory::makeOldestFirst(){
    MergeSort s(CompareBy::Time);
    s.sort(items, SortOrder::Ascending);
}

void Inventory::removeItem(const string& name, ItemType t){
    if(isEmpty()){
        throw std::underflow_error("Removing from empty inventory!");
    }
    int index = itemFound(name,t);
    if(index == -1){
        throw invalid_argument("removeItem: Item not found!");
    }
    if(items[index] != nullptr && items[index]->getItem() != nullptr && items[index]->getItem()->getType() == ItemType::POTION && items[index]->currentQuantity() > 1){//for potions
        items[index]->decreaseQuantity(1);
    }
    else{
        items[index].reset(nullptr);
        reorganizeItems();
        size --;
    }
}

void Inventory::removeItem(const Item& item){
    if(isEmpty()){
        throw std::underflow_error("Removing from empty inventory!");
    }
    int index = itemFound(item);
    if(index == -1){
        throw std::invalid_argument("removeItem: Item is not in inventory!");
    }
    if(items[index] != nullptr && items[index]->getItem() != nullptr && items[index]->getItem()->getType() == ItemType::POTION && items[index]->currentQuantity() > 1){//for potions
        items[index]->decreaseQuantity(1);
    }
    else{
        items[index].reset(nullptr);
        reorganizeItems();
        size --;
    }
}

void Inventory::removeItem(const string& name){
    if(isEmpty()){
        throw std::underflow_error("Removing from empty inventory!");
    }
    int index = itemFound(name);
    if(index == -1){
        throw std::invalid_argument("removeItem: Item is not in inventory!");
    }
    if(items[index] != nullptr && items[index]->getItem() != nullptr && items[index]->getItem()->getType() == ItemType::POTION && items[index]->currentQuantity() > 1){//for potions
        items[index]->decreaseQuantity(1);
    }
    else{
        items[index].reset(nullptr);
        reorganizeItems();
        size --;
    }
}

ostream& Inventory::outputWeapons(ostream& out) const{
    for(unsigned i = 0; i < size; i++){
        if(items[i] != nullptr && items[i]->getItem() != nullptr && items[i]->getItem()->getType() == ItemType::WEAPON){
            out << *items[i];
        }
    }
    return out;
}

// Serialization
std::string Inventory::serialize() const {
    std::ostringstream oss;
    oss << size << "\n" << capacity << "\n";
    for (const auto& item : items) {
        if (item) {
            oss << item->serialize() << "\n";
        }
    }
    return oss.str();
}

// Deserialization
bool Inventory::deserialize(const std::string& data) {
    std::istringstream iss(data);
    if (!(iss >> size >> capacity)) return false;

    items.clear();
    items.reserve(capacity);

    std::string itemData;
    while (std::getline(iss, itemData)) {
        if (!itemData.empty()) {
            unique_ptr<ItemStack> stack = make_unique<ItemStack>(nullptr);
            if(stack->deserialize(itemData)) {
                items.push_back(std::move(stack));
            } else {
                return false;
            }
        }
    }
    return true;
}

void Inventory::clear(){
    size = 0;
    items.clear();
}

Item* Inventory::getItem(int index){
    if(itemFound(index) == -1){
        throw std::invalid_argument("Inventory getItem: index invald!");
    }
    return items[index]->getItem();
}

const Item* Inventory::getItem(int index) const{
    if(itemFound(index) == -1){
        throw std::invalid_argument("Inventory getItem: index invald!");
    }
    return items[index]->getItem();
}

void Inventory::resize(){
    items.resize(Inventory::capacity*2);

    capacity *= 2;
    
}