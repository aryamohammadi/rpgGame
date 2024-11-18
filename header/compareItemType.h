#pragma once
#define COMPAREITEMTYPE_H
#include "../header/compare.h"
class CompareItemTypeCharacteristics{
    public: 
        enum Characteristics{
            None
        };
        static bool compare(const Item* lowerBound, const Item* upperBound, Characteristics attributes, Item::ItemType type, SortOrder order = SortOrder::Ascending) {
            switch(attributes){
                case Characteristics::None:
                    throw std::invalid_argument("Not a valid argument for itemCompare!");
                break;
            }
            return true;
        }
};