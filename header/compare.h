#pragma once
#include "../header/sortorder.h"
#include "../header/item.h"
#include "../header/compareBy.h"
#include <cmath>
class CompareItem{
        private:
            bool compareType();
    public:
        static bool compare(const Item* lowerBound, const Item* upperBound, CompareBy compareBy, SortOrder order);
};