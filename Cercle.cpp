/*
 * Cercle.cpp
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#include "Cercle.h"
#include <iostream>



Cercle::~Cercle() {
	// TODO Auto-generated destructor stub
}

void Cercle::Afficher(){
	cout << "C " << nom << " " << centre.GetX() << " " << centre.GetY() << " " << rayon << endl;
}

void Cercle::Deplacer(long x,long y){
	centre.SetX(centre.GetX()+x);
	centre.SetY(centre.GetY()+y);
}
