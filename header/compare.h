#pragma once
#define COMPARE_H
#include "../header/sort.h"
#include "../header/item.h"
#include "sort.h"
#include "item.h"
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
                case CompareBy::Type:
                    if(order == SortOrder::Ascending && item1->getType() < item2->getType()){
                        return true;
                    }
                    if(order == SortOrder::Descending && item1->getType() > item2->getType()){
                        return true;
                    }
            }
            return false;
        }
};