#include "../header/item.h"
#include "../header/weapon.h"
#include "../header/potion.h"
#include "../header/armour.h"
#include "../header/inventory.h"
#include "../header/sort.h"
#include "../header/insertionSort.h"
#include "../header/mergeSort.h"
#include "../header/bucketSort.h"
#include "../header/compareBy.h"
#include <sstream>
using std::ostringstream;
using testing::Return;
using namespace std;

TEST(BucketSortTest, WeaponsPriotoryTest){
    vector<ItemStack*> array;
    vector<ItemStack*> results;
    ostringstream out;
    ostringstream result;
    // Random Weapon subclass
    array.push_back(new ItemStack(new Weapon(ItemType::WEAPON, std::string("Silver Sword"), Item::Grade::RARE, std::string("A shimmering silver sword"), 12, Weapon::WeaponType::Sword)));
    array.push_back(new ItemStack(new Weapon(ItemType::WEAPON, std::string("Recurve Bow"), Item::Grade::COMMON, std::string("A lightweight bow for swift attacks"), 8, Weapon::WeaponType::Bow)));
    array.push_back(new ItemStack(new Weapon(ItemType::WEAPON, std::string("Crystal Staff"), Item::Grade::EPIC, std::string("A magical staff embedded with a crystal"), 18, Weapon::WeaponType::Staff)));

    // Random Potion subclass
    array.push_back(new ItemStack(new Potion(ItemType::POTION, std::string("Strength Potion"), Item::Grade::LEGENDARY, std::string("Boosts physical strength significantly"), 120)));
    array.push_back(new ItemStack(new Potion(ItemType::POTION, std::string("Poison Antidote"), Item::Grade::COMMON, std::string("Cures poison over time"), 50)));
    array.push_back(new ItemStack(new Potion(ItemType::POTION, std::string("Fire Resistance"), Item::Grade::RARE, std::string("Grants resistance to fire for a limited time"), 75)));

    // Random Armour subclass
    array.push_back(new ItemStack(new Armour(ItemType::ARMOUR, std::string("Plate Armor"), Item::Grade::EPIC, std::string("Heavy armor with high defense"), 25)));
    array.push_back(new ItemStack(new Armour(ItemType::ARMOUR, std::string("Buckler Shield"), Item::Grade::RARE, std::string("A small shield that provides moderate defense"), 10)));
    array.push_back(new ItemStack(new Armour(ItemType::ARMOUR, std::string("Elven Cloak"), Item::Grade::COMMON, std::string("A cloak that offers light protection and stealth"), 5)));

    BucketSort sort(CompareBy::Type, CompareItemTypeCharacteristics::Characteristics::Damage, ItemType::WEAPON);
    sort.sort(array, SortOrder::Ascending);
    
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, std::string("Recurve Bow"), Item::Grade::COMMON, std::string("A lightweight bow for swift attacks"), 8, Weapon::WeaponType::Bow)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, std::string("Silver Sword"), Item::Grade::RARE, std::string("A shimmering silver sword"), 12, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, std::string("Crystal Staff"), Item::Grade::EPIC, std::string("A magical staff embedded with a crystal"), 18, Weapon::WeaponType::Staff)));
    //check if first are weapons and sorted by damage
    for(unsigned i = 0; i < 3; i++){
        out << *array[i] << endl;
    }

    for(unsigned i = 0; i < 3; i++){
        result << results[i] << endl;
    }

    EXPECT_EQ(out.str(), result.str());

}

TEST(BucketSortTest, SortedWeapons){
    vector<ItemStack*> array;
    // Testing Weapon subclass
    array.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Iron Sword", Item::Grade::COMMON, "A basic iron sword", 10, Weapon::WeaponType::Sword)));
    array.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow", 15, Weapon::WeaponType::Bow)));
    array.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Mage Staff", Item::Grade::EPIC, "An enchanted staff for spellcasting", 20, Weapon::WeaponType::Staff)));

    // Testing Potion subclass
    array.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Potion", Item::Grade::COMMON, "Restores a small amount of health", 50)));
    array.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Elixir", Item::Grade::RARE, "Restores a moderate amount of mana", 100)));
    array.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Boost", Item::Grade::LEGENDARY, "Greatly increases stamina", 200)));

    // Testing Armour subclass
    array.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Leather Armor", Item::Grade::COMMON, "Provides minimal protection", 5)));
    array.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Chainmail", Item::Grade::RARE, "Offers moderate protection", 15)));
    array.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Armor", Item::Grade::LEGENDARY, "Unmatched protection", 50)));
}

