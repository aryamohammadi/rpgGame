#include "item.h"
#include <stdexcept>
using std::endl;

ostream& operator<<(ostream& out, const Item& object){
    out << "Name: " << object.getName() << endl;
    out << "Description: " << object.getDescript() << endl;
    out << "Type: " << object.determineType(object.getType()) << endl;
    out << "Grade: " << object.determineGrade(object.getGrade()) << endl;
    return out;
}

string Item::determineType(int typeIndex) const{
    if(typeIndex < 0 || typeIndex >= types.size()){
        throw std::invalid_argument("type is invalid!");
    }
    return types.at(typeIndex);
}

string Item::determineGrade(int gradeIndex) const{
    if(gradeIndex < 0 || gradeIndex > grades.size()){
        throw std::invalid_argument("grade is invalid!");
    }
    return grades.at(gradeIndex);
}

Item& Item::operator=(const Item& other){
    if(this != &other){
        name = other.name;
        description = other.description;
        itemGrade = other.itemGrade;
        type = other.type;
        timeEarned = other.timeEarned;
    }
    return *this;
}

void swap(Item& item1, Item& item2){
    if(&item1 != &item2){
        Item::ItemType typeTmp = item1.type;
        string nameTmp = item1.name;
        Item::Grade g = item1.itemGrade;
        string descript = item1.description;
        time_t time = item1.timeEarned;

        item1 = item2;

        item2.type = typeTmp;
        item2.name = nameTmp;
        item2.itemGrade = g;
        item2.description = descript;
        item2.timeEarned = time;
    }
}