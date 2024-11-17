#pragma once
#define COMPAREITEMTYPE_H
#include "../header/compare.h"
class CompareItemTypeCharacteristics{
    public: 
        enum Characteristics{
            None
        };
        static bool compare(const Item* lowerBound, const Item* upperBound, Characteristics attributes, SortOrder order = SortOrder::Ascending) {
            return true;
        }
};