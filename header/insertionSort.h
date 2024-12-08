#pragma once 

#include "../header/sort.h"
using namespace std;
class InsertionSort : public AbstractItemSort{
    public:
        InsertionSort(CompareBy sortMode):AbstractItemSort(sortMode){}
        void sort(vector<unique_ptr<ItemStack>>& array, SortOrder order) override{
            for(unsigned i = 1; i < array.size(); i++){
                int j = i - 1;
                unique_ptr<ItemStack> key = make_unique<ItemStack>(*array[i]);
                while(j >= 0 && !CompareItem::compare(array[j]->getItem(), key->getItem(), sortConfig, order)){
                    array[j + 1] = move(array[j]);
                    j--;
                }
                array[j + 1] = move(key);
            }
        }
};
