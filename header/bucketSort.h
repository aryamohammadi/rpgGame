#pragma once
#define BUCKETSORT_H
#include "sort.h"
class BucketSort : public AbstractItemSort{

    public:

        void sort(vector<ItemStack*>& array, SortOrder order, CompareItem::CompareBy mode) override;
};