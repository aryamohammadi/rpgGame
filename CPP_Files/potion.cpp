#include "../header/potion.h"
#include "../header/character.h"

Potion::Potion(ItemType t = ItemType::ARMOUR, const string& name = "", Item::Grade itemGrade = Grade::COMMON, const string& descript = "", int amount = 0, double timeElapsed = -1.0):Item(t,name,itemGrade, descript, timeElapsed), recoveryAmount(amount){}

void Potion::useItem(Character& player){
    player.increaseHealth(recoveryAmount);
}

Item* Potion::clone() const{
    return new Potion(getType(),getName(),getGrade(),getDescript(),getTime(),recoveryAmount);
}