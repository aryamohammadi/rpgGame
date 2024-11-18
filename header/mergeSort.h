#pragma once
#define MERGESORT_H

#include "../header/sort.h"

class MergeSort : public AbstractItemSort{
    private:
        void merge(vector<ItemStack*>& array, SortOrder order, int left, int mid, int right);
        void mergeSort(vector<ItemStack*>& array, SortOrder order, int left, int right);
    public:
        MergeSort(CompareItem::CompareBy sortMode):AbstractItemSort(sortMode){}
        void sort(vector<ItemStack*>& array, SortOrder order) override;

};