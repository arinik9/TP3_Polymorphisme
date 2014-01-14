
#include "Rectangle.h"
#include <iostream>

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

void Rectangle::Afficher(){
	cout << "R " << nom << " " << point1.GetX() << " " << point1.GetY() << " " << point2.GetX() << " " << point2.GetY() << " " << endl;
}
