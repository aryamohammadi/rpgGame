#pragma once
#define BUCKETSORT_H
#include "../header/sort.h"
#include "../header/compareItemType.h"
class BucketSort : public AbstractItemSort{
    private:
        CompareItemTypeCharacteristics::Characteristics attribute;
    public: 
        BucketSort(CompareItem::CompareBy sortMode, CompareItemTypeCharacteristics::Characteristics attribute = CompareItemTypeCharacteristics::Characteristics::None):AbstractItemSort(sortMode), attribute(attribute){}
        void sort(vector<ItemStack*>& array, SortOrder order) override{
            if(sortConfig == CompareItem::CompareBy::Type){
                vector<ItemStack*> weaponsBucket;
                vector<ItemStack*> potionsBucket;
                vector<ItemStack*> armourBucket;

                for(ItemStack* stack : array){
                    if(stack == nullptr){
                        break;
                    }
                    Item::ItemType curr = stack->getItem()->getType();
                    switch(curr){
                        case Item::ItemType::WEAPON:
                            weaponsBucket.push_back(new ItemStack(*stack));
                            break;
                        case Item::ItemType::ARMOUR:
                            armourBucket.push_back(new ItemStack(*stack));
                            break;
                        case Item::ItemType::POTION:
                            potionsBucket.push_back(new ItemStack(*stack));
                            break;
                    }
                }
                

            }
            else{
                InsertionSort s(sortConfig);
                s.sort(array, order);
            }
        }
};