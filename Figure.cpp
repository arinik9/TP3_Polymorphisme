
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
#include <map>

using namespace std;


void Figure::Ajouter(string type, string nomObjet, vector<long> points){
	//map<string,ElementGeo*>::iterator it;
	//vector<long>::iterator itVec;
	//vector<string> vide;
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
		cout << "OK" << endl;
	}
	else {
		cout << "ERR" << endl;
		cout << "#This name is already used" << endl;
	}
}

void Figure::AjouterOA(string nomObjet, set<string> listeObjets){
	if (elements.find(nomObjet) == elements.end()) {
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
			ObjetAgrege* objetAgrege = new ObjetAgrege(nomObjet);
			elements[nomObjet] = objetAgrege;
			for (itSet = listeObjets.begin(); itSet != listeObjets.end(); itSet++){
				itMap = elements.find(*itSet);
				objetAgrege->AjouterDansOA(*itSet, itMap->second); //Ajoute l'élément dans la map de l'OA
				itMap->second->AjouterDansListeOA(nomObjet, objetAgrege); //Ajoute l'OA dans la map de l'élément
			}
			cout << "OK" << endl;
		}
		else{
			cout << "ERR" << endl;
			cout << "#At least one object does not exist" << endl;
		}
	}
	else{
		cout << "ERR" << endl;
		cout << "#This name is already used" << endl;
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
			itMap->second->RetirerDesOA();
			if (itMap->second->GetType() == "OA"){
				((ObjetAgrege*)(itMap->second))->RetirerDesObjets();
			}
			elements.erase(itMap);
		}
		cout << "OK" << endl;
	}
	else{
		cout << "ERR" << endl;
		cout << "# Au moins un nom est invalide" << endl;
	}
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



//void Figure::Ajouter(string typeElement,string nom, vector<long> vec){
//
//	if(typeElement == "C"){
//
//		if(vec.size() != 3){
//			cout << "invalid parameters" << endl;
//		}
//		else{
//		long x = vec[0];
//		long y = vec[1];
//		long rayon = vec[2];
//		ElementGeo* temp = new Cercle(nom,x,y,rayon);
//		elements.push_back(temp);
//		cout << "New object :" << nom << endl;
//		}
//	}
//
//}

void Figure::Afficher(){

	map<string,ElementGeo*>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++){
		it->second->Afficher();
	}
}

void Figure::Deplacer(string nom, long x, long y, vector<string> objetsDeplaces){
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

void Figure::AjouterCommandeDansStack(Commande& cmd){
	//	if(cmd.numeroOperation != 5 || cmd.numeroOperation !=6) // pas de Commande Undo et Redo
	Undo.push(cmd);
}

bool Figure::ExecuteUndo(bool op){
	Commande cmd;
	bool res = true;
	if (Undo.empty()){
		res = false;
	}

	if (res){
		if (op == true){
			while (!Redo.empty()) // on dÃ©pile donc Redo va etre vide
				Redo.pop();
		}

		cmd = Undo.top();
		Redo.push(cmd); //Undo.top()  -->>  supprimer le dernier element qui est inserÃ©
		Undo.pop();

		if (cmd.numeroOperation == 1){//1=ajouter
			//donc supprimer
			map<string, ElementGeo*>::iterator it;
			it = elements.find(cmd.nom);
			elements.erase(it);
		}
		if (cmd.numeroOperation == 2){//2=supprimer

				set<string>::iterator setIt;
				for(setIt=cmd.listeObjetString.begin();setIt!=cmd.listeObjetString.end();setIt++){

					if(cmd.contenuEtType[*setIt].type!="OA"){ // OA degilse
						Ajouter( cmd.contenuEtType[*setIt].type, *setIt, cmd.contenuEtType[*setIt].vects);
						cmd.listeObjetString.erase(setIt);
					}
				}
				for(setIt=cmd.listeObjetString.begin();setIt!=cmd.listeObjetString.end();setIt++){
					if(cmd.contenuEtType[*setIt].type=="OA"){
						cout <<"OA" << endl;
						AjouterOA(*setIt,cmd.contenuEtType[*setIt].contenuPlusieursObjetsString);
					}
				}

		}
		if (cmd.numeroOperation == 3){//3=deplacer
			vector<string> vect;
			Deplacer(cmd.nom, (-1)*cmd.points[0], (-1)*cmd.points[1], vect);
		}
		if (cmd.numeroOperation == 4){//4=clear
			map<string, ElementGeo*>::iterator it=cmd.objetsCopiees.begin();
			for(it=cmd.objetsCopiees.begin();it!=cmd.objetsCopiees.end();it++){
				if(it->second->GetType()=="C" || it->second->GetType()=="R" || it->second->GetType()=="L"  || it->second->GetType()=="PL"){
						Ajouter(it->second->GetType(),it->first,it->second->GetPoints());
				}
				else{// c=a=d type=OA
					AjouterOA(it->first,it->second->GetObjetsGeo());
				}
			}
		}
	}
	return res;
}

bool Figure::ExecuteRedo(bool op){
	Commande cmd;
	bool res = true;
	if (Redo.empty())
		res = false;

	if (res){
		cmd = Redo.top();
		if (op){
			while (!Redo.empty()) // on dÃ©pile donc Redo va etre vide
				Redo.pop();
		}

		if (!op){
			Undo.push(cmd);
			Redo.pop();


			if (cmd.numeroOperation == 1){//ajouter
				if (cmd.listeObjetString.empty())
					Ajouter(cmd.type, cmd.nom, cmd.points);
				else{
					AjouterOA(cmd.nom, cmd.listeObjetString);
				}
			}
			if (cmd.numeroOperation == 2){//supprimer

				Supprimer(cmd.listeObjetString);
			}
			if (cmd.numeroOperation == 3){//deplacer
				vector<string> vect;
				Deplacer(cmd.nom, cmd.points[0], cmd.points[1], vect);
			}
		}
		if (cmd.numeroOperation == 4){//clear
			clear();
		}
	}
	return res;
}

void Figure::Sauvegarder(string nomFichier){
	map<string, ElementGeo*>::iterator it;
	map<string, ElementGeo*> temp;
	string chemin = "/home/nejat/MasaÃŒstÃŒ/"; // optionnel
	chemin += nomFichier;
	ofstream myfile(chemin.c_str());
	if (myfile.is_open()){
		for (it = elements.begin(); it != elements.end(); it++){
			string type = it->second->GetType();
			if (type != "OA")
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

set<string> Figure::GetContenuObjet(string type,string nom){
	set<string> a;
	map<string, ElementGeo*>::iterator it;
	it=elements.find(nom);
		a=it->second->GetObjetsGeo();

	return a;
}

vector<long> Figure::GetPoints(string type,string nom){
	vector<long> a;
	map<string, ElementGeo*>::iterator it;
	it=elements.find(nom);
	a=it->second->GetPoints();


	return a;
}


string Figure::GetType(string nom){
	string type;
	map<string, ElementGeo*>::iterator it;
	it=elements.find(nom);
	type=it->second->GetType();
	return type;
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
