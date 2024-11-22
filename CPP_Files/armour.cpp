#include "../header/armour.h"
#include "../header/itemType.h"

    Armour::Armour(ItemType t = ItemType::ARMOUR, const std::string& name = "", Grade itemGrade = COMMON, const string& descript = "", double timeElapsed = -1.0, int stat):Item(t,name,itemGrade,descript,timeElapsed), armourStat(stat){}

    void Armour::useItem(Character& target){
        target.equipArmour(this);
    }

    Item* Armour::clone() const{
        return new Armour(getType(),getName(),getGrade(),getDescript(),getTime(),armourStat);
    }