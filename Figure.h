/*
 * figure.h
 *
 *  Created on: 7 janv. 2014
 *      Author: narinik
 */

#ifndef FIGURE_H_
#define FIGURE_H_


#include <iostream>
#include <list>
#include "string"
#include <vector>
#include "ElementGeo.h"
#include <map>
#include <set>

//using namespace std;

//struct Parametres
//{
//	vector<string> objetAgr,elementObjAgr;
//	vector<long> points;
//
//};

class Figure {
private:
	map<string, ElementGeo*> elements;
		//typedef map<std::vector<long>, std::vector<string> > Parametres;
		//typedef map<string, Parametres> ObjetGeo;
		//ObjetGeo stockage;
public:
	//std::list<ElementGeo*> elements;
	Figure();
	void Ajouter(string type, string nomObjet, vector<long> points); // on va utiliser REFERENCE????
	void Ajouter(string nomObjet, set<string> QuelobjetAgraget); // on va utiliser REFERENCE????
	//void Ajouter(std::string typeElement,std::string nom, vector<long> vec);
	void Afficher();
	virtual ~Figure();
};




#endif /* FIGURE_H_ */
