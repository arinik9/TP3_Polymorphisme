/*
 * Ligne.cpp
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#include "Ligne.h"
#include "Point.h"
#include <iostream>

void Ligne::Afficher(){
	cout << "L " << nom << " " << point1.GetX() << " " << point1.GetY() << " " << point2.GetX() << " " << point2.GetY() << " " << endl;
}

Ligne::~Ligne() {
	// TODO Auto-generated destructor stub
}
