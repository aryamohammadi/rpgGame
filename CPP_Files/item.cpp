#include "../header/item.h"
#include "../header/character.h"
#include <stdexcept>
using std::endl;

ostream& operator<<(ostream& out, const Item& object){
    out << "Name: " << object.getName() << endl;
    out << "Description: " << object.getDescript() << endl;
    out << "Type: " << object.determineType(object.getType()) << endl;
    out << "Grade: " << object.determineGrade(object.getGrade()) << endl;
    return out;
}

string Item::determineType(ItemType type) const{
    switch(type){
        case ItemType::WEAPON:
            return types.front();
        case ItemType::POTION:
            return types.back();
        case ItemType::ARMOUR:
            return types.at(1);
        default:
            throw std::logic_error("Item has invalid type!");
    }
}

string Item::determineGrade(int gradeIndex) const{
    if(gradeIndex < 0 || gradeIndex >= grades.size()){
        throw std::invalid_argument("grade is invalid!");
    }
    return grades.at(gradeIndex);
}

void swap(Item* &item1, Item* &item2){
    Item* item1Placeholder = item1;

    item1 = item2;
    
    item2 = item1Placeholder;
}

std::string Item::serialize() const {
    std::ostringstream oss;
    oss << name << "\n" << static_cast<int>(type) << "\n" << description << "\n"
        << timeEarned << "\n" << static_cast<int>(itemGrade);
    return oss.str();
}

bool Item::deserialize(const string& data) {
    std::istringstream iss(data);
    int typeInt, gradeInt;

    if (!(std::getline(iss, name) && iss >> typeInt && std::getline(iss, description)
          && iss >> timeEarned && iss >> gradeInt)) {
        return false;
    }

    type = static_cast<ItemType>(typeInt);
    itemGrade = static_cast<Grade>(gradeInt);
    return true;
}
