#include "../header/item.h"
#include "../header/inventory.h"
#include "../header/weapon.h"
#include "../header/potion.h"
#include "../header/armour.h"
#include "../header/character.h"
#include <sstream>
using std::ostringstream;
using testing::Return;
using namespace std;

TEST(CharacterTest, EquipWeapon){
    Character C("Hi");
    ostringstream out;
    ostringstream result;

    C.equipArmour(new Armour(ItemType::ARMOUR, "God", Item::Grade::LEGENDARY, "Divine Armour of the Gods", 10));

    out << C << endl;

    result << "Name: " << "Hi" << std::endl;
    result << "Current Health: " << 100 << std::endl;
    result << "Current Speed: " << 20 << std::endl;
    result << "Current Defense: " << 0 << std::endl;
    
}
