#include "item.h"
#include "inventory.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <sstream>
using std::ostringstream;
using testing::Return;

class MockItem: public Item{
    public:
        MockItem(ItemType t = WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", time_t time = time(nullptr)):Item(t,name,itemGrade,descript, time){}
        MOCK_METHOD(void, useItem,(),(override));
};
void swap(MockItem*& item1, MockItem*& item2){
    MockItem* item1Placeholder = item1;

    item1 = item2;

    item2 = item1Placeholder;
}
class MockInventory: public Inventory{
    public:
        MockInventory():Inventory(){}
        MOCK_METHOD(void, addItem, (MockItem* item), ());
        MOCK_METHOD(bool, itemFound, (const std::string& name), ());
        MOCK_METHOD(bool, removeItem, (const std::string& name), ());
};

TEST(ItemTest, outputItem){
    MockItem A(Item::ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
    ostringstream out;
    out.clear();
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
    MockItem* B = new MockItem(Item::ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
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
    delete B;
}

TEST(ItemTest, ItemSwap){
    MockItem* A = new MockItem(Item::ItemType::POTION, "Danny",Item::Grade::LEGENDARY,"OP");
    MockItem* B = new MockItem(Item::ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
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

    bool result = playerStorage.itemFound("Danny");

    EXPECT_FALSE(result);

}

TEST(InventoryTest, OneItem){

    MockItem* item = new MockItem(Item::ItemType::ARMOR, "Danny", Item::Grade::EPIC, "hi");

    MockInventory playerStorage;

    ON_CALL(playerStorage, addItem(item))
    .WillByDefault(testing::Invoke([](MockItem* item){
        // Simulate behavior of addItem
        std::cout << "Item added: " << item->getName() << std::endl;
    }));

    playerStorage.addItem(item);

    EXPECT_CALL(playerStorage, itemFound("Danny")).WillOnce(testing::Return(true));
    bool result = playerStorage.itemFound("Danny");

    EXPECT_TRUE(result);
    

    delete item;
}

TEST(InventoryTest, removeOneItem){
    
    MockItem* item = new MockItem(Item::ItemType::ARMOR, "Danny", Item::Grade::EPIC, "hi");

    MockInventory playerStorage;

    ON_CALL(playerStorage, addItem(item))
    .WillByDefault(testing::Invoke([](MockItem* item){
        // Simulate behavior of addItem
        std::cout << "Item added: " << item->getName() << std::endl;
    }));

    playerStorage.addItem(item);

    playerStorage.removeItem(item->getName());

    bool result = playerStorage.itemFound("Danny");

    EXPECT_FALSE(result);
    
    delete item;   
}