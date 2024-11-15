#pragma once
#define SORT_H
#include "../header/itemStack.h"
enum class SortOrder{
    Ascending,
    Descending
};
template<typename T>
class AbstractSort{

    public:
        virtual void sort(vector<itemStack*>& array, SortOrder order = SortOrder::Ascending) = 0;
        bool isSorted(const vector<itemStack*>& array, SortOrder order = SortOrder::Ascending) const {
            for(unsigned i = 1; i < array.size(); i++){
                if((order == SortOrder::Ascending && array[i]->item < array[i - 1]->item) ||(order == SortOrder::Descending && array[i] > array[i - 1])){
                    return false;
                }
            }
            return true;
        }
};