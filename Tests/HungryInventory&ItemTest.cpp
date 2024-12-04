#include "../header/item.h"
#include "../header/itemType.h"
#include "../header/inventory.h"
#include "../header/sort.h"
#include "../header/insertionSort.h"
#include "../header/mergeSort.h"
#include "../header/weapon.h"
#include "../header/potion.h"
#include "../header/armour.h"
#include <sstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using std::ostringstream;
using testing::Return;
using namespace std;

TEST(ItemTest, outputItem){
    MockItem A(ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
    ostringstream out;
    
    out << A;
    
    string expect = "Name: " + A.getName() + "\n";
    expect += "Description: " + A.getDescript() + "\n";
    expect += "Type: " + A.determineType(A.getType()) + "\n";
    expect += "Grade: " + A.determineGrade(A.getGrade()) + "\n";
    
    EXPECT_EQ(out.str(), expect);
}

TEST(ItemTest, emptyItem){
    MockItem A;
    
    ostringstream out;
    out << A;

    string expect = "Name: " + A.getName() + "\n";
    expect += "Description: " + A.getDescript() + "\n";
    expect += "Type: " + A.determineType(A.getType()) + "\n";
    expect += "Grade: " + A.determineGrade(A.getGrade()) + "\n";

    EXPECT_EQ(out.str(), expect);
}

TEST(ItemTest, swapTestWithOneEmpty){
    MockItem* A = new MockItem();
    MockItem* B = new MockItem(ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
    ostringstream AOut;
    ostringstream BOut;

    string expectA = "Name: " + A->getName() + "\n";
    expectA += "Description: " + A->getDescript() + "\n";
    expectA += "Type: " + A->determineType(A->getType()) + "\n";
    expectA += "Grade: " + A->determineGrade(A->getGrade()) + "\n";

    string expectB = "Name: " + B->getName() + "\n";
    expectB += "Description: " + B->getDescript() + "\n";
    expectB += "Type: " + B->determineType(B->getType()) + "\n";
    expectB += "Grade: " + B->determineGrade(B->getGrade()) + "\n";

    swap(A, B);
    AOut << *A;
    BOut << *B;

    EXPECT_EQ(AOut.str(), expectB);
    EXPECT_EQ(BOut.str(), expectA);

    delete A;
    A = nullptr;
    delete B;
}

TEST(ItemTest, ItemSwap){
    MockItem* A = new MockItem(ItemType::POTION, "Danny",Item::Grade::LEGENDARY,"OP");
    MockItem* B = new MockItem(ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
    ostringstream AOut;
    ostringstream BOut;
    swap(A, B);

    string expectA = "Name: " + A->getName() + "\n";
    expectA += "Description: " + A->getDescript() + "\n";
    expectA += "Type: " + A->determineType(A->getType()) + "\n";
    expectA += "Grade: " + A->determineGrade(A->getGrade()) + "\n";

    AOut << *A;

    string expectB = "Name: " + B->getName() + "\n";
    expectB += "Description: " + B->getDescript() + "\n";
    expectB += "Type: " + B->determineType(B->getType()) + "\n";
    expectB += "Grade: " + B->determineGrade(B->getGrade()) + "\n";

    BOut << *B;

    EXPECT_EQ(AOut.str(), expectA);
    EXPECT_EQ(BOut.str(), expectB);

    delete A;
    delete B;

}

TEST(InventoryTest, emptyInventory){
    Inventory playerStorage;

    bool result = (playerStorage.itemFound("Danny")) == -1;

    EXPECT_TRUE(result);

}

TEST(InventoryTest, AddOneItem){

    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);

    bool result = (playerStorage.itemFound("Danny")) != -1;

    EXPECT_TRUE(result);
    
}

TEST(InventoryTest, AddMultipleItems){

    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);
    playerStorage.addItem(new MockItem(ItemType::WEAPON,"Emily",Item::Grade::COMMON,"L"));
    playerStorage.addItem(new MockItem(ItemType::ARMOUR,"E",Item::Grade::LEGENDARY,"A"));
    playerStorage.addItem(new MockItem(ItemType::POTION,"Milly",Item::Grade::EPIC,"M"));

    bool result = (playerStorage.itemFound("Danny")) != -1;

    EXPECT_TRUE(result);

    result = (playerStorage.itemFound("E")) != -1;

    EXPECT_TRUE(result);

    result = (playerStorage.itemFound("Milly")) != -1;

    EXPECT_TRUE(result);

    result = (playerStorage.itemFound("Emily")) != -1;

    EXPECT_TRUE(result);
    
}

TEST(InventoryTest, removeOneItem){
    
    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);

    playerStorage.removeItem("Danny");

    bool result = (playerStorage.itemFound("Danny")) == -1;

    EXPECT_TRUE(result);
      
}

TEST(InventoryTest, RemoveAndAddMultipleItems){

    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);
    playerStorage.addItem(new MockItem(ItemType::WEAPON,"Emily",Item::Grade::COMMON,"L"));
    playerStorage.addItem(new MockItem(ItemType::ARMOUR,"E",Item::Grade::LEGENDARY,"A"));
    playerStorage.addItem(new MockItem(ItemType::POTION,"Milly",Item::Grade::EPIC,"M"));

    bool result = (playerStorage.itemFound("Danny")) != -1;

    EXPECT_TRUE(result);

    result = (playerStorage.itemFound("E")) != -1;

    EXPECT_TRUE(result);

    result = (playerStorage.itemFound("Milly")) != -1;

    EXPECT_TRUE(result);

    result = (playerStorage.itemFound("Emily")) != -1;

    EXPECT_TRUE(result);

    //Remove Items
    playerStorage.removeItem("Emily");

    result = (playerStorage.itemFound("Emily")) == -1;

    EXPECT_TRUE(result);

    playerStorage.removeItem("E");

    result = (playerStorage.itemFound("E")) == -1;

    EXPECT_TRUE(result);

    playerStorage.removeItem("Danny");

    result = (playerStorage.itemFound("Danny")) == -1;

    EXPECT_TRUE(result);

    playerStorage.removeItem("Milly");

    result = (playerStorage.itemFound("Danny")) == -1;

    EXPECT_TRUE(result);

    EXPECT_TRUE(playerStorage.isEmpty());

}

TEST(InventoryTest, RemoveAndAddMultipleItemsAndUnderFlow){

    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);
    playerStorage.addItem(new MockItem(ItemType::WEAPON,"Emily",Item::Grade::COMMON,"L"));
    playerStorage.addItem(new MockItem(ItemType::ARMOUR,"E",Item::Grade::LEGENDARY,"A"));
    playerStorage.addItem(new MockItem(ItemType::POTION,"Milly",Item::Grade::EPIC,"M"));

    bool result = (playerStorage.itemFound("Danny")) != -1;

    EXPECT_TRUE(result);

    result = (playerStorage.itemFound("E")) != -1;

    EXPECT_TRUE(result);

    result = (playerStorage.itemFound("Milly")) != -1;

    EXPECT_TRUE(result);

    result = (playerStorage.itemFound("Emily")) != -1;

    EXPECT_TRUE(result);
    //Remove Items
    playerStorage.removeItem("Emily");

    result = (playerStorage.itemFound("Emily")) == -1;

    EXPECT_TRUE(result);

    playerStorage.removeItem("E");

    result = (playerStorage.itemFound("E")) == -1;
    
    EXPECT_TRUE(result);

    playerStorage.removeItem("Danny");

    result = (playerStorage.itemFound("Danny")) == -1;
    
    EXPECT_TRUE(result);

    playerStorage.removeItem("Milly");

    result = (playerStorage.itemFound("Milly")) == -1;
    
    EXPECT_TRUE(result);
    
    EXPECT_TRUE(playerStorage.isEmpty());
    
    EXPECT_ANY_THROW(playerStorage.removeItem(""));

    
}

