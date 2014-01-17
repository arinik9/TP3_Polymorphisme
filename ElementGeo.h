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
#include <fstream>
using namespace std;

class ElementGeo {
public:
	ElementGeo();
	ElementGeo(string nom1,string type1):nom(nom1),type(type1){}
	virtual void Deplacer(long x,long y, vector<string> objetsDeplaces);
	virtual void Afficher();
	string GetType(); //virtual
	virtual void Sauvegarder(ofstream& f);
	virtual ~ElementGeo();
protected:
	string nom;
	string type;
};

#endif /* ELEMENTGEO_H_ */
