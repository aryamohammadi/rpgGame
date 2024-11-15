#pragma once
#define COMPARE_H
#include "../header/sort.h"
#include "../header/item.h"
template<typename T>
class CompareItem{
    public:
        enum CompareBy{
            Type,
            Grade
        };
        CompareBy compareBy;
        CompareItem(CompareBy by):compareBy(by){}

        bool operator()(const Item& item1, const Item& item2) const {
            switch(compareBy){
                case CompareBy::Grade:
                    if(SortOrder::Ascending && item1.itemGrade < item2.itemGrade){
                        return true;
                    }
                    if(SortOrder::Descending && item1.itemGrade > item2.itemGrade){
                        return true;
                    }
                case CompareBy::Type:
                    if(SortOrder::Ascending && item1.itemGrade < item2.itemGrade){
                        return true;
                    }
                    if(SortOrder::Descending && item1.itemGrade > item2.itemGrade){
                        return true;
                    }
            }
            return false;
        }
};