#pragma once
#define SORT_H
#include "../header/itemStack.h"
#include "../header/compare.h"
enum class SortOrder{
    Ascending,
    Descending
};
class AbstractItemSort{
    protected:
    CompareItem::CompareBy sortConfig;
    public:
        AbstractItemSort(CompareItem::CompareBy sortMode):sortConfig(sortMode){}
        virtual void sort(vector<ItemStack*>& array, SortOrder order = SortOrder::Ascending, CompareItem::CompareBy mode) = 0;
        bool isSorted(const vector<ItemStack*>& array, SortOrder order = SortOrder::Ascending, CompareItem::CompareBy mode) const {
            for(unsigned i = 1; i < array.size(); i++){
                if((order == SortOrder::Ascending && array[i]->getItem() < array[i - 1]->getItem()) ||(order == SortOrder::Descending && array[i] > array[i - 1])){
                    return false;
                }
            }
            return true;
        }
};

class MockAbstractItemSort : public AbstractItemSort{
    public:
        MOCK_METHOD(void, sort, (vector<ItemStack*>& array, SortOrder order, CompareItem::CompareBy mode), (override));
};