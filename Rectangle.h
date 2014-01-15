/*
 * Rectangle.h
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "ElementGeo.h"
#include "Point.h"
#include <string>

using namespace std;

class Rectangle:public ElementGeo {

public:
	Rectangle(string nom1, long x1,long y1,long x2,long y2):ElementGeo(nom1), point1(Point(x1,y1)), point2(Point(x2,y2)){};
	virtual ~Rectangle();
	void Afficher();
	void Deplacer(long x,long y);

protected :
	Point point1;
	Point point2;
};

#endif /* RECTANGLE_H_ */
