
#include "Figure.h"
#include "Cercle.h"
#include "Rectangle.h"
#include "Ligne.h"
#include "PolyLigne.h"
#include <list>
#include <set>
#include <vector>
#include "string"
#include "ElementGeo.h"

using namespace std;

//http://kapo-cpp.blogspot.fr/2007/10/multilevel-undo-with-command-pattern.html


void Figure::Ajouter(string type, string nomObjet, vector<long> points){
	map<string,ElementGeo*>::iterator it;
	vector<long>::iterator itVec;

	if (elements.find(nomObjet) == elements.end()) { // C'EST PAS LA PEINE PEUT-ETRE!!!
		if (type == "C"){
			ElementGeo* cercle = new Cercle(nomObjet, points[0], points[1], points[2]);
			elements[nomObjet] = cercle;
		}
		else if (type == "R"){
			ElementGeo* rectangle = new Rectangle(nomObjet, points[0], points[1], points[2], points[3]);
			elements[nomObjet] = rectangle;
		}
		else if (type == "L"){
			ElementGeo* ligne = new Ligne(nomObjet, points[0], points[1], points[2], points[3]);
			elements[nomObjet] = ligne;
		}
		else if (type == "PL"){
			ElementGeo* polyligne = new PolyLigne(nomObjet, points);
			elements[nomObjet] = polyligne;
		}
	}
}

void Figure::AjouterCommandeDansStack(Commande& cmd){
	if(cmd.numeroOperation != 5 || cmd.numeroOperation !=6) // pas de Commande Undo et Redo
		Undo.push(cmd);
}

bool Figure::ExecuteUndo(){
	Commande cmd;
	bool res=true;
	if (Undo.empty())
		res=false;

	if (res){
		cmd=Undo.top();
		Redo.push(cmd); //Undo.top()  -->>  supprimer le dernier element qui est inseré
		Undo.pop();

		if(cmd.numeroOperation==1){
			//ajouter
		}
		if(cmd.numeroOperation==2){
			//supprimer
		}
		if(cmd.numeroOperation==3){
			//deplacer
		}
		if(cmd.numeroOperation==4){
			//clear
		}
	}
	return res;
}

bool Figure::ExecuteRedo(){
	Commande cmd;
	bool res=true;
	if (Undo.empty())
		res=false;

	if(res){
		cmd=Redo.top();
		Undo.push(cmd); //Undo.top()  -->>  supprimer le dernier element qui est inseré
		Redo.pop();

		if(cmd.numeroOperation==1){
			//ajouter
		}
		if(cmd.numeroOperation==2){
			//supprimer
		}
		if(cmd.numeroOperation==3){
			//deplacer
		}
		if(cmd.numeroOperation==4){
			//clear
		}
	}
	return res;
}
//void Figure::Ajouter(string nomObjet, set<string> QuelobjetAgraget){
//	set<string>::iterator iter;
//	map<string,Parametres>::iterator it;
//	vector<string>::iterator itVec;
//
//	for(iter=QuelobjetAgraget.begin();iter!=QuelobjetAgraget.end();iter++){
//		stockage[nomObjet].elementObjAgr.push_back(*iter);
//	}
//
//	for(iter=QuelobjetAgraget.begin();iter!=QuelobjetAgraget.end();iter++){
//		if(stockage.find(*iter) != stockage.end()) // on ajoute aussi du type OA
//				stockage[*iter].objetAgr.push_back(nomObjet);
//	}
//
//
//}



void Figure::Afficher(){

	map<string,ElementGeo*>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++){
		it->second->Afficher();
	}
}

	Figure::Figure(){
		// TODO Auto-generated constructor stub
	}

	Figure::~Figure() {
			// TODO Auto-generated destructor stub
	}
