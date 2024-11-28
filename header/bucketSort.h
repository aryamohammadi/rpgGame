#pragma once

#include "../header/sort.h"
#include "../header/compareItemType.h"
#include "../header/sortItemType.h"
#include "../header/itemTypeInsertionSort.h"
class BucketSort : public AbstractItemTypeSort{
    private:
        void addPotions(vector<ItemStack*>& array, vector<ItemStack*>& potions, int& currentIndex, int size, bool& complete){
            for(ItemStack*& stack : potions){
                if(currentIndex >= size){
                    break;
                }
                array[currentIndex] = stack;
                stack = nullptr;
                currentIndex ++;
            }
            complete = true;
        }
        void addWeapons(vector<ItemStack*>& array, vector<ItemStack*>& weapons, int& currentIndex, int size, bool& complete){
            for(ItemStack*& stack : weapons){
                if(currentIndex >= size){
                    break;
                }
                array[currentIndex] = stack;
                stack = nullptr;
                currentIndex ++;
            }
            complete = true;
        }
        void addArmour(vector<ItemStack*>& array, vector<ItemStack*>& armour, int& currentIndex, int size, bool& complete){
            for(ItemStack*& stack : armour){
                if(currentIndex >= size){
                    break;
                }
                array[currentIndex] = stack;
                stack = nullptr;
                currentIndex ++;
            }
            complete = true;
        }
    public: 
        BucketSort(CompareBy sortMode, CompareItemTypeCharacteristics::Characteristics attribute, ItemType type):AbstractItemTypeSort(sortMode, attribute, type){}
        void sort(vector<ItemStack*>& array, SortOrder order) override{
            if(sortConfig == CompareBy::Type){
                vector<ItemStack*> weaponsBucket;
                vector<ItemStack*> potionsBucket;
                vector<ItemStack*> armourBucket;
                //organize into buckets
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
                //clear array
                int size = 0;
                for(ItemStack*& stack : array){
                    if(stack == nullptr){
                        break;
                    }
                    delete stack;
                    stack = nullptr;
                    size ++;
                }

                //sort 
                ItemTypeInsertionSort weaponSort(sortConfig, attribute, ItemType::WEAPON);
                weaponSort.sort(weaponsBucket, order); 

                ItemTypeInsertionSort armourSort(sortConfig, attribute, ItemType::ARMOUR);
                armourSort.sort(armourBucket, order);

                ItemTypeInsertionSort potionSort(sortConfig, attribute, ItemType::WEAPON);
                potionSort.sort(weaponsBucket, order);

                //combine arrays
                int index = 0;
                bool weaponsAdded = false;
                bool potionsAdded = false;
                bool armourAdded = false;
                if(type == ItemType::WEAPON){
                    addWeapons(array, weaponsBucket, index, size, weaponsAdded);
                }
                else if(type == ItemType::ARMOUR){
                    addArmour(array, armourBucket, index, size, armourAdded);
                }
                else{
                    addPotions(array, potionsBucket, index, size, potionsAdded);
                }
                while(!potionsAdded || !weaponsAdded || !armourAdded){
                    if(!potionsAdded){
                        addPotions(array, potionsBucket, index, size, potionsAdded);
                    }
                    else if(!weaponsAdded){
                        addWeapons(array, weaponsBucket, index, size, weaponsAdded);
                    }
                    else{
                        addArmour(array, armourBucket, index, size, armourAdded);
                    }
                }
            }
            else{
                InsertionSort s(sortConfig);
                s.sort(array, order);
            }
        }
};