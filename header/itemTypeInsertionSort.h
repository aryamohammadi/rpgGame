#pragma once

#include "../header/sort.h"
#include "../header/compareItemType.h"
#include "../header/sortItemType.h"

class ItemTypeInsertionSort : public AbstractItemTypeSort{
        public:
        ItemTypeInsertionSort(CompareBy sortMode, CompareItemTypeCharacteristics::Characteristics attribute, ItemType type):AbstractItemTypeSort(sortMode, attribute, type){}
        void sort(vector<ItemStack*>& array, SortOrder order) override{
            for(unsigned i = 1; i < array.size(); i++){
                int j = i - 1;
                ItemStack* key = array[i];
                while(j >= 0 && !CompareItemTypeCharacteristics::compare(array[j]->getItem(), key->getItem(), attribute, type, order)){
                    array[j + 1] = array[j];
                    j--;
                }
                array[j + 1] = key;
            }
        }
};