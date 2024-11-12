#include "item.h"
#include "gtest/gtest.h"
#include <sstream>
using std::ostringstream;
TEST(ItemTest, outputItem){
    Item A(Item::ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
    ostringstream out;
    out << A;
    
    string expect = "Name: " + A.getName() + "\n";
    EXPECT_EQ(out, "");
}