#include "../header/item.h"
#include "../header/inventory.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <sstream>
using std::ostringstream;
using testing::Return;
using namespace std;

TEST(ItemTest, outputItem){
    MockItem A(Item::ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
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
    A = nullptr;
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

    bool result = (playerStorage.itemFound("Danny")) == -1;

    EXPECT_TRUE(result);

}

TEST(InventoryTest, AddOneItem){

    MockItem* item = new MockItem(Item::ItemType::ARMOR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);

    bool result = (playerStorage.itemFound("Danny")) != -1;

    EXPECT_TRUE(result);
    
}

TEST(InventoryTest, AddMultipleItems){

    MockItem* item = new MockItem(Item::ItemType::ARMOR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);
    playerStorage.addItem(new MockItem(Item::ItemType::WEAPON,"Emily",Item::Grade::COMMON,"L"));
    playerStorage.addItem(new MockItem(Item::ItemType::ARMOR,"E",Item::Grade::LEGENDARY,"A"));
    playerStorage.addItem(new MockItem(Item::ItemType::POTION,"Milly",Item::Grade::EPIC,"M"));

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
    
    MockItem* item = new MockItem(Item::ItemType::ARMOR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);

    playerStorage.removeItem("Danny");

    bool result = (playerStorage.itemFound("Danny")) == -1;

    EXPECT_TRUE(result);
      
}

TEST(InventoryTest, RemoveAndAddMultipleItems){

    MockItem* item = new MockItem(Item::ItemType::ARMOR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);
    playerStorage.addItem(new MockItem(Item::ItemType::WEAPON,"Emily",Item::Grade::COMMON,"L"));
    playerStorage.addItem(new MockItem(Item::ItemType::ARMOR,"E",Item::Grade::LEGENDARY,"A"));
    playerStorage.addItem(new MockItem(Item::ItemType::POTION,"Milly",Item::Grade::EPIC,"M"));

    std::cout << playerStorage << std::endl;

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

    MockItem* item = new MockItem(Item::ItemType::ARMOR, "Danny", Item::Grade::EPIC, "hi");

    Inventory playerStorage;

    playerStorage.addItem(item);
    playerStorage.addItem(new MockItem(Item::ItemType::WEAPON,"Emily",Item::Grade::COMMON,"L"));
    playerStorage.addItem(new MockItem(Item::ItemType::ARMOR,"E",Item::Grade::LEGENDARY,"A"));
    playerStorage.addItem(new MockItem(Item::ItemType::POTION,"Milly",Item::Grade::EPIC,"M"));

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
