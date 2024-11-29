#include "../header/item.h"
#include "../header/inventory.h"
#include "../header/sort.h"
#include "../header/insertionSort.h"
#include "../header/mergeSort.h"
#include <sstream>
using std::ostringstream;
using testing::Return;
using namespace std;

TEST(SortTest, isSortedOneItemTest){
    MockAbstractItemSort s(CompareBy::Name);
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emilly"))};

    EXPECT_TRUE(s.isSorted(stacks,SortOrder::Ascending));
}

TEST(SortTest, TwoItemsNotSortedInAscendingOrderTest){
    MockAbstractItemSort s(CompareBy::Name);
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emily"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));

    EXPECT_FALSE(s.isSorted(stacks,SortOrder::Ascending));
}

TEST(SortTest, TwoItemsNotSortedInDescendingOrderTest){
    MockAbstractItemSort s(CompareBy::Name);
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Dragon Slayer Sword"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Emily")));

    EXPECT_FALSE(s.isSorted(stacks,SortOrder::Descending));
}

TEST(InsertionSortTest, multipleAscendingItemTest){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results;
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emilly")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    InsertionSort s(CompareBy::Name);
    s.sort(stacks, SortOrder::Ascending);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(ItemStack* stack : results){
        result << *stack << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Ascending));
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(InsertionSortTest, multipleDescendingItemTest){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results;
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emilly")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    InsertionSort s(CompareBy::Name);
    s.sort(stacks, SortOrder::Descending);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(int i = results.size() - 1; i >= 0; i --){
        result << *results[i] << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Descending));
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(InsertionSortTest, ascendingTimeSort){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results = stacks;
    
    InsertionSort s(CompareBy::Time);
    s.sort(stacks, SortOrder::Ascending);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(ItemStack* stack : results){
        result << *stack << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Ascending));
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(InsertionSortTest, descendingimeSort){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results = stacks;
    
    InsertionSort s(CompareBy::Time);
    s.sort(stacks, SortOrder::Descending);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(int i = results.size() - 1; i >= 0; i--){
        result << *results[i] << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Descending));
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(MergeSortTest, multipleAscendingItemTest){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results;
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emilly")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    MergeSort s(CompareBy::Name);
    s.sort(stacks, SortOrder::Ascending);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(ItemStack* stack : results){
        result << *stack << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Ascending));
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(MergeSortTest, multipleDescendingItemTest){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results;
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emilly")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    results.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));
    results.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    results.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    MergeSort s(CompareBy::Name);
    s.sort(stacks, SortOrder::Descending);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(int i = results.size() - 1; i >= 0; i --){
        result << *results[i] << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Descending));
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(MergeSortTest, ascendingTimeSort){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results = stacks;
    
    MergeSort s(CompareBy::Time);
    s.sort(stacks, SortOrder::Ascending);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(ItemStack* stack : results){
        result << *stack << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Ascending));
    EXPECT_EQ(out.str(), result.str());
    
}

TEST(MergeSortTest, descendingimeSort){
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(ItemType::POTION, "Emilly"))};
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Emily's Elixir")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Knight's Shield")));

    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Healing Tonic")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Excalibur")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::POTION, "Mana Brew")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::WEAPON, "Thunder Hammer")));
    stacks.push_back(new ItemStack(new MockItem(ItemType::ARMOUR, "Elven Cloak")));

    vector<ItemStack*> results = stacks;
    
    MergeSort s(CompareBy::Time);
    s.sort(stacks, SortOrder::Descending);

    ostringstream out;
    ostringstream result;

    for(ItemStack* stack : stacks){
        out << *stack << endl;
    }
    for(int i = results.size() - 1; i >= 0; i--){
        result << *results[i] << endl;
    }
    EXPECT_TRUE(s.isSorted(stacks, SortOrder::Descending));
    EXPECT_EQ(out.str(), result.str());
    
}