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
#include "ObjetAgrege.h"
#include <stack>

using namespace std;
struct PlusieursChoseEtType{
	vector<long> vects;
	string type;
	set<string> contenuPlusieursObjetsString;
};
struct Commande
{
	string nom;
	string type;
	vector<long> points;
	set<string> listeObjetString;
	map<string, PlusieursChoseEtType> contenuEtType;
	map<string, ElementGeo*> objetsCopiees;
	vector<long> pointsDesES;
	int numeroOperation;
};

class Figure {
private:
	map<string, ElementGeo*> elements;
	stack<Commande> Undo;
	stack<Commande> Redo;
public:
	Figure();
	void Ajouter(string type, string nomObjet, vector<long> points); // on va utiliser REFERENCE????
	void AjouterOA(string nomObjet, set<string> listeObjets); //Méthode ajouter pour les OA
	void AjouterCommandeDansStack(Commande& cmd);
	bool ExecuteUndo(bool op);
	bool ExecuteRedo(bool op);
	void Afficher();
	void Supprimer(set<string> listeObjets);
	void Deplacer(string nom, long x, long y, vector<string> objetsDeplaces);
	void Sauvegarder(string nomFichier);
	set<string> GetContenuObjet(string type,string nom);
	string GetType(string nom);
	map<string, ElementGeo*> clear();
	vector<long> GetPoints(string type,string nom);
	virtual ~Figure();
};




#endif /* FIGURE_H_ */
