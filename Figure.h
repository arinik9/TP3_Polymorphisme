

#ifndef FIGURE_H_
#define FIGURE_H_

#include <iostream>
#include <list>
#include "string"
#include <vector>
#include "ElementGeo.h"
#include <map>
#include <set>
#include <stack>

struct Commande
{
	string nom;
	string type;
	vector<long> points;
	//vector<string> NomObjetUnique;
	int numeroOperation;
};

class Figure {
private:
	map<string, ElementGeo*> elements;
	std::stack<Commande> Undo;
	std::stack<Commande> Redo;
public:
	//std::list<ElementGeo*> elements;
	Figure();
	void Ajouter(string type, string nomObjet, vector<long> points); // on va utiliser REFERENCE????
	void Ajouter(string nomObjet, set<string> QuelobjetAgraget); // on va utiliser REFERENCE????
	void AjouterCommandeDansStack(Commande& cmd);
	bool ExecuteUndo();
	bool ExecuteRedo();
	void Afficher();
	void Deplacer(string nom,long x,long y);
	void Sauvegarder();
	virtual ~Figure();
};




#endif /* FIGURE_H_ */
