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

<<<<<<< HEAD
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
=======
struct Parametres
{
	vector<string> objetAgr,elementObjAgr;
	vector<long> points;

};

class Figure {
private:
		//typedef map<std::vector<long>, std::vector<string> > Parametres;
		typedef map<string, Parametres> ObjetGeo;
		ObjetGeo stockage;
>>>>>>> 2e7159e0647be8fae7bdc32e5bfdb9ca7c8d830e
public:
	//std::list<ElementGeo*> elements;
	Figure();
<<<<<<< HEAD
	void Ajouter(string type, string nomObjet, vector<long> points); // on va utiliser REFERENCE????
	void Ajouter(string nomObjet, set<string> QuelobjetAgraget); // on va utiliser REFERENCE????
	//void Ajouter(std::string typeElement,std::string nom, vector<long> vec);
=======
	void Ajouter(string nomObjet, vector<long> &points); // on va utiliser REFERENCE????
	void Ajouter(string nomObjet, set<string> QuelobjetAgraget); // on va utiliser REFERENCE????
	void Ajouter(std::string typeElement,std::string nom, vector<long> vec);
>>>>>>> 2e7159e0647be8fae7bdc32e5bfdb9ca7c8d830e
	void Afficher();
	virtual ~Figure();
};




#endif /* FIGURE_H_ */
