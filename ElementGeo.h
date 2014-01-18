/*
 * ElementGeo.h
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#ifndef ELEMENTGEO_H_
#define ELEMENTGEO_H_

#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
class ObjetAgrege;
using namespace std;

class ElementGeo {
public:
	ElementGeo(string nom1, string type1):nom(nom1), type(type1){}
	virtual string GetType();
	virtual void Deplacer(long x,long y, vector<string> objetsDeplaces);
	virtual void Afficher();
	void AjouterDansListeOA(string nomObjet, ObjetAgrege* objet);
	void EnleverDansListeOA(string nomObjet);
	void RetirerDesOA();
	virtual set<string> GetObjetsGeo();
	virtual void Sauvegarder(ofstream& f);
	virtual ~ElementGeo();
	virtual string GetNomObjet();
	virtual vector<long> GetPoints();
protected:
	string nom;
	string type;
	map<string, ObjetAgrege*> listeOA; //liste des OA contenant cet élément
};

#endif /* ELEMENTGEO_H_ */
