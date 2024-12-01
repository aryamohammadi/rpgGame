#pragma once

#include "../header/sort.h"
#include "../header/compareItemType.h"
#include "../header/sortItemType.h"
class BucketSort : public AbstractItemTypeSort{

    public: 
        BucketSort(CompareItem::CompareBy sortMode, CompareItemTypeCharacteristics::Characteristics attribute = CompareItemTypeCharacteristics::Characteristics::None):AbstractItemTypeSort(sortMode, attribute){}
        void sort(vector<ItemStack*>& array, SortOrder order) override{
            if(sortConfig == CompareItem::CompareBy::Type){
                vector<ItemStack*> weaponsBucket;
                vector<ItemStack*> potionsBucket;
                vector<ItemStack*> armourBucket;

                for(ItemStack* stack : array){
                    if(stack == nullptr){
                        break;
                    }
                    ItemType curr = stack->getItem()->getType();
                    switch(curr){
                        case ItemType::WEAPON:
                            weaponsBucket.push_back(new ItemStack(*stack));
                            break;
                        case ItemType::ARMOUR:
                            armourBucket.push_back(new ItemStack(*stack));
                            break;
                        case ItemType::POTION:
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