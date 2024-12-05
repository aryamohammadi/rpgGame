#include "../header/compare.h"

bool CompareItem::compare(const Item* lowerBound, const Item* upperBound, CompareBy compareBy, SortOrder order){
    if(lowerBound == nullptr){
        throw std::invalid_argument("compare: lowerBound nullptr!");
    }
    if(upperBound == nullptr){
        throw std::invalid_argument("compare: upperBound nullptr!");
    }
    CompareItem compareValues(order);
    switch(compareBy){
        case CompareBy::Name:
            return compareValues.compareName(lowerBound->getName(), upperBound->getName());
        case CompareBy::Time:
            return compareValues.compareTime(lowerBound->getTime(), upperBound->getTime());
        default:
            throw std::invalid_argument("Compare: Invalid compareBy");
    }
}

bool CompareItem::compareName(const std::string& lowerName, const std::string& upperName) const{
    switch(order){
        case SortOrder::Ascending:{
            return lowerName <= upperName;
        }
        case SortOrder::Descending:{
            return lowerName >= upperName;
        }
        default:
            throw std::logic_error("compareTime: SortOrder type invalid");
    }
}
bool CompareItem::compareTime(double lowerTime, double upperTime) const{
    if(std::fabs(lowerTime - upperTime) < 1e-6){
        return true;
    }
    switch(order){
        case SortOrder::Ascending:{
            return lowerTime <= upperTime;
        }
        case SortOrder::Descending:{
            return lowerTime <= upperTime;
        }
        default:
            throw std::logic_error("compareTime: SortOrder type invalid");
    }
}