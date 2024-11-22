#include "../header/armour.h"
#include "../header/itemType.h"
#include "../header/character.h"
    Armour::Armour(ItemType t, const string& name, Item::Grade itemGrade, const string& descript, double timeElapsed = -1.0, int stat):Item(t,name,itemGrade,descript,timeElapsed), armourStat(stat){}

    void Armour::useItem(Character& target){
        target.equipArmour(this);
    }

    Item* Armour::clone() const{
        return new Armour(getType(),getName(),getGrade(),getDescript(),getTime(),armourStat);
    }
