#include "../header/item.h"
#include <stdexcept>
using std::endl;

ostream& operator<<(ostream& out, const Item& object){
    out << "Name: " << object.getName() << endl;
    out << "Description: " << object.getDescript() << endl;
    out << "Type: " << object.getType() << endl;
    out << "Grade: " << object.getGrade() << endl;
    return out;
}


void swap(Item* &item1, Item* &item2){
    Item* item1Placeholder = item1;

    item1 = item2;
    
    item2 = item1Placeholder;
}