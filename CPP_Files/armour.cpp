#include "../header/armour.h"
#include "../header/character.h"
    Armour::Armour(ItemType t = ItemType::ARMOUR, const string& name = "", Item::Grade itemGrade = Grade::COMMON, const string& descript = "", double timeElapsed = -1.0, int stat = 0):Item(t,name,itemGrade,descript,timeElapsed), armourStat(stat){}

    void Armour::useItem(Character& target){
        target.equipArmour(this);
    }

    Item* Armour::clone() const{
        return new Armour(getType(),getName(),getGrade(),getDescript(),getTime(),armourStat);
    }
