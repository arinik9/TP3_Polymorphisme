/*
 * ElementGeo.h
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#ifndef ELEMENTGEO_H_
#define ELEMENTGEO_H_

#include <string>
using namespace std;

class ElementGeo {
public:
	ElementGeo(string nom1):nom(nom1){}
	virtual bool Deplacer(long x,long y);
	virtual ~ElementGeo();
protected:
	string nom;
};

#endif /* ELEMENTGEO_H_ */
