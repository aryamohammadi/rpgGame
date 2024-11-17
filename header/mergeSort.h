#pragma once
#define MERGESORT_H

#include "../header/sort.h"

class MergeSort : public AbstractItemSort{

    public:
        MergeSort(CompareItem::CompareBy sortMode):AbstractItemSort(sortMode){}
        void sort(vector<ItemStack*>& array, SortOrder order, CompareItem::CompareBy mode) override;

};