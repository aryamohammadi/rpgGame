#include "../header/item.h"
#include "../header/inventory.h"
#include "../header/sort.h"
#include "../header/insertionSort.h"
#include "../header/mergeSort.h"
#include "../header/bucketSort.h"
#include <sstream>
using std::ostringstream;
using testing::Return;
using namespace std;

TEST(SortTest, isSortedOneItemTest){
    MockAbstractItemSort s(CompareItem::CompareBy::Name);
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(Item::ItemType::POTION, "Emilly"))};

    EXPECT_TRUE(s.isSorted(stacks,SortOrder::Ascending, CompareItem::CompareBy::Name));
}

TEST(SortTest, TwoItemsNotSortedInAscendingOrderTest){
    MockAbstractItemSort s(CompareItem::CompareBy::Name);
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(Item::ItemType::POTION, "Emily"))};
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Dragon Slayer Sword")));

    EXPECT_FALSE(s.isSorted(stacks,SortOrder::Ascending, CompareItem::CompareBy::Name));
}

TEST(SortTest, TwoItemsNotSortedInDescendingOrderTest){
    MockAbstractItemSort s(CompareItem::CompareBy::Name);
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(Item::ItemType::POTION, "Dragon Slayer Sword"))};
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Emily")));

    EXPECT_FALSE(s.isSorted(stacks,SortOrder::Descending, CompareItem::CompareBy::Name));
}

TEST(InsertionSortTest, multipleAscendingItemTest){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(Item::ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results;
    results.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Dragon Scale Armor")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Dragon Slayer Sword")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Elven Cloak")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Emilly")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Emily's Elixir")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Excalibur")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Healing Tonic")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Knight's Shield")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Mana Brew")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Thunder Hammer")));
    InsertionSort s(CompareItem::CompareBy::Name);
    s.sort(stacks, SortOrder::Ascending, CompareItem::CompareBy::Name);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(ItemStack* stack : results){
        result << *stack << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Ascending, CompareItem::CompareBy::Name));
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(InsertionSortTest, multipleDescendingItemTest){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(Item::ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results;
    results.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Dragon Scale Armor")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Dragon Slayer Sword")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Elven Cloak")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Emilly")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Emily's Elixir")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Excalibur")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Healing Tonic")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::ARMOUR, "Knight's Shield")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::POTION, "Mana Brew")));
    results.push_back(new ItemStack(new MockItem(Item::ItemType::WEAPON, "Thunder Hammer")));
    InsertionSort s(CompareItem::CompareBy::Name);
    s.sort(stacks, SortOrder::Descending, CompareItem::CompareBy::Name);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(int i = results.size() - 1; i >= 0; i --){
        result << *results[i] << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Descending, CompareItem::CompareBy::Name));
    EXPECT_EQ(out.str(), result.str());
    
}