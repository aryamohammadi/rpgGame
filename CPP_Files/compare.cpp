#include "../header/compare.h"

bool CompareItem::compare(const Item* lowerBound, const Item* upperBound, CompareBy compareBy, SortOrder order){
    switch(compareBy){
        case CompareBy::Type:
            throw std::logic_error("Compare: Not comparing types!");
        case CompareBy::Name:
            if(order == SortOrder::Descending && upperBound->getName() <= lowerBound->getName()){
                return true;
            }
            if(order == SortOrder::Ascending && upperBound->getName() >= lowerBound->getName()){
                return true;
            }
            break;
        case CompareBy::Time:
            if (std::fabs(lowerBound->getTime() - upperBound->getTime()) < 1e-6) {
                return true; // Treat approximately equal times as equal
            }
            if(order == SortOrder::Descending && upperBound->getTime() <= lowerBound->getTime()){
                return true;
            }
            if(order == SortOrder::Ascending && upperBound->getTime() >= lowerBound->getTime()){
                return true;
            }
            break;
        default:
            throw std::invalid_argument("Compare: Invalid compareBy");
    }
    return false;
}