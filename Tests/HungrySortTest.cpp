#include "../header/item.h"
#include "../header/inventory.h"
#include "../header/sort.h"
#include <sstream>
using std::ostringstream;
using testing::Return;
using namespace std;

TEST(SortTest, isSortedOneItemTest){
    MockAbstractItemSort s(CompareItem::CompareBy::Name);
    vector<ItemStack*> stacks = {new ItemStack(new MockItem(Item::ItemType::POTION, "Emilly"))};

    EXPECT_TRUE(s.isSorted(stacks,SortOrder::Ascending, CompareItem::CompareBy::Name));


}