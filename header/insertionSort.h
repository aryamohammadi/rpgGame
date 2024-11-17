#pragma once 
#define INSERTIONSORT_H
#include "../header/sort.h"
using namespace std;
class InsertionSort : public AbstractItemSort{
    public:
        InsertionSort(CompareItem::CompareBy sortMode):AbstractItemSort(sortMode){}
        void sort(vector<ItemStack*>& array, SortOrder order, CompareItem::CompareBy mode) override{
            for(unsigned i = 1; i < array.size(); i++){
                int j = i - 1;
                ItemStack* key = array[i];
                while(j >= 0 && !CompareItem::compare(array[j]->getItem(), key->getItem(), mode, order)){
                    array[j + 1] = array[j];
                    j--;
                }
                array[j + 1] = key;
            }
        }
};