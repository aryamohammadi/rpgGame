#include "item.h"
#include "gtest/gtest.h"

TEST(ItemTest, emptyName){
    Item A(Item::ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
    
    string result = A.getName();
    
    EXPECT_EQ(result, "Emily");
}