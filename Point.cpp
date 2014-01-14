/*
 * Point.cpp
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#include "Point.h"


Point::~Point() {
	// TODO Auto-generated destructor stub
}

long Point::GetX(){
	return x;
}

long Point::GetY(){
	return y;
}

void Point::SetX(long x){
	this->x = x;
}

void Point::SetY(long y){
	this->y = y;
}
