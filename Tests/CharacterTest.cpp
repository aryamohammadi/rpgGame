#include "../header/character.h"
#include "../header/item.h"
#include "../header/inventory.h"
#include "gtest/gtest.h"
#include <sstream>
#include <string>

using namespace std;

// Helper function to create a weapon with default properties
Weapon* createWeapon(const std::string& name, int damage, double speedEffect = -1.0) {
    const string defaultDescription = "Default weapon description";
    return new Weapon(ItemType::WEAPON, name, defaultDescription, damage, Weapon::WeaponType::Sword, speedEffect);
}


TEST(CharacterTest, DefaultConstructor) {
    Character testCharacter("TestCharacter");
    EXPECT_EQ(testCharacter.getName(), "TestCharacter");
    EXPECT_EQ(testCharacter.getHealth(), 100);
    EXPECT_EQ(testCharacter.getDefense(), 0);
    EXPECT_EQ(testCharacter.getSpeed(), 20);
    EXPECT_TRUE(testCharacter.isAlive());
}

TEST(CharacterTest, CopyConstructor) {
    Character original("Original");
    original.pickUpItem(new Armour(ItemType::ARMOUR, "Knight's Armour", "Sturdy armour", 50));
    Character copy(original);

    ostringstream outOriginal, outCopy;
    original.showInventory(outOriginal);
    copy.showInventory(outCopy);

    EXPECT_EQ(outOriginal.str(), outCopy.str());

    original.throwAwayItem("Knight's Armour");

    ostringstream outModifiedOriginal, outUnmodifiedCopy;
    original.showInventory(outModifiedOriginal);
    copy.showInventory(outUnmodifiedCopy);

    EXPECT_NE(outModifiedOriginal.str(), outUnmodifiedCopy.str());
}


TEST(CharacterTest, AssignmentOperator) {
    Character original("Original");
    Weapon* sword = createWeapon("Sword", 75);
    original.pickUpItem(sword);
    original.equipWeapon(sword);

    Character assigned("Assigned");
    assigned = original;

    // Name should match after assignment
    EXPECT_EQ(assigned.getName(), "Original");
    EXPECT_EQ(original.getHealth(), assigned.getHealth());
    EXPECT_EQ(original.getDefense(), assigned.getDefense());

    ostringstream outOriginal, outAssigned;
    original.showInventory(outOriginal);
    assigned.showInventory(outAssigned);
    EXPECT_EQ(outOriginal.str(), outAssigned.str());

    // Ensure changes to the original do not affect the assigned character
    original.throwAwayItem("Sword");
    ostringstream outModifiedOriginal, outUnmodifiedAssigned;
    original.showInventory(outModifiedOriginal);
    assigned.showInventory(outUnmodifiedAssigned);
    EXPECT_NE(outModifiedOriginal.str(), outUnmodifiedAssigned.str());
}

TEST(CharacterTest, SerializeDeserialize) {
    Character original("Serializable");

    original.pickUpItem(new Potion(ItemType::POTION, "Health Potion", "Restores health", 50));
    original.equipArmour(new Armour(ItemType::ARMOUR, "Helmet", "Protective helmet", 10));

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


TEST(CharacterTest, EquipWeaponAndModifySpeed) {
    Character speedyCharacter("SpeedTest");

    Weapon* sword = new Weapon(ItemType::WEAPON, "Fast Sword", "Increases speed", 50, Weapon::WeaponType::Sword, 10);
    Weapon* bow = new Weapon(ItemType::WEAPON, "Long Bow", "Decreases speed", 60, Weapon::WeaponType::Bow, -5);

    speedyCharacter.pickUpItem(sword);
    speedyCharacter.pickUpItem(bow);

    speedyCharacter.equipWeapon(sword);
    EXPECT_EQ(speedyCharacter.getSpeed(), 30);

    speedyCharacter.changeWeapon(0);
    EXPECT_EQ(speedyCharacter.getSpeed(), 15);
}




TEST(CharacterTest, InventoryCapacity) {
    Character testCharacter("CapacityTest");
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(testCharacter.pickUpItem(createWeapon("Weapon" + to_string(i), 10)));
    }
    EXPECT_FALSE(testCharacter.pickUpItem(createWeapon("Extra Weapon", 10)));
}

TEST(CharacterTest, InvalidWeaponEquipping) {
    Character testCharacter("ErrorTest");
    EXPECT_THROW(testCharacter.equipWeapon(nullptr), std::logic_error);
}

TEST(CharacterTest, PotionUsage) {
    Character testCharacter("PotionTest");
    Potion* healingPotion = new Potion(ItemType::POTION, "Health Potion", "Restores health", 20);
    
    testCharacter.pickUpItem(healingPotion);
    int initialHealth = testCharacter.getHealth();
    EXPECT_TRUE(testCharacter.useItem("Health Potion"));
    EXPECT_GT(testCharacter.getHealth(), initialHealth);
}
