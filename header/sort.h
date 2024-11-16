#pragma once
#define SORT_H
#include "../header/itemStack.h"
#include "../header/compare.h"
enum class SortOrder{
    Ascending,
    Descending
};
class AbstractItemSort{
    enum SortBy{
        Name, 
        Time,
        Type,
        Grade
    };
    SortBy sortConfig;
    public:
        AbstractItemSort(SortBy sortMode):sortConfig(sortMode){}
        virtual void sort(vector<ItemStack*>& array, SortOrder order = SortOrder::Ascending) = 0;
        bool isSorted(const vector<ItemStack*>& array, SortOrder order = SortOrder::Ascending) const {
            for(unsigned i = 1; i < array.size(); i++){
                if((order == SortOrder::Ascending && array[i]->getItem() < array[i - 1]->getItem()) ||(order == SortOrder::Descending && array[i] > array[i - 1])){
                    return false;
                }
            }
            return true;
        }
};