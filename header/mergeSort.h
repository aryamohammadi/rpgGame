#pragma once


#include "../header/sort.h"

class MergeSort : public AbstractItemSort{
    private:
        void merge(vector<unique_ptr<ItemStack>>& array, SortOrder order, int left, int mid, int right);
        void mergeSort(vector<unique_ptr<ItemStack>>& array, SortOrder order, int left, int right);
    public:
        MergeSort(CompareBy sortMode):AbstractItemSort(sortMode){}
        void sort(vector<unique_ptr<ItemStack>>& array, SortOrder order) override{
            mergeSort(array, order, 0, array.size() - 1);
        }

};