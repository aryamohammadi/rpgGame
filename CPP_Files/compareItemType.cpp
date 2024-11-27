#include "../header/compareItemType.h"
#include "../header/weapon.h"
#include "../header/potion.h"
#include "../header/armour.h"
bool CompareItemTypeCharacteristics::compare(Item* lowerBound, Item* upperBound, Characteristics attributes, ItemType type, SortOrder order = SortOrder::Ascending) {
    switch(attributes){
        case Characteristics::None:
            throw std::invalid_argument("Not a valid argument for itemCompare!");
        break;
        case Characteristics::Damage:
            if(dynamic_cast<Weapon*>(lowerBound) == nullptr){
                
            }
    }
    return true;
}