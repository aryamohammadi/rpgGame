#pragma once 
#define INSERTIONSORT_H
#include "../header/sort.h"
class InsertionSort : public AbstractItemSort{
    public:
        InsertionSort(CompareItem::CompareBy sortMode):AbstractItemSort(sortMode){}
        void sort(vector<ItemStack*>& array, SortOrder order, CompareItem::CompareBy mode) override{
            for(unsigned i = 1; i < array.size(); i++){
                int j = i - 1;
                while( j < array.size() && !CompareItem::compare(array[j + 1]->getItem(), array[j]->getItem(), mode, order)){
                    swap(array[j+1], array[j]);
                    j++;
                }
            }
        }
};