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

string ElementGeo::GetType(){
	return type;
}

void ElementGeo::Afficher(){}
void ElementGeo::Deplacer(long x, long y, vector<string> objetsDeplaces){}
void ElementGeo::Sauvegarder(ofstream& f){}

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

 set<string> ElementGeo::GetObjetsGeo(){
	set<string> a;
	 return a;
 }

 string ElementGeo::GetNomObjet(){
	 string a;
	 return a;
 }

 vector<long> ElementGeo::GetPoints(){

 	 vector<long> a;
 	 return a;
  }
