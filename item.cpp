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