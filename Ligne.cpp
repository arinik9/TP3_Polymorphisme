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

void Ligne::Deplacer(long x,long y){
	point1.SetX(point1.GetX()+x);
	point1.SetY(point1.GetY()+y);
	point2.SetX(point2.GetX()+x);
	point2.SetY(point2.GetY()+y);
}

Ligne::~Ligne() {
	// TODO Auto-generated destructor stub
}
