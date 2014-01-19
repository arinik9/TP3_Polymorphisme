#include "ObjetAgrege.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;



ObjetAgrege::~ObjetAgrege()
{
}


void ObjetAgrege::AjouterDansOA(string nomElement, ElementGeo* elementAjoute){
	if (contenu.find(nomElement) == contenu.end()){
		contenu[nomElement] = elementAjoute;
	}
}

void ObjetAgrege::EnleverDansOA(string nomElement){
	map<string, ElementGeo*>::iterator it;
	it = contenu.find(nomElement);
	contenu.erase(it);
}

void ObjetAgrege::RetirerDesObjets(){
	map<string, ElementGeo*>::iterator itOA;
	for (itOA = contenu.begin(); itOA != contenu.end(); itOA++){
		itOA->second->EnleverDansListeOA(nom);
	}
}

void ObjetAgrege::Afficher(){
	cout << "OA " << nom;
	if (contenu.size() != 0){
		map<string, ElementGeo*>::iterator it;
		for (it = contenu.begin(); it != contenu.end(); it++){
			cout << " " << it->first;
		}
	}
	cout << endl;
}

void ObjetAgrege::Deplacer(long x, long y, vector<string>& objetsDeplaces){
	map<string, ElementGeo*>::iterator itMap;
	for (itMap = contenu.begin(); itMap != contenu.end(); itMap++){
		if (find(objetsDeplaces.begin(), objetsDeplaces.end(), itMap->first) == objetsDeplaces.end()){
			itMap->second->Deplacer(x, y, objetsDeplaces);
			objetsDeplaces.push_back(itMap->first);
		}
	}
}

void ObjetAgrege::Sauvegarder(ofstream& f){
	streambuf *file_buffer = f.rdbuf();
	streambuf *old_cout_buffer = cout.rdbuf(file_buffer);
	Afficher();
	cout.rdbuf(old_cout_buffer);
}

set<string> ObjetAgrege::getObjetsGeo(){
	set<string> set;
	map<string, ElementGeo*>::iterator it;
	for(it=contenu.begin();it!=contenu.end();it++){
		string nomObjet=it->second->getNom();
		set.insert(nomObjet);
	}

	return set;
}
