/*
 * PolyLigne.cpp
 *
 *  Created on: 07 Oca 2014
 *      Author: nejat
 */

#include "PolyLigne.h"
#include <iostream>

//PolyLigne::PolyLigne(string nom1, vector<long> points){
//	Ligne(nom1, points[0], points[1], points[2], points[3]);
//	autresPoints = points;
//	autresPoints.erase(autresPoints.begin(), autresPoints.begin() + 4);
//
//}


PolyLigne::~PolyLigne() {
	// TODO Auto-generated destructor stub
}

void PolyLigne::Afficher(){
	cout << "PL " << nom << " " << point1.GetX() << " " << point1.GetY() << " " << point2.GetX() << " " << point2.GetY();
	if (autresPoints.size() != 0) {
		vector<long>::iterator it;
		for (it = autresPoints.begin()+4; it != autresPoints.end(); it++){
			cout << " " << *it;
		}
	}
	cout << endl;
}
