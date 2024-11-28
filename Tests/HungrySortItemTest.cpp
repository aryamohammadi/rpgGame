#include "../header/item.h"
#include "../header/inventory.h"
#include "../header/sort.h"
#include "../header/insertionSort.h"
#include "../header/mergeSort.h"
#include "../header/bucketSort.h"
#include <sstream>
using std::ostringstream;
using testing::Return;
using namespace std;

TEST(BucketSortTest, WeaponsPriotoryTest){
    vector<ItemStack*> array;
    array.push_back(new ItemStack(new Weapon(ItemType::WEAPON, " ", Item::Grade::COMMON, )))

}