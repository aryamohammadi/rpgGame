#pragma once
#include "../header/sortorder.h"
#include "../header/item.h"
#include "../header/compareItemType.h"
#include <cmath>
class CompareItem{
    public:
        enum CompareBy{
            Type,
            Grade,
            Name,
            Time
        };
        static bool compare(const Item* lowerBound, const Item* upperBound, CompareBy compareBy, SortOrder order);
};