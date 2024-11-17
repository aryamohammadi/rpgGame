#pragma once
#define COMPARE_H
#include "../header/sortorder.h"
#include "../header/item.h"
class CompareItem{
    public:
        enum CompareBy{
            Type,
            Grade,
            Name,
            Time
        };
        static bool compare(const Item* item1, const Item* item2, CompareBy compareBy, SortOrder order = SortOrder::Ascending){
            switch(compareBy){
                case CompareBy::Grade:
                    if(order == SortOrder::Ascending && item1->getGrade() < item2->getGrade()){
                        return true;
                    }
                    if(order == SortOrder::Descending && item1->getGrade() > item2->getGrade()){
                        return true;
                    }
                    break;
                case CompareBy::Type:
                    if(order == SortOrder::Ascending && item1->getType() < item2->getType()){
                        return true;
                    }
                    if(order == SortOrder::Descending && item1->getType() > item2->getType()){
                        return true;
                    }
                    break;
            }
            return false;
        }
};

class CompareItemTypeCharacteristics{
    public: 
        enum Characteristics{

        };
        static bool compare(const Item* item1, const Item* item2, Characteristics attributes, SortOrder order = SortOrder::Ascending) {
            return true;
        }
};