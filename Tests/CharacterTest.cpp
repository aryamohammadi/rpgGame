#include "../header/character.h"
#include "../header/armour.h"
#include "../header/inventory.h"
#include "../header/potion.h"
#include "../header/weapon.h"
#include <gtest/gtest.h>
#include <sstream>
#include <string>

using namespace std;

// Test the default constructor
TEST(CharacterTest, DefaultConstructor) {
    Character character("TestCharacter");
    EXPECT_EQ(character.getName(), "TestCharacter");
    EXPECT_EQ(character.getHealth(), 100);
    EXPECT_EQ(character.getDefense(), 0);
    EXPECT_EQ(character.getSpeed(), 20);
    EXPECT_TRUE(character.isAlive());
}

// Test the copy constructor
TEST(CharacterTest, CopyConstructor) {
    Character original("Original");
    original.pickUpItem(new Armour(ItemType::ARMOUR, "Knight's Armour", Item::Grade::EPIC, "Sturdy armour", 50));

    Character copy(original);
    EXPECT_EQ(copy.getName(), "Original");
    EXPECT_EQ(copy.getHealth(), 100);
    EXPECT_EQ(copy.getDefense(), 0);

    ostringstream outOriginal, outCopy;
    original.showInventory(outOriginal);
    copy.showInventory(outCopy);

    EXPECT_EQ(outOriginal.str(), outCopy.str());
}

// Test the assignment operator
TEST(CharacterTest, AssignmentOperator) {
    Character original("Original");
    original.pickUpItem(new Weapon(ItemType::WEAPON, "Sword", Item::Grade::RARE, "A sharp sword", 75, Weapon::WeaponType::Sword));

    Character assigned("Assigned");
    assigned = original;

    EXPECT_EQ(assigned.getName(), "Original");
    ostringstream outOriginal, outAssigned;
    original.showInventory(outOriginal);
    assigned.showInventory(outAssigned);

    EXPECT_EQ(outOriginal.str(), outAssigned.str());
}

// Test equip and unequip armour
TEST(CharacterTest, EquipAndUnequipArmour) {
    Character character("ArmourTest");
    Armour* armour = new Armour(ItemType::ARMOUR, "Shield", Item::Grade::LEGENDARY, "Protective shield", 40);

    character.equipArmour(armour);
    EXPECT_EQ(character.getDefense(), 40);

    character.deEquipArmour();
    EXPECT_EQ(character.getDefense(), 0);
}

// Test serialization and deserialization
TEST(CharacterTest, SerializeDeserialize) {
    Character original("Serializable");
    original.pickUpItem(new Potion(ItemType::POTION, "Health Potion", Item::Grade::RARE, "Restores health", 50));
    original.equipArmour(new Armour(ItemType::ARMOUR, "Helmet", Item::Grade::COMMON, "Protective helmet", 10));

    string serialized = original.serialize();
    Character deserialized("Empty");
    EXPECT_TRUE(deserialized.deserialize(serialized));

    ostringstream outOriginal, outDeserialized;
    original.showInventory(outOriginal);
    deserialized.showInventory(outDeserialized);

    EXPECT_EQ(outOriginal.str(), outDeserialized.str());
    EXPECT_EQ(original.getName(), deserialized.getName());
    EXPECT_EQ(original.getDefense(), deserialized.getDefense());
}

// Test inventory sorting by name
TEST(CharacterTest, SortInventoryByName) {
    Character character("Sorter");
    character.pickUpItem(new Armour(ItemType::ARMOUR, "Zebra Armour", Item::Grade::COMMON, "Alphabetically last", 5));
    character.pickUpItem(new Weapon(ItemType::WEAPON, "Alpha Sword", Item::Grade::LEGENDARY, "Alphabetically first", 100));

    character.sortAlphabetically();

    ostringstream out;
    character.showInventory(out);

    EXPECT_NE(out.str().find("Alpha Sword"), string::npos);
    EXPECT_NE(out.str().find("Zebra Armour"), string::npos);
    EXPECT_LT(out.str().find("Alpha Sword"), out.str().find("Zebra Armour"));
}

// Test weapon equip and speed modification
TEST(CharacterTest, EquipWeaponAndModifySpeed) {
    Character character("SpeedTest");
    Weapon* sword = new Weapon(ItemType::WEAPON, "Fast Sword", Item::Grade::RARE, "Increases speed", 50, Weapon::WeaponType::Sword, 10);

    character.equipWeapon(sword);
    EXPECT_EQ(character.getSpeed(), 30);

    character.changeWeapon(0); // Swap with inventory (if applicable)
    EXPECT_EQ(character.getSpeed(), 20); // Reset speed after weapon removal
}