TEST(InventorySortingTest, sortAlphabetically){
    ostringstream out;
    ostringstream result;
    Inventory playerStorage;

    playerStorage.addItem(new MockItem(ItemType::POTION, "Emilly"));
    playerStorage.addItem(new MockItem(ItemType::POTION, "Emily's Elixir"));
    playerStorage.addItem(new MockItem(ItemType::WEAPON, "Dragon Slayer Sword"));
    playerStorage.addItem(new MockItem(ItemType::ARMOUR, "Knight's Shield"));

    playerStorage.addItem(new MockItem(ItemType::POTION, "Healing Tonic"));
    playerStorage.addItem(new MockItem(ItemType::WEAPON, "Excalibur"));
    playerStorage.addItem(new MockItem(ItemType::ARMOUR, "Dragon Scale Armor"));
    playerStorage.addItem(new MockItem(ItemType::POTION, "Mana Brew"));
    playerStorage.addItem(new MockItem(ItemType::WEAPON, "Thunder Hammer"));
    playerStorage.addItem(new MockItem(ItemType::ARMOUR, "Elven Cloak"));

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

    playerStorage.sortAlphabetically();

    out << playerStorage;

    for(unsigned i = 0; i < results.size(); i++){
        result << "Item " << i << ':' << std::endl;
        result << *results[i] << endl;
        delete results[i];
        results[i] = nullptr;
    }
    

    EXPECT_EQ(out.str(), result.str());
}

TEST(InventorySortingTestWithActualItems, makeLatestFirst){
    ostringstream out;
    ostringstream result;
    Inventory playerStorage(20);

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        Item* clone = stack->getItem()->clone();
        ASSERT_DOUBLE_EQ(stack->getItem()->getTime(), clone->getTime());
        delete clone;
        playerStorage.addItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Time);
    s.sort(results, SortOrder::Descending);
    playerStorage.makeLatestFirst();

    out << playerStorage;
    int index = 0;
    for(int i = 0; i < results.size(); i++){
        result << "Item " << index << ':' << std::endl;
        result << *results[i] << endl;
        index ++;
    }

    EXPECT_EQ(out.str(), result.str());
    for(ItemStack*& stack : results) {
        delete stack;
    }
    results.clear();
}

TEST(InventorySortingTestWithActualItems, makeOldestFirst){
    ostringstream out;
    ostringstream result;
    Inventory playerStorage(20);

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        Item* clone = stack->getItem()->clone();
        ASSERT_DOUBLE_EQ(stack->getItem()->getTime(), clone->getTime());
        delete clone;
        playerStorage.addItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Time);
    s.sort(results, SortOrder::Ascending);
    playerStorage.makeOldestFirst();

    out << playerStorage;
    int index = 0;
    for(int i = 0; i < results.size(); i++){
        result << "Item " << index << ':' << std::endl;
        result << *results[i] << endl;
        index ++;
    }

    EXPECT_EQ(out.str(), result.str());
    for(ItemStack*& stack : results) {
        delete stack;
    }
    results.clear();
}

TEST(InventorySortingTestWithActualItems, sortByDescendingGrade){
    ostringstream out;
    ostringstream result;
    Inventory playerStorage(20);

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        playerStorage.addItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Grade);
    s.sort(results, SortOrder::Descending);
    playerStorage.sortByDescendingGrade();

    out << playerStorage;
    int index = 0;
    for(int i = 0; i < results.size(); i++){
        result << "Item " << index << ':' << std::endl;
        result << *results[i] << endl;
        index ++;
    }

    EXPECT_EQ(out.str(), result.str());
    for(ItemStack*& stack : results) {
        delete stack;
    }
    results.clear();
}

TEST(InventorySortingTestWithActualItems, sortByAscendingGrade){
    ostringstream out;
    ostringstream result;
    Inventory playerStorage(20);

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        playerStorage.addItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Grade);
    s.sort(results, SortOrder::Ascending);
    playerStorage.sortByAscendingGrade();

    out << playerStorage;
    int index = 0;
    for(int i = 0; i < results.size(); i++){
        result << "Item " << index << ':' << std::endl;
        result << *results[i] << endl;
        index ++;
    }

    EXPECT_EQ(out.str(), result.str());
    for(ItemStack*& stack : results) {
        delete stack;
    }
    results.clear();
}

TEST(InventorySortingTestWithActualItems, sortAlphabetically){
    ostringstream out;
    ostringstream result;
    Inventory playerStorage(20);

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        playerStorage.addItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Name);
    s.sort(results, SortOrder::Ascending);
    playerStorage.sortAlphabetically();

    out << playerStorage;
    int index = 0;
    for(int i = 0; i < results.size(); i++){
        result << "Item " << index << ':' << std::endl;
        result << *results[i] << endl;
        index ++;
    }

    EXPECT_EQ(out.str(), result.str());
    for(ItemStack*& stack : results) {
        delete stack;
    }
    results.clear();
}