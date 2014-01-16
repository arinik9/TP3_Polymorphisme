
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
//	if(cmd.numeroOperation != 5 || cmd.numeroOperation !=6) // pas de Commande Undo et Redo
		Undo.push(cmd);
}

bool Figure::ExecuteUndo(){
	Commande cmd;
	bool res=true;
	if (Undo.empty()){
		res=false;
	}

	if (res){
		cmd=Undo.top();
		Redo.push(cmd); //Undo.top()  -->>  supprimer le dernier element qui est inseré
		Undo.pop();

		if(cmd.numeroOperation==1){//1=ajouter
			//donc supprimer
			map<string,ElementGeo*>::iterator it;
			it=elements.find(cmd.nom);
			elements.erase(it);
		}
		if(cmd.numeroOperation==2){//2=supprimer
			//donc ajouter
			if(cmd.listeObjetString.empty())
				Ajouter(cmd.type,cmd.nom,cmd.points);
			else{
				//Ajouter string
			}
		}
		if(cmd.numeroOperation==3){//3=deplacer
			Deplacer(cmd.nom,(-1)*cmd.points[0],(-1)*cmd.points[1]);
		}
		if(cmd.numeroOperation==4){//4=clear

		}
	}
	return res;
}

bool Figure::ExecuteRedo(){
	Commande cmd;
	bool res=true;
	if (Redo.empty())
		res=false;

	if(res){
		cmd=Redo.top();
		Undo.push(cmd); //Undo.top()  -->>  supprimer le dernier element qui est inseré
		Redo.pop();

		if(cmd.numeroOperation==1){//ajouter
			if(cmd.listeObjetString.empty())
				Ajouter(cmd.type,cmd.nom,cmd.points);
			else{
				//Ajouter string
			}
		}
		if(cmd.numeroOperation==2){//supprimer
			map<string,ElementGeo*>::iterator it;
			it=elements.find(cmd.nom);
			elements.erase(it);
		}
		if(cmd.numeroOperation==3){//deplacer
			Deplacer(cmd.nom,cmd.points[0],cmd.points[1]);
		}
		if(cmd.numeroOperation==4){//clear

		}
	}
	return res;
}
/*
void Figure::Ajouter(string nomObjet, set<string> QuelobjetAgraget){
	set<string>::iterator iter;
	map<string,Parametres>::iterator it;
	vector<string>::iterator itVec;

	for(iter=QuelobjetAgraget.begin();iter!=QuelobjetAgraget.end();iter++){
		stockage[nomObjet].elementObjAgr.push_back(*iter);
	}

	for(iter=QuelobjetAgraget.begin();iter!=QuelobjetAgraget.end();iter++){
		if(stockage.find(*iter) != stockage.end()) // on ajoute aussi du type OA
				stockage[*iter].objetAgr.push_back(nomObjet);
	}


}*/



void Figure::Afficher(){

	map<string,ElementGeo*>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++){
		it->second->Afficher();
	}
}


void Figure::Deplacer(string nom,long x,long y){
	map<string,ElementGeo*>::iterator it;

	 it=elements.find(nom);
	 it->second->Deplacer(x,y);
}

void Figure::Supprimer(set<string> listeObjets){
	bool erreur = false;
	set<string>::iterator itSet;
	map<string, ElementGeo*>::iterator itMap;
	for (itSet = listeObjets.begin(); itSet != listeObjets.end(); itSet++){
		itMap = elements.find(*itSet);
		if (itMap == elements.end()){
			erreur = true;
			break;
		}
	}
	if (erreur == false){
		for (itSet = listeObjets.begin(); itSet != listeObjets.end(); itSet++){
			itMap = elements.find(*itSet);
			elements.erase(itMap);
		}
		//cout << "OK" << endl;
	}
	else{
		cout << "ERR" << endl;
		cout << "# Au moins un nom est invalide" << endl;
	}
}

void Figure::Sauvegarder(){
	map<string,ElementGeo*>::iterator it;
	ofstream myfile("/home/nejat/Masaüstü/babayaro.txt");
	if (myfile.is_open()){
		for (it = elements.begin(); it != elements.end(); it++){
			it->second->Sauvegarder(myfile);
		}

		myfile.close();
	}
}

	Figure::Figure(){
		// TODO Auto-generated constructor stub
	}

	Figure::~Figure() {
			// TODO Auto-generated destructor stub
	}
