/*
 * Ligne.h
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#ifndef LIGNE_H_
#define LIGNE_H_

#include "ElementGeo.h"
#include "Point.h"

class Ligne:public ElementGeo {
public:

	Ligne(string nom1,long x1,long y1,long x2,long y2):ElementGeo(nom1), point1(Point(x1,y1)), point2(Point(x2,y2)){};
	void Afficher();
	void Deplacer(long x,long y);
	void Sauvegarder(ofstream& f);
	virtual ~Ligne();
protected:
	Point point1;
	Point point2;
};

#endif /* LIGNE_H_ */
