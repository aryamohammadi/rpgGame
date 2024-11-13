#include "item.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <sstream>
using std::ostringstream;

class MockItem: public Item{
    public:
    MockItem(ItemType t = WEAPON, const string& name = "", Grade itemGrade = COMMON, const string& descript = "", time_t time = time(nullptr)):Item(t,name,itemGrade,descript,time){}
    MOCK_METHOD(void, useItem,(),(override));
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

TEST(ItemTest, swapTest){
    MockItem A;
    MockItem B(Item::ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
    ostringstream AOut;
    ostringstream BOut;
    swap(A, B);

    string expectA = "Name: " + A.getName() + "\n";
    expectA += "Description: " + A.getDescript() + "\n";
    expectA += "Type: " + A.determineType(A.getType()) + "\n";
    expectA += "Grade: " + A.determineGrade(A.getGrade()) + "\n";

    AOut << A;

    string expectB = "Name: " + B.getName() + "\n";
    expectB += "Description: " + B.getDescript() + "\n";
    expectB += "Type: " + B.determineType(B.getType()) + "\n";
    expectB += "Grade: " + B.determineGrade(B.getGrade()) + "\n";

    BOut << B;

    EXPECT_EQ(AOut.str(), expectA);
    EXPECT_EQ(BOut.str(), expectB);
}