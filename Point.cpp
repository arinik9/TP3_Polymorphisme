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

long Point::getX(){
	return x;
}

long Point::getY(){
	return y;
}

void Point::setX(long x){
	this->x = x;
}

void Point::setY(long y){
	this->y = y;
}
