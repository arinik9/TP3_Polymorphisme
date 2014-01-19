/*
 * ElementGeo.cpp
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */

#include "ElementGeo.h"
#include "ObjetAgrege.h"
#include <vector>

ElementGeo::~ElementGeo() {
	// TODO Auto-generated destructor stub
}

string ElementGeo::getType(){
	return type;
}

string ElementGeo::getNom(){
	return nom;
}

void ElementGeo::Afficher(){}
void ElementGeo::Deplacer(long x, long y, vector<string>& objetsDeplaces){}
void ElementGeo::Sauvegarder(ofstream& f){}
vector<long> ElementGeo::getPoints(){
	vector<long> a;
	return a;
}
set<string> ElementGeo::getObjetsGeo(){
	set<string> a;
	return a;
}

set<string> ElementGeo::getObjetsAgreges(){
	set<string> set;
	map<string, ObjetAgrege*>::iterator it;
	for (it = listeOA.begin(); it != listeOA.end(); it++){
		string nomObjet = it->first;
		set.insert(nomObjet);
	}
	return set;
}

 void ElementGeo::AjouterDansListeOA(string nomObjet, ObjetAgrege* objet){
	 if (listeOA.find(nomObjet) == listeOA.end()){
		 listeOA[nomObjet] = objet;
	 }
 }

 void ElementGeo::EnleverDansListeOA(string nomObjet){
	 map<string, ObjetAgrege*>::iterator it;
	 it = listeOA.find(nomObjet);
	 listeOA.erase(it);
 }

 void ElementGeo::RetirerDesOA(){
	 map<string, ObjetAgrege*>::iterator it;
	 for (it = listeOA.begin(); it != listeOA.end(); it++){
		 it->second->EnleverDansOA(nom);
	 }
 }
