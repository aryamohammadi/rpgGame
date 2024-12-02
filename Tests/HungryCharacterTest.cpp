#include "../header/item.h"
#include "../header/inventory.h"
#include "../header/weapon.h"
#include "../header/potion.h"
#include "../header/armour.h"
#include "../header/character.h"
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