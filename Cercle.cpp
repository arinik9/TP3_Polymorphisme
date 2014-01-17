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

void Cercle::Deplacer(long x,long y,vector<string> objetsDeplaces){
	centre.SetX(centre.GetX()+x);
	centre.SetY(centre.GetY()+y);
}

void Cercle::Sauvegarder(ofstream& f){
	streambuf *file_buffer=f.rdbuf();
	streambuf *old_cout_buffer=cout.rdbuf(file_buffer);
	Afficher();
	cout.rdbuf(old_cout_buffer);
 }
