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
#include <vector>
#include <map>
#include <set>
#include <stack>
#include "ObjetAgrege.h"
#include "Cercle.h"
#include "Rectangle.h"
#include "Ligne.h"
#include "PolyLigne.h"
class ElementGeo;
class Ligne;
using namespace std;

struct PlusieursChoseEtType{
	vector<long> vects;
	string type;
	set<string> contenuPlusieursObjetsString;
	set<string> listeDesOA;
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
	bool Ajouter(string type, string nomObjet, vector<long> points, bool load); // on va utiliser REFERENCE????
	bool AjouterOA(string nomObjet, set<string> listeObjets, bool load); //Méthode ajouter pour les OA
	void AjouterCommandeDansStack(Commande& cmd);
	bool ExecuteUndo(bool op);
	bool ExecuteRedo(bool op);
	void ViderStacks();
	void Afficher();
	bool Supprimer(set<string> listeObjets);
	bool Deplacer(string nom, long x, long y, vector<string>& objetsDeplaces);
	void Sauvegarder(string nomFichier);
	map<string, ElementGeo*> clear();
	set<string> getContenuObjet(string nom);
	set<string> getListeOA(string nom);
	string getType(string nom);
	vector<long> getPoints(string type, string nom);
	virtual ~Figure();
};




#endif /* FIGURE_H_ */
