#include "../header/character.h"
#include "../header/armour.h"
void Character::equipArmour(Armour* armour){
    if(this->armour == nullptr){
        this->armour = armour;
    }
    else{
        if(storage.itemFound(*armour) != -1){
            storage.removeItem(*armour);
        }
        this->armour = armour;
    }
    defense += armour->getArmourStat();
}

void Character::deEquipArmour() {
    if (armour != nullptr) {
        defense -= armour->getArmourStat();
        storage.addItem(armour);           
        armour = nullptr;                  
    }
}