#include "../header/item.h"
#include "../header/inventory.h"
#include "../header/sort.h"
#include "../header/insertionSort.h"
#include "../header/mergeSort.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <sstream>
using std::ostringstream;
using testing::Return;
using namespace std;

class MockAbstractItemSort : public AbstractItemSort{
    public:
        MockAbstractItemSort(CompareBy sortMode):AbstractItemSort(sortMode){}
        MOCK_METHOD(void, sort, (vector<unique_ptr<ItemStack>>& array, SortOrder order), (override));
};

TEST(SortTest, isSortedOneItemTest){
    MockAbstractItemSort s(CompareBy::Name);
    unique_ptr<Item> item;
    item.reset(new MockItem(ItemType::POTION, "Emilly",  "Hi"));
    vector<unique_ptr<ItemStack>> stacks;
    stacks.push_back(make_unique<ItemStack>(move(item)));

    EXPECT_TRUE(s.isSorted(stacks,SortOrder::Ascending));
    stacks.front() = nullptr;
}

TEST(SortTest, TwoItemsNotSortedInAscendingOrderTest){
    MockAbstractItemSort s(CompareBy::Name);
    unique_ptr<Item> item;
    item.reset(new MockItem(ItemType::POTION, "Emily"));
    vector<unique_ptr<ItemStack>> stacks;
    stacks.push_back(make_unique<ItemStack>(move(item)));
    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));
    stacks.push_back(make_unique<ItemStack>(move(item)));

    EXPECT_FALSE(s.isSorted(stacks,SortOrder::Ascending));
}

TEST(SortTest, TwoItemsNotSortedInDescendingOrderTest){
    MockAbstractItemSort s(CompareBy::Name);

    unique_ptr<Item> item;
    item.reset(new MockItem(ItemType::POTION, "Dragon Slayer Sword"));

    vector<unique_ptr<ItemStack>> stacks;
    stacks.push_back(make_unique<ItemStack>(move(item)));
    item.reset(new MockItem(ItemType::WEAPON, "Emily"));
    stacks.push_back(make_unique<ItemStack>(move(item)));

    EXPECT_FALSE(s.isSorted(stacks,SortOrder::Descending));
}

TEST(InsertionSortTest, multipleAscendingItemTest){
    unique_ptr<Item> item;

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    vector<unique_ptr<ItemStack>> stacks;

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    vector<unique_ptr<ItemStack>> results;

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    results.push_back(make_unique<ItemStack>(move(item)));

    InsertionSort s(CompareBy::Name);
    s.sort(stacks, SortOrder::Ascending);
    s.sort(results, SortOrder::Ascending);

    ostringstream out;
    ostringstream result;
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Ascending));
    for(unsigned i = 0; i < stacks.size(); i++){
        out << *stacks[i];
    }
    for(unsigned i = 0; i < results.size(); i++){
        result << *results[i];
    }
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(InsertionSortTest, multipleDescendingItemTest){
    unique_ptr<Item> item;

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    vector<unique_ptr<ItemStack>> stacks;

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    vector<unique_ptr<ItemStack>> results;

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    results.push_back(make_unique<ItemStack>(move(item)));
    InsertionSort s(CompareBy::Name);
    s.sort(stacks, SortOrder::Descending);

    ostringstream out;
    ostringstream result;
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Descending));

    for(unsigned i = 0; i < stacks.size(); i++){
        out << *stacks[i] << endl;
    }
    for(unsigned i = 0; i < results.size(); i++){
        result << *results[i] << endl;
    }

    EXPECT_EQ(out.str(), result.str());
    
}

TEST(InsertionSortTest, ascendingTimeSort){
    unique_ptr<Item> item;

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    vector<unique_ptr<ItemStack>> stacks;

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    vector<unique_ptr<ItemStack>> results;

    for(unsigned i = 0; i < stacks.size(); i++){
        results.push_back(make_unique<ItemStack>(*stacks[i]));
    }
    
    InsertionSort s(CompareBy::Time);
    s.sort(stacks, SortOrder::Ascending);

    ostringstream out;
    ostringstream result;
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Ascending));
    for(unsigned i = 0; i < stacks.size(); i++){
        out << *stacks[i] << endl;
    }
    for(unsigned i = 0; i < results.size(); i++){
        result << *results[i] << endl;
    }
    EXPECT_EQ(out.str(), result.str());
}

TEST(InsertionSortTest, descendingTimeSort){
    unique_ptr<Item> item;

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    vector<unique_ptr<ItemStack>> stacks;

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    vector<unique_ptr<ItemStack>> results;
    for(unsigned i = 0; i < stacks.size(); i++){
        results.push_back(make_unique<ItemStack>(*stacks[i]));
    }
    InsertionSort s(CompareBy::Time);
    s.sort(stacks, SortOrder::Descending);

    ostringstream out;
    ostringstream result;
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Descending));
    for(unsigned i = 0; i < stacks.size(); i++){
        out << *stacks[i] << endl;
    }
    for(int i = results.size() - 1; i >= 0; i--){
        result << *results[i] << endl;
    }
    EXPECT_EQ(out.str(), result.str());
}

TEST(MergeSortTest, multipleAscendingItemTest){
    unique_ptr<Item> item;

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    vector<unique_ptr<ItemStack>> stacks;

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    vector<unique_ptr<ItemStack>> results;

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emilly"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));
    results.push_back(make_unique<ItemStack>(move(item)));

    MergeSort s(CompareBy::Name);
    s.sort(stacks, SortOrder::Ascending);
    ostringstream out;
    ostringstream result;
    for(unsigned i = 0; i < results.size(); i++){
        result << *results[i] << endl;
    }
    for(unsigned i = 0; i < stacks.size(); i++){
        out << *stacks[i] << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Ascending));
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(MergeSortTest, multipleDescendingItemTest){
    unique_ptr<Item> item;

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    vector<unique_ptr<ItemStack>> stacks;

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    vector<unique_ptr<ItemStack>> results;

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emilly"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));
    results.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));
    results.push_back(make_unique<ItemStack>(move(item)));

    MergeSort s(CompareBy::Name);
    s.sort(stacks, SortOrder::Descending);

    ostringstream out;
    ostringstream result;

    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Descending));

    for(unsigned i = 0; i < stacks.size(); i++){
        out << *stacks[i] << endl;
    }   
    for(int i = results.size() - 1; i >= 0; i --){
        result << *results[i] << endl;
    }
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(MergeSortTest, ascendingTimeSort){
    unique_ptr<Item> item;

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    vector<unique_ptr<ItemStack>> stacks;

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    vector<unique_ptr<ItemStack>> results;
    for(unsigned i = 0; i < stacks.size(); i++){
        results.push_back(make_unique<ItemStack>(*stacks[i]));
    }
    
    MergeSort s(CompareBy::Time);
    s.sort(stacks, SortOrder::Ascending);

    ostringstream out;
    ostringstream result;
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Ascending));
    for(unsigned i = 0; i < stacks.size(); i++){
        out << *stacks[i] << endl;
    }
    for(unsigned i = 0; i < results.size(); i++){
        result << *results[i] << endl;
    }
    EXPECT_EQ(out.str(), result.str());
}

TEST(MergeSortTest, descendingimeSort){
    unique_ptr<Item> item;

    item.reset(new MockItem(ItemType::POTION, "Emilly"));

    vector<unique_ptr<ItemStack>> stacks;

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Emily's Elixir"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Healing Tonic"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Excalibur"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::POTION, "Mana Brew"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::WEAPON, "Thunder Hammer"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    item.reset(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

    stacks.push_back(make_unique<ItemStack>(move(item)));

    vector<unique_ptr<ItemStack>> results;
    for(unsigned i = 0; i < stacks.size(); i++){
        results.push_back(make_unique<ItemStack>(*stacks[i]));
    }
    MergeSort s(CompareBy::Time);
    s.sort(stacks, SortOrder::Descending);

    ostringstream out;
    ostringstream result;
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Descending));
    for(unsigned i = 0; i < stacks.size(); i++){
        out << *stacks[i] << endl;
    }
    for(int i = results.size() - 1; i >= 0; i--){
        result << *results[i] << endl;
    }
    EXPECT_EQ(out.str(), result.str());

}