/*
 * Cercle.h
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#ifndef CERCLE_H_
#define CERCLE_H_

#include "ElementGeo.h"
#include "Point.h"

class Cercle: public ElementGeo {
public:
	Cercle(string nom1,long x1,long y1,long rayon1):ElementGeo(nom1), centre(Point(x1,y1)),rayon(rayon1){}
	virtual ~Cercle();
	void Afficher();
protected:
	Point centre;

	long rayon;
};

#endif /* CERCLE_H_ */
