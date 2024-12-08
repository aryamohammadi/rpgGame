#include "../header/item.h"
#include "../header/itemType.h"
#include "../header/inventory.h"
#include "../header/sort.h"
#include "../header/insertionSort.h"
#include "../header/mergeSort.h"
#include <sstream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using std::ostringstream;
using testing::Return;
using namespace std;
class MockItem: public Item{
    public:
        MockItem(ItemType t = ItemType::WEAPON, const string& name = "", const string& descript = "", double timeElapsed = -1.0):Item(t,name,descript, timeElapsed){}
        MOCK_METHOD(void, useItem,(Character&),(override));
        MOCK_METHOD(std::string, serialize, (), (const, override));
        MOCK_METHOD(bool,deserialize,(const string&), (override));
        Item* clone() const override{
            return new MockItem(type, name, description, timeEarned);
        }
        friend void swap(MockItem*& item1, MockItem*& item2){
            MockItem* item1Placeholder = item1;

            item1 = item2;

            item2 = item1Placeholder;
    }
};

TEST(ItemTest, outputItem){
    MockItem A(ItemType::WEAPON, "Emily","hi");
    ostringstream out;
    
    out << A;
    
    string expect = "Name: " + A.getName() + "\n";
    expect += "Description: " + A.getDescript() + "\n";
    expect += "Type: " + A.determineType(A.getType()) + "\n";
    
    EXPECT_EQ(out.str(), expect);
}

TEST(ItemTest, emptyItem){
    MockItem A;
    
    ostringstream out;
    out << A;

    string expect = "Name: " + A.getName() + "\n";
    expect += "Description: " + A.getDescript() + "\n";
    expect += "Type: " + A.determineType(A.getType()) + "\n";

    EXPECT_EQ(out.str(), expect);
}

TEST(ItemTest, swapTestWithOneEmpty){
    MockItem* A = new MockItem();
    MockItem* B = new MockItem(ItemType::WEAPON, "Emily","hi");
    ostringstream AOut;
    ostringstream BOut;

    string expectA = "Name: " + A->getName() + "\n";
    expectA += "Description: " + A->getDescript() + "\n";
    expectA += "Type: " + A->determineType(A->getType()) + "\n";

    string expectB = "Name: " + B->getName() + "\n";
    expectB += "Description: " + B->getDescript() + "\n";
    expectB += "Type: " + B->determineType(B->getType()) + "\n";

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
    MockItem* A = new MockItem(ItemType::POTION, "Danny","OP");
    MockItem* B = new MockItem(ItemType::WEAPON, "Emily","hi");
    ostringstream AOut;
    ostringstream BOut;
    swap(A, B);

    string expectA = "Name: " + A->getName() + "\n";
    expectA += "Description: " + A->getDescript() + "\n";
    expectA += "Type: " + A->determineType(A->getType()) + "\n";

    AOut << *A;

    string expectB = "Name: " + B->getName() + "\n";
    expectB += "Description: " + B->getDescript() + "\n";
    expectB += "Type: " + B->determineType(B->getType()) + "\n";

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

    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny",  "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);

    bool result = (playerStorage.itemFound("Danny")) != -1;

    EXPECT_TRUE(result);
    
}

TEST(InventoryTest, AddMultipleItems){

    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny",  "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);
    playerStorage.addItem(new MockItem(ItemType::WEAPON,"Emily","L"));
    playerStorage.addItem(new MockItem(ItemType::ARMOUR,"E","A"));
    playerStorage.addItem(new MockItem(ItemType::POTION,"Milly","M"));

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
    
    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny",  "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);

    playerStorage.removeItem("Danny");

    bool result = (playerStorage.itemFound("Danny")) == -1;

    EXPECT_TRUE(result);
      
}

TEST(InventoryTest, RemoveAndAddMultipleItems){

    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny",  "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);
    playerStorage.addItem(new MockItem(ItemType::WEAPON,"Emily","L"));
    playerStorage.addItem(new MockItem(ItemType::ARMOUR,"E","A"));
    playerStorage.addItem(new MockItem(ItemType::POTION,"Milly","M"));

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

    MockItem* item = new MockItem(ItemType::ARMOUR, "Danny",  "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);
    playerStorage.addItem(new MockItem(ItemType::WEAPON,"Emily","L"));
    playerStorage.addItem(new MockItem(ItemType::ARMOUR,"E","A"));
    playerStorage.addItem(new MockItem(ItemType::POTION,"Milly","M"));

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

    vector<unique_ptr<ItemStack>> results;
    unique_ptr<Item> item;

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

    playerStorage.sortAlphabetically();

    out << playerStorage;

    for(unsigned i = 0; i < results.size(); i++){
        result << "Item " << i << ':' << std::endl;
        result << *results[i] << endl;
    }
    

    EXPECT_EQ(out.str(), result.str());
}

TEST(InventorySortingTestWithActualItems, makeLatestFirst){
    ostringstream out;
    ostringstream result;
    Inventory playerStorage(20);

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur",  "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow",  "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer",  "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield",  "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate",  "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak",  "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir",  "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught",  "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew",  "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote",  "Cures poisons and venoms", 25)));

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
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur",  "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow",  "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer",  "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield",  "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate",  "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak",  "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir",  "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught",  "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew",  "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote",  "Cures poisons and venoms", 25)));

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

TEST(InventorySortingTestWithActualItems, sortAlphabetically){
    ostringstream out;
    ostringstream result;
    Inventory playerStorage(20);

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur",  "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow",  "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer",  "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield",  "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate",  "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak",  "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir",  "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught",  "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew",  "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote",  "Cures poisons and venoms", 25)));

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