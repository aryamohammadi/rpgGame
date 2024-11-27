#pragma once

#include "../header/compare.h"
#include "../header/itemType.h"
class CompareItemTypeCharacteristics{
    public: 
        enum Characteristics{
            None,
            Damage,
            recoveryAmount,
            armourStat
        };
        static bool compare(Item* lowerBound, Item* upperBound, Characteristics attributes, ItemType type, SortOrder order = SortOrder::Ascending);
};
