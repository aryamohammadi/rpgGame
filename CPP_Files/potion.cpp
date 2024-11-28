#include "../header/potion.h"
#include "../header/character.h"

Potion::Potion(ItemType t, const string& name, Item::Grade itemGrade, const string& descript, int amount, double timeElapsed):Item(t,name,itemGrade, descript, timeElapsed), recoveryAmount(amount){}

void Potion::useItem(Character& player){
    player.increaseHealth(recoveryAmount);
}

Item* Potion::clone() const{
    return new Potion(getType(),getName(),getGrade(),getDescript(),getTime(),recoveryAmount);
}