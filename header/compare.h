#pragma once
#include "../header/sortorder.h"
#include "../header/item.h"
#include "../header/compareBy.h"
#include <cmath>
class CompareItem{
        private:
                SortOrder order;
                bool compareName(const std::string& lowerName, const std::string& upperName) const;     
                bool compareTime(double lowerTime, double upperTime) const;
        public:
                CompareItem(SortOrder order):order(order){}
                static bool compare(const Item* lowerBound, const Item* upperBound, CompareBy compareBy, SortOrder order);
};