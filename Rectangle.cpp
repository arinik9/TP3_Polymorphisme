
#include "Rectangle.h"
#include <iostream>

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

void Rectangle::Afficher(){
	cout << "R " << nom << " " << point1.GetX() << " " << point1.GetY() << " " << point2.GetX() << " " << point2.GetY() << " " << endl;
}

void Rectangle::Deplacer(long x,long y){
	point1.SetX(point1.GetX()+x);
	point1.SetY(point1.GetY()+y);
	point2.SetX(point2.GetX()+x);
	point2.SetY(point2.GetY()+y);
}

void Rectangle::Sauvegarder(ofstream& f){
	streambuf *file_buffer=f.rdbuf();
	streambuf *old_cout_buffer=cout.rdbuf(file_buffer);
	Afficher();
	cout.rdbuf(old_cout_buffer);
 }
