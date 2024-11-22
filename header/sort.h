#pragma once

#include "../header/itemStack.h"
#include "../header/compare.h"
#include "../header/sortorder.h"
class AbstractItemSort{
    protected:
    CompareItem::CompareBy sortConfig;
    public:
        AbstractItemSort(CompareItem::CompareBy sortMode):sortConfig(sortMode){}
        virtual void sort(vector<ItemStack*>& array, SortOrder order) = 0;
        bool isSorted(const std::vector<ItemStack*>& array, SortOrder order) const{
            for(unsigned i = 1; i < array.size(); i++){
                if(array[i] == nullptr){
                    if(i + 1 < array.size() && array[i + 1] != nullptr){
                        return false; //any holes 
                    }
                    return true; //no holes, so end of array
                }
                if(!CompareItem::compare(array[i - 1]->getItem(), array[i]->getItem(), sortConfig, order)){
                    return false;
                }
            }
            return true;
        }

};

class MockAbstractItemSort : public AbstractItemSort{
    public:
        MockAbstractItemSort(CompareItem::CompareBy sortMode):AbstractItemSort(sortMode){}
        MOCK_METHOD(void, sort, (vector<ItemStack*>& array, SortOrder order), (override));
};