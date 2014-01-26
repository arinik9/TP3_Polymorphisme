
#include "Rectangle.h"
#include <iostream>

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

void Rectangle::Afficher(){
	cout << "R " << nom << " " << point1.getX() << " " << point1.getY() << " " << point2.getX() << " " << point2.getY() << " " << endl;
}

void Rectangle::Deplacer(long x1, long y1, vector<string>& objetsDeplaces){
	//deplacement du 1er point
	point1.setX(point1.getX() + x1);
	point1.setY(point1.getY() + y1);
	//deplacement du 2nd point
	point2.setX(point2.getX() + x1);
	point2.setY(point2.getY() + y1);
}

void Rectangle::Sauvegarder(ofstream& f){
	streambuf *file_buffer = f.rdbuf();
	streambuf *old_cout_buffer = cout.rdbuf(file_buffer);
	Afficher();
	cout.rdbuf(old_cout_buffer);
}
 vector<long> Rectangle::getPoints(){
	vector<long> a;
	vector<long>::iterator it;
	a.push_back(point1.getX());
	a.push_back(point1.getY());
	a.push_back(point2.getX());
	a.push_back(point2.getY());
	return a;
}
