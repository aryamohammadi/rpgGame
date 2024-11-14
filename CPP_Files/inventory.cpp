#include "../header/inventory.h"
#include <stdexcept>
using std::endl;
using std::to_string;
using std::exception;
int Inventory::itemFound(const Item& item) const {
    if(size == 0){
        return -1;
    }
    for(unsigned i = 0; i < size; i++){
        if(items[i] != nullptr && items[i]->isItem(item)){
            return i;
        }
    }
    return -1;
}

int Inventory::itemFound(const string& name) const {
    if(size == 0){
        return -1;
    }
    for(unsigned i = 0; i < size; i ++){
        if(items[i] != nullptr && items[i]->item->getName() == name){
            return i;
        }
    }
    return -1;
}

int Inventory::itemFound(const string& name, Item::ItemType t) const {
    if(size == 0){
        return -1;
    }
    for(unsigned i = 0; i < size; i ++){
        if(items[i] != nullptr && items[i]->item->getName() == name && items[i]->item->getType() == t){
            return i;
        }
    }
    return -1;
}


void Inventory::addItem(Item* item){
    if(sizeGreaterThanOrEqualToCapacity()){
        throw std::overflow_error("size of " + std::to_string(size) + " >= capacity of " + std::to_string(capacity) + '\n');
    }
    items.at(size) = new ItemStack(item);
    size ++;
}

void Inventory::addItem(Item* item, int quantity){
    if(sizeGreaterThanOrEqualToCapacity()){
        throw std::overflow_error("size of " + std::to_string(size) + " >= capacity of " + std::to_string(capacity) + '\n');
    }
    items.at(size) = new ItemStack(item, quantity);
    size ++;
}

void Inventory::removeItem(const Item& item){
    if(isEmpty()){
        throw std::underflow_error("Removing from empty inventory!\n");
    }
    int index = itemFound(item);
    if(index == -1){
        throw std::invalid_argument("item named " + item.getName() + " not found!");
    }
    delete items[index];
    items[index] = nullptr;
    reorganizeItems();
    size --;
}

int Inventory::itemsWithName(const string& name) const{
    if(itemFound(name) == -1){
        
    }
    return count;
}

void Inventory::reorganizeItems(){
    
    vector<ItemStack*> itemsNew;
    for(unsigned i = 0; i < size; i++){
        if(items[i] != nullptr){
            itemsNew.push_back(items[i]);
        }
    }
    items = itemsNew;
}


ostream& operator<<(ostream& out, const Inventory& rhs){
    if(rhs.isEmpty()){
        return out;
    }
    for(unsigned i = 0; i < rhs.size; i++){
        if(rhs.items[i] != nullptr){
            out << "Item " + std::to_string(i) << std::endl;
            out << *rhs.items[i] << endl;
        }
    }
    return out;
}

void Inventory::removeItem(const string& name){
    int index = itemFound(name);
    if(index == -1){
        throw std::invalid_argument("Item nammed " + name + " not in inventory!");
    }
    delete items[index];
    items[index] = nullptr;
    reorganizeItems();
    size --;
}