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
	cout << "PL " << nom << " " << point1.getX() << " " << point1.getY() << " " << point2.getX() << " " << point2.getY();
	if (autresPoints.size() != 0) {
		vector<long>::iterator it;
		for (it = autresPoints.begin()+4; it != autresPoints.end(); it++){
			cout << " " << *it;
		}
	}
	cout << endl;
}

void PolyLigne::Deplacer(long x, long y, vector<string> objetsDeplaces){
	point1.setX(point1.getX() + x);
	point1.setY(point1.getY() + y);
	point2.setX(point2.getX() + x);
	point2.setY(point2.getY() + y);
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
	streambuf *file_buffer = f.rdbuf();
	streambuf *old_cout_buffer = cout.rdbuf(file_buffer);
	Afficher();
	cout.rdbuf(old_cout_buffer);
}

string PolyLigne::GetNomObjet(){
	return nom;
}

string PolyLigne::GetType(){
	return type;
}

vector<long> PolyLigne::GetPoints(){
	vector<long> a;
	vector<long>::iterator it;
	a.push_back(point1.getX());
	a.push_back(point1.getY());
	a.push_back(point2.getX());
	a.push_back(point2.getY());
	for(it=autresPoints.begin()+4;it!=autresPoints.end();it++){
		a.push_back(*it);
	}

	return a;
}
