#pragma once 

#include "../header/sort.h"
using namespace std;
class InsertionSort : public AbstractItemSort{
    public:
        InsertionSort(CompareBy sortMode):AbstractItemSort(sortMode){}
        void sort(vector<ItemStack*>& array, SortOrder order) override{
            for(unsigned i = 1; i < array.size(); i++){
                int j = i - 1;
                ItemStack* key = array[i];
                if(array[j - 1] == nullptr || key == nullptr){
                    return;
                }
                while(j >= 0 && !CompareItem::compare(array[j]->getItem(), key->getItem(), sortConfig, order)){
                    array[j + 1] = array[j];
                    j--;
                }
                array[j + 1] = key;
            }
        }
};
