#include "../header/armour.h"
#include "../header/character.h"
    Armour::Armour(ItemType t, const string& name, Item::Grade itemGrade, const string& descript, int stat, double timeElapsed):Item(t,name,itemGrade,descript,timeElapsed), armourStat(stat){}

    void Armour::useItem(Character& target){
        target.equipArmour(this);
    }

    Item* Armour::clone() const{
        return new Armour(getType(),getName(),getGrade(),getDescript(),getTime(),armourStat);
    }

std::ostream& operator<<(std::ostream& out, const Armour& currentArmour){
    out << static_cast<const Item&>(currentArmour);
    out << "Armour Stat: " << currentArmour.getArmourStat() << std::endl;
    return out;
}