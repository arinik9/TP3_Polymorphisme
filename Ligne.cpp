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

void Ligne::Deplacer(long x,long y,vector<string> objetsDeplaces){
	point1.SetX(point1.GetX()+x);
	point1.SetY(point1.GetY()+y);
	point2.SetX(point2.GetX()+x);
	point2.SetY(point2.GetY()+y);
}

void Ligne::Sauvegarder(ofstream& f){
	streambuf *file_buffer=f.rdbuf();
	streambuf *old_cout_buffer=cout.rdbuf(file_buffer);
	Afficher();
	cout.rdbuf(old_cout_buffer);
 }

vector<long> Ligne::GetPoints(){
	cout << "LIGNE" << endl;
	vector<long> a;
	vector<long>::iterator it;
	a.push_back(point1.GetX());
	a.push_back(point1.GetY());
	a.push_back(point2.GetX());
	a.push_back(point2.GetY());

	return a;
}

Ligne::~Ligne() {
	// TODO Auto-generated destructor stub
}
