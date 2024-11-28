#include "../header/compareItemType.h"
#include "../header/weapon.h"
#include "../header/potion.h"
#include "../header/armour.h"
bool CompareItemTypeCharacteristics::compare(const Item* lowerBound, const Item* upperBound, Characteristics attributes, ItemType type, SortOrder order = SortOrder::Ascending) {
    CompareItemTypeCharacteristics compareObject(type);
        const Weapon* lowerWeapon = dynamic_cast<const Weapon*>(lowerBound);
        const Weapon* upperWeapon = dynamic_cast<const Weapon*>(upperBound);
        const Armour* lowerArmour= dynamic_cast<const Armour*>(lowerBound);
        const Armour* upperArmour = dynamic_cast<const Armour*>(upperBound);
        const Potion* lowerPotion= dynamic_cast<const Potion*>(lowerBound);
        const Potion* upperPotion = dynamic_cast<const Potion*>(upperBound);
    switch(attributes){
        case Characteristics::None:
            throw std::invalid_argument("Not a valid argument for itemCompare!");
        case Characteristics::Damage:
            if(lowerWeapon == nullptr || upperWeapon == nullptr){
                return compareObject.compareRank(lowerBound, upperBound, order);
            }
            if(order == SortOrder::Ascending){
                return (lowerWeapon->getDamage() < upperWeapon->getDamage());
            }
            else{
                return (lowerWeapon->getDamage() > upperWeapon->getDamage());
            }
          
        case Characteristics::armourStat:
            if(lowerArmour == nullptr || upperArmour == nullptr){
                return compareObject.compareRank(lowerBound, upperBound, order);
            }
            if(order == SortOrder::Ascending){
                return (lowerArmour->getArmourStat() < upperArmour->getArmourStat());
            }
            else{
                return (lowerArmour->getArmourStat() > upperArmour->getArmourStat());
            }
        case Characteristics::recoveryAmount:
            if(lowerArmour == nullptr || upperArmour == nullptr){
                return compareObject.compareRank(lowerBound, upperBound, order);
            }
            if(order == SortOrder::Ascending){
                return (lowerPotion->getRecoveryAmount() < upperPotion->getRecoveryAmount());
            }
            else{
                return (lowerPotion->getRecoveryAmount() > upperPotion->getRecoveryAmount());
            }
        default:
            throw std::invalid_argument("Not a valid argument for itemCompare!");
    }
}

int CompareItemTypeCharacteristics::getTypeRank(const Item* item) const{
    switch(type){
        case ItemType::WEAPON:
            if(dynamic_cast<const Weapon*>(item)){
                return 1;
            }
            return 0;
        case ItemType::ARMOUR:
            if(dynamic_cast<const Armour*>(item)){
                return 1;
            }
            return 0;
        case ItemType::POTION:
            if(dynamic_cast<const Potion*>(item)){
                return 1;
            }
            return 0;
        default:
            throw std::logic_error("getTypeRank: Invalid item type used!");
    }
}

bool CompareItemTypeCharacteristics::compareRank(const Item* lowerBound, const Item* upperBound, SortOrder order) const{
    if(order == SortOrder::Ascending){
        return (getTypeRank(lowerBound) < getTypeRank(upperBound));
    }
    else{
        return(getTypeRank(lowerBound) > getTypeRank(upperBound));
    }
}