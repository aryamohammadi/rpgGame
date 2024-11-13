#include "inventory.h"
#include <stdexcept>
bool Inventory::itemFound(const string& name){
    if(size == 0){
        return false;
    }
    for(Item* item : items){
        if(item != nullptr && item->getName() == name){
            return true;
        }
    }
    return false;
}

void Inventory::addItem(Item* item){
    if(sizeGreaterThanOrEqualToCapacity()){
        throw std::overflow_error("size of " + std::to_string(size) + " >= capacity of " + std::to_string(capacity) + '\n');
    }
    items.at(size) = item;
    size ++;
}

void Inventory::removeItem(const string& name){
    if(isEmpty()){
        throw std::underflow_error("Removing from empty inventory!\n");
    }
    if(!itemFound(name)){
        throw std::invalid_argument("name " + name + " not found in inventory!");
    }
    for(unsigned i = 0; i < size; i++){
        if(items[i]->getName() == name){
            if(i == size - 1){
                items[i] = nullptr;
                size --;
                break;
            }
            else if(i == 0){
                items[i] = nullptr;
                size --;
                break;
            }
            else{
                items[i] = nullptr;
                reorganizeItems();
                size --;
                break;
            }
        }
    }
}

void Inventory::reorganizeItems(){
    vector<Item*> itemsNew;

    for(unsigned i = 0; i < size; i++){
        if(items[i] != nullptr){
            itemsNew.push_back(items[i]);
        }
    }

    itemsNew.reserve(capacity);

    items = itemsNew;
}

ostream& operator<<(ostream& out, const Inventory& rhs){
    if(rhs.isEmpty()){
        return out;
    }
    for(Item* item : rhs.items){
        if(item != nullptr){
            out << *item;
            out << std::endl;
        }
    }
    return out;
}