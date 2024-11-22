#include "../header/compare.h"

bool CompareItem::compare(const Item* lowerBound, const Item* upperBound, CompareBy compareBy, SortOrder order = SortOrder::Ascending){
    switch(compareBy){
        case CompareBy::Grade:
            if(order == SortOrder::Descending && upperBound->getGrade() <= lowerBound->getGrade()){
                return true;
            }
            if(order == SortOrder::Ascending && upperBound->getGrade() >= lowerBound->getGrade()){
                return true;
            }
            break;
        case CompareBy::Type:
            if(order == SortOrder::Descending && upperBound->getType() <= lowerBound->getType()){
                return true;
            }
            if(order == SortOrder::Ascending && upperBound->getType() >= lowerBound->getType()){
                return true;
            }
            break;
        case CompareBy::Name:
            if(order == SortOrder::Descending && upperBound->getName() <= lowerBound->getName()){
                return true;
            }
            if(order == SortOrder::Ascending && upperBound->getName() >= lowerBound->getName()){
                return true;
            }
            break;
        case CompareBy::Time:
            if(order == SortOrder::Descending && upperBound->getTime() < lowerBound->getTime() || std::fabs(upperBound->getTime() - lowerBound->getTime()) < 1e-6){
                return true;
            }
            if(order == SortOrder::Ascending && upperBound->getTime() > lowerBound->getTime() || std::fabs(upperBound->getTime() - lowerBound->getTime()) < 1e-6){
                return true;
            }
            break;
    }
    return false;
}
