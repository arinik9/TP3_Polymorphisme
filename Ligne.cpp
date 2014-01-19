/*
 * Ligne.cpp
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#include "Ligne.h"
#include "Point.h"
#include <iostream>

Ligne::~Ligne() {
	// TODO Auto-generated destructor stub
}

void Ligne::Afficher(){
	cout << "L " << nom << " " << point1.getX() << " " << point1.getY() << " " << point2.getX() << " " << point2.getY() << " " << endl;
}

void Ligne::Deplacer(long x, long y, vector<string>& objetsDeplaces){
	point1.setX(point1.getX() + x);
	point1.setY(point1.getY() + y);
	point2.setX(point2.getX() + x);
	point2.setY(point2.getY() + y);
}

void Ligne::Sauvegarder(ofstream& f){
	streambuf *file_buffer = f.rdbuf();
	streambuf *old_cout_buffer = cout.rdbuf(file_buffer);
	Afficher();
	cout.rdbuf(old_cout_buffer);
}
vector<long> Ligne::getPoints(){
	cout << "LIGNE" << endl;
	vector<long> a;
	vector<long>::iterator it;
	a.push_back(point1.getX());
	a.push_back(point1.getY());
	a.push_back(point2.getX());
	a.push_back(point2.getY());

	return a;
}
