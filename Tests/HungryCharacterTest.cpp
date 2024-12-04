#include "../header/item.h"
#include "../header/inventory.h"
#include "../header/weapon.h"
#include "../header/potion.h"
#include "../header/armour.h"
#include "../header/character.h"
#include "../header/insertionSort.h"
#include "../header/mergeSort.h"
#include "../header/sortorder.h"
#include <gtest.h>
#include <sstream>
using std::ostringstream;
using std::endl;
using std::ostringstream;

TEST(CharacterTest, EquipArmour){
    Character C("Hi");
    ostringstream out;
    ostringstream result;

    C.equipArmour(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 10));

    out << C << endl;

    result << "Name: " << "Hi" << std::endl;
    result << "Current Health: " << 100 << std::endl;
    result << "Current Speed: " << 20 << std::endl;
    result << "Current Defense: " << 10 << std::endl;
    result << "Current Armour: " << std::endl;
    result << Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 10) << std::endl;

    EXPECT_EQ(out.str(), result.str());
}

TEST(CharacterTest, EquipAndDeequipArmour){
    Character C("Hi");
    ostringstream out;
    ostringstream result;

    C.equipArmour(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 10));
    C.deEquipArmour();
    C.equipArmour(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 11));
    out << C << endl;

    result << "Name: " << "Hi" << std::endl;
    result << "Current Health: " << 100 << std::endl;
    result << "Current Speed: " << 20 << std::endl;
    result << "Current Defense: " << 11 << std::endl;
    result << "Current Armour: " << std::endl;
    result << Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 11) << std::endl;

    EXPECT_EQ(out.str(), result.str());
}
TEST(CharacterTest, throwAwayItem){
    Character C("Hi");
    ostringstream out;
    ostringstream result;

    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 10));
    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 11));

    C.throwAwayItem(0);

    EXPECT_TRUE(C.throwAwayItem(0));
}

TEST(CharacterTest, throwAwayManyItems){
    Character C("Hi");
    ostringstream out;
    ostringstream result;

    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 10));
    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 11));
    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 12));
    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 13));
    EXPECT_TRUE(C.throwAwayItem(0));
    EXPECT_TRUE(C.throwAwayItem(0));
    EXPECT_TRUE(C.throwAwayItem(0));
    EXPECT_TRUE(C.throwAwayItem(0));
}
TEST(CharacterTest, throwTooManyItems){
    Character C("Hi");
    ostringstream out;
    ostringstream result;

    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 10));
    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 11));
    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 12));
    C.pickUpItem(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 13));
    EXPECT_TRUE(C.throwAwayItem(0));
    EXPECT_TRUE(C.throwAwayItem(0));
    EXPECT_TRUE(C.throwAwayItem(0));
    EXPECT_TRUE(C.throwAwayItem(0));
    EXPECT_FALSE(C.throwAwayItem(0));
}

TEST(CharacterSortTest, CharacterSortAlphabetically){
    ostringstream out;
    ostringstream result;
    Character player("Player");

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        player.pickUpItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Name);
    s.sort(results, SortOrder::Ascending);
    player.sortAlphabetically();

    player.showInventory(out);
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

TEST(CharacterSortTest, CharacterSortByAscendingGrade){
    ostringstream out;
    ostringstream result;
    Character player("Player");

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        player.pickUpItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Grade);
    s.sort(results, SortOrder::Ascending);
    player.sortByAscendingGrade();

    player.showInventory(out);
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

TEST(CharacterSortTest, CharacterMakeLatestFirst){
    ostringstream out;
    ostringstream result;
    Character player("Player");

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        Item* clone = stack->getItem()->clone();
        ASSERT_DOUBLE_EQ(stack->getItem()->getTime(), clone->getTime());
        delete clone;
        player.pickUpItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Time);
    s.sort(results, SortOrder::Descending);
    player.makeLatestFirst();

    player.showInventory(out);
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

TEST(CharacterSortTest, CharacterMakeOldestFirst){
    ostringstream out;
    ostringstream result;
    Character player("Player");

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        Item* clone = stack->getItem()->clone();
        ASSERT_DOUBLE_EQ(stack->getItem()->getTime(), clone->getTime());
        delete clone;
        player.pickUpItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Time);
    s.sort(results, SortOrder::Ascending);
    player.makeOldestFirst();

    player.showInventory(out);
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

TEST(CharacterSortTest, CharacterSortByDescendingGrade){
    ostringstream out;
    ostringstream result;
    Character player("Player");

    vector<ItemStack*> results;

    // Adding Weapons
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Excalibur", Item::Grade::LEGENDARY, "A legendary sword of immense power", 100, Weapon::WeaponType::Sword)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Longbow", Item::Grade::RARE, "A finely crafted longbow for precision strikes", 60, Weapon::WeaponType::Bow, -1.0)));
    results.push_back(new ItemStack(new Weapon(ItemType::WEAPON, "Warhammer", Item::Grade::EPIC, "A hammer capable of crushing armor", 80, Weapon::WeaponType::Sword)));

    // Adding Armour
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Dragon Scale Shield", Item::Grade::EPIC, "A shield made from dragon scales", 50)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Knight's Plate", Item::Grade::RARE, "Heavy armor worn by knights", 70)));
    results.push_back(new ItemStack(new Armour(ItemType::ARMOUR, "Ranger's Cloak", Item::Grade::UNCOMMON, "Light armor ideal for scouts", 30)));

    // Adding Potions
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Health Elixir", Item::Grade::RARE, "Restores a significant amount of health", 75)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Mana Draught", Item::Grade::COMMON, "Replenishes mana for spellcasters", 50)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Stamina Brew", Item::Grade::UNCOMMON, "Boosts stamina temporarily", 40)));
    results.push_back(new ItemStack(new Potion(ItemType::POTION, "Antidote", Item::Grade::COMMON, "Cures poisons and venoms", 25)));

    for(ItemStack*& stack : results){
        player.pickUpItem(stack->getItem()->clone());
    }
    InsertionSort s(CompareBy::Grade);
    s.sort(results, SortOrder::Descending);
    player.sortByDescendingGrade();

    player.showInventory(out);
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