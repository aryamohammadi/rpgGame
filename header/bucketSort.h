#pragma once
#define BUCKETSORT_H
#include "../header/sort.h"
class BucketSort : public AbstractItemSort{

    public: 
        BucketSort(CompareItem::CompareBy sortMode):AbstractItemSort(sortMode){}
        void sort(vector<ItemStack*>& array, SortOrder order, CompareItem::CompareBy mode) override;
};