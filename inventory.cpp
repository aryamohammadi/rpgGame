#include "inventory.h"

bool Inventory::itemFound(const string& name){
    if(size == 0){
        return false;
    }
    for(Item* item : items){
        if(item->getName() == name){
            return true;
        }
    }
    return false;
}

void Inventory::addItem(Item* item){
    if(item == nullptr){
        return;
    }
    items.push_back(item);
    size ++;
}