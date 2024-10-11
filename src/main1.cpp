#include <iostream>
#include "../header/rectangle.hpp"

using namespace std;

int main()
{
    Rectangle rect;
    rect.set_width(3); 
    rect.set_height(4);
    cout << "Rectangle area: " << rect.area() << endl;
    return 0;
}