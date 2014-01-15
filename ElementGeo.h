/*
 * ElementGeo.h
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#ifndef ELEMENTGEO_H_
#define ELEMENTGEO_H_

#include <string>
#include <vector>
using namespace std;

class ElementGeo {
public:
	ElementGeo();
	ElementGeo(string nom1):nom(nom1){}
	virtual void Deplacer(long x,long y);
	virtual void Afficher();
	virtual ~ElementGeo();
protected:
	string nom;
	vector<string> listeOA; //liste des OA contenant cet élément
};

#endif /* ELEMENTGEO_H_ */
