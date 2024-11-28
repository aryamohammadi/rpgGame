#pragma once

#include "../header/itemStack.h"
#include "../header/compare.h"
#include "../header/sortorder.h"
#include "../header/compareItemType.h"
#include "../header/itemType.h"
class AbstractItemTypeSort{
    protected:
        CompareItemTypeCharacteristics::Characteristics attribute;
        CompareBy sortConfig;
        ItemType type;
    public:
        AbstractItemTypeSort(CompareBy sortMode, CompareItemTypeCharacteristics::Characteristics attribute, ItemType type):sortConfig(sortMode), attribute(attribute), type(type){}
        virtual void sort(vector<ItemStack*>& array, SortOrder order) = 0;
        bool isSorted(const std::vector<ItemStack*>& array, SortOrder order) const{
            for(unsigned i = 1; i < array.size(); i++){
                if(array[i] == nullptr){
                    if(i + 1 < array.size() && array[i + 1] != nullptr){
                        return false; //any holes 
                    }
                    return true; //no holes, so end of array
                }
                if(!CompareItemTypeCharacteristics::compare(array[i - 1]->getItem(), array[i]->getItem(), attribute, type, order)){
                    return false;
                }
            }
            return true;
        }
};