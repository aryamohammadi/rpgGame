#pragma once
#define SORT_H
#include "../header/itemStack.h"

template<typename T>
class AbstractSort{

    public:
        enum class SortOrder{
            Ascending,
            Descending
        };
        virtual void sort(vector<T>& array, SortOrder order = SortOrder::Ascending) = 0;
        bool isSorted(const vector<T>& array, SortOrder order = SortOrder::Ascending) const {
            for(unsigned i = 1; i < array.size(); i++){
                if((order == SortOrder::Ascending && array[i] < array[i - 1]) ||(order == SortOrder::Descending && array[i] > array[i - 1])){
                    return false;
                }
            }
            return true;
        }
};