#pragma once

#include "../header/compare.h"
#include "../header/itemType.h"
class CompareItemTypeCharacteristics{
    private:
        ItemType type;
    public: 
        CompareItemTypeCharacteristics(ItemType type):type(type){}
        enum Characteristics{
            None,
            Damage,
            recoveryAmount,
            armourStat
        };
        static bool compare(const Item* lowerBound, const Item* upperBound, Characteristics attributes, ItemType type, SortOrder order = SortOrder::Ascending);
        int getTypeRank(const Item* item) const;
        bool compareRank(const Item* lowerBound, const Item* upperBound, SortOrder order) const;
};
