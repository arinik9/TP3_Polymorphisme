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


void PolyLigne::Deplacer(long x,long y, vector<string> objetsDeplaces){
	point1.SetX(point1.GetX()+x);
	point1.SetY(point1.GetY()+y);
	point2.SetX(point2.GetX()+x);
	point2.SetY(point2.GetY()+y);
	if (autresPoints.size() != 0) {
			vector<long>::iterator it;
			bool pair = false;
			for (it = autresPoints.begin() + 4; it != autresPoints.end(); it++){
				if (!pair){
					*it = *it + x;
					pair = true;
					cout << "IMPAIR" << endl;
				}
				else if (pair){
				*it = *it + y;
				pair = false;
				cout << "PAIR" << endl;
			}
			}
		}
}


void PolyLigne::Sauvegarder(ofstream& f){
	streambuf *file_buffer=f.rdbuf();
	streambuf *old_cout_buffer=cout.rdbuf(file_buffer);
	Afficher();
	cout.rdbuf(old_cout_buffer);
 }
