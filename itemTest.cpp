#include "item.h"
#include "gtest/gtest.h"
#include <sstream>
using std::ostringstream;

TEST(ItemTest, outputItem){
    Item A(Item::ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
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
    Item A;
    
    ostringstream out;
    out << A;

    string expect = "Name: " + A.getName() + "\n";
    expect += "Description: " + A.getDescript() + "\n";
    expect += "Type: " + A.determineType(A.getType()) + "\n";
    expect += "Grade: " + A.determineGrade(A.getGrade()) + "\n";

    EXPECT_EQ(out.str(), expect);
}

TEST(ItemTest, swapTest){
    Item A;
    Item B(Item::ItemType::WEAPON, "Emily",Item::Grade::COMMON,"hi");
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