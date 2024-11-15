#pragma once
#define COMPARE_H
#include "../header/sort.h"
#include "../header/item.h"

class CompareItem{
    private:
        SortOrder order;
    public:
        enum CompareBy{
            Type,
            Grade,
            Name,
            Time
        };
        CompareBy compareBy;
        CompareItem(CompareBy by, SortOrder order = SortOrder::Ascending):compareBy(by), order(order){}

        bool operator()(const Item& item1, const Item& item2) const {
            switch(compareBy){
                case CompareBy::Grade:
                    if(order == SortOrder::Ascending && item1.itemGrade < item2.itemGrade){
                        return true;
                    }
                    if(order == SortOrder::Descending && item1.itemGrade > item2.itemGrade){
                        return true;
                    }
                case CompareBy::Type:
                    if(order == SortOrder::Ascending && item1.type < item2.type){
                        return true;
                    }
                    if(order == SortOrder::Descending && item1.type > item2.type){
                        return true;
                    }
            }
            return false;
        }
};