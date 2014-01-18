
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
			ElementGeo* ligne = new Ligne(type,nomObjet, points[0], points[1], points[2], points[3]);
			elements[nomObjet] = ligne;
		}
		else if (type == "PL"){
			ElementGeo* polyligne = new PolyLigne(nomObjet, points);
			elements[nomObjet] = polyligne;
		}
		else{
				cout << "ELSE" << endl;
			}
	}

}

void Figure::AjouterCommandeDansStack(Commande& cmd){
//	if(cmd.numeroOperation != 5 || cmd.numeroOperation !=6) // pas de Commande Undo et Redo
		Undo.push(cmd);
}

bool Figure::ExecuteUndo(bool op){
	Commande cmd;
	bool res=true;
	if (Undo.empty()){
		res=false;
	}

	if (res){
		if(op==true){
			while(!Redo.empty()) // on dépile donc Redo va etre vide
			Redo.pop();
		}

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
			vector<string> vect;
			Deplacer(cmd.nom,(-1)*cmd.points[0],(-1)*cmd.points[1],vect);
		}
		if(cmd.numeroOperation==4){//4=clear
			map<string, ElementGeo*>::iterator it=cmd.objetsCopiees.begin();
			for(it=cmd.objetsCopiees.begin();it!=cmd.objetsCopiees.end();it++){
				if(it->second->GetType()=="C" || it->second->GetType()=="R" || it->second->GetType()=="L"  || it->second->GetType()=="PL"){
					Ajouter(it->second->GetType(),it->first,it->second->GetPoints());
				}
			}
		}
	}
	return res;
}

bool Figure::ExecuteRedo(bool op){
	Commande cmd;
	bool res=true;
	if (Redo.empty())
		res=false;

	if(res){
		cmd=Redo.top();
		if(op){
			while(!Redo.empty()) // on dépile donc Redo va etre vide
				Redo.pop();
		}

		if(!op){
			Undo.push(cmd);
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
			vector<string> vect;
			Deplacer(cmd.nom,cmd.points[0],cmd.points[1],vect);
		}
		if(cmd.numeroOperation==4){//clear
			clear();
				}
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


void Figure::Deplacer(string nom,long x,long y,vector<string> objetsDeplaces){
	map<string, ElementGeo*>::iterator it;
		it = elements.find(nom);
		if (it != elements.end()){
			it->second->Deplacer(x, y, objetsDeplaces);
			cout << "OK" << endl;
		}
		else{
			cout << "ERR" << endl;
			cout << "# L'objet n'existe pas" << endl;
		}
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

void Figure::Sauvegarder(string nomFichier){
	map<string,ElementGeo*>::iterator it;
		map<string,ElementGeo*> temp;
		string chemin="/home/nejat/Masaüstü/"; // optionnel
		chemin+=nomFichier;
		ofstream myfile(chemin.c_str());
		if (myfile.is_open()){
			for (it = elements.begin(); it != elements.end(); it++){
				string type=it->second->GetType();
				if(type!="OA")
					it->second->Sauvegarder(myfile);
				else{
					temp.insert(*it);
				}
			}

			for (it = temp.begin(); it != temp.end(); it++){
				it->second->Sauvegarder(myfile);
			}

			myfile.close();
		}
}

map<string, ElementGeo*> Figure::clear(){
	map<string, ElementGeo*> objetcopiees;
	map<string, ElementGeo*>::iterator it;
	for(it=elements.begin();it!=elements.end();it++){
		objetcopiees[it->first]=it->second;
	}
	elements.clear();

	return objetcopiees;
}
	Figure::Figure(){
		// TODO Auto-generated constructor stub
	}

	Figure::~Figure() {
			// TODO Auto-generated destructor stub
	}
