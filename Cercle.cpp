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
	cout << "C " << nom << " " << centre.getX() << " " << centre.getY() << " " << rayon << endl;
}

void Cercle::Deplacer(long x, long y, vector<string>& objetsDeplaces){
	centre.setX(centre.getX() + x);
	centre.setY(centre.getY() + y);
}

void Cercle::Sauvegarder(ofstream& f){
	streambuf *file_buffer = f.rdbuf();
	streambuf *old_cout_buffer = cout.rdbuf(file_buffer);
	Afficher();
	cout.rdbuf(old_cout_buffer);
}
vector<long> Cercle::getPoints(){
	vector<long> a;
	vector<long>::iterator it;
	a.push_back(centre.getX());
	a.push_back(centre.getY());
	a.push_back(rayon);

	return a;
}
