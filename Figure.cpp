
#include "Figure.h"



bool Figure::Ajouter(string type, string nomObjet, vector<long> points, bool load){
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
			ElementGeo* ligne = new Ligne(type, nomObjet, points[0], points[1], points[2], points[3]);
			elements[nomObjet] = ligne;
		}
		else if (type == "PL"){
			ElementGeo* polyligne = new PolyLigne(nomObjet, points);
			elements[nomObjet] = polyligne;
		}
		if (!load){
		cout << "OK" << endl;
		}
		return true;
	}
	else {
		if (!load){
			cout << "ERR" << endl;
			cout << "#This name is already used" << endl;
		}
		return false;
	}
}

bool Figure::AjouterOA(string nomObjet, set<string> listeObjets, bool load){
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
			if (!load){ cout << "OK" << endl; }
			return true;
		}
		else{
			if (!load){
				cout << "ERR" << endl;
				cout << "#At least one element does not exist" << endl;
			}
			return false;
		}
	}
	else{
		if (!load){
			cout << "ERR" << endl;
			cout << "#This name is already used" << endl;
		}
		return false;
	}
}


bool Figure::Supprimer(set<string> listeObjets){
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
			if (itMap->second->getType() == "OA"){
				((ObjetAgrege*)(itMap->second))->RetirerDesObjets();
			}
			delete itMap->second;
			elements.erase(itMap);
		}
		cout << "OK" << endl;
		return true;
	}
	else{
		cout << "ERR" << endl;
		cout << "#At least one element does not exist" << endl;
		return false;
	}
}


void Figure::Afficher(){

	map<string,ElementGeo*>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++){
		it->second->Afficher();
	}
}

bool Figure::Deplacer(string nom, long x, long y, vector<string>& objetsDeplaces){
	map<string, ElementGeo*>::iterator it;
	it = elements.find(nom);
	if (it != elements.end()){
		it->second->Deplacer(x, y, objetsDeplaces);
		cout << "OK" << endl;
		return true;
	}
	else{
		cout << "ERR" << endl;
		cout << "#This element does not exist" << endl;
		return false;
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
			set<string> temp;
			temp.insert(cmd.nom);
			Supprimer(temp);
		}
		if (cmd.numeroOperation == 2){//2=supprimer
			//donc ajouter
			set<string>::iterator setIt;
			for (setIt = cmd.listeObjetString.begin(); setIt != cmd.listeObjetString.end(); setIt++){
				if (cmd.contenuEtType[*setIt].type != "OA"){ // OA degilse
					Ajouter(cmd.contenuEtType[*setIt].type, *setIt, cmd.contenuEtType[*setIt].vects, 0);
					//Recréation de la liste des OA contenant l'objet et réinsertion de l'objet dans les OA correspondants
					set<string>::iterator itListeOA;
					map<string, ElementGeo*>::iterator itElementOA;
					map<string, ElementGeo*>::iterator itElementObjet;
					for (itListeOA = cmd.contenuEtType[*setIt].listeDesOA.begin(); itListeOA != cmd.contenuEtType[*setIt].listeDesOA.end(); itListeOA++){
						itElementOA = elements.find(*itListeOA);
						itElementObjet = elements.find(*setIt);
						itElementObjet->second->AjouterDansListeOA(*itListeOA, ((ObjetAgrege*)(itElementOA->second)));
						((ObjetAgrege*)(itElementOA->second))->AjouterDansOA(*setIt, itElementObjet->second);
					}
				}
			}
			for (setIt = cmd.listeObjetString.begin(); setIt != cmd.listeObjetString.end(); setIt++){
				if (cmd.contenuEtType[*setIt].type == "OA"){
					AjouterOA(*setIt, cmd.contenuEtType[*setIt].contenuPlusieursObjetsString, 0);
					//Recréation de la liste des OA contenant l'objet et réinsertion de l'objet dans les OA correspondants
					set<string>::iterator itListeOA;
					map<string, ElementGeo*>::iterator itElementOA;
					map<string, ElementGeo*>::iterator itElementObjet;
					for (itListeOA = cmd.contenuEtType[*setIt].listeDesOA.begin(); itListeOA != cmd.contenuEtType[*setIt].listeDesOA.end(); itListeOA++){
						itElementOA = elements.find(*itListeOA);
						itElementObjet = elements.find(*setIt);
						itElementObjet->second->AjouterDansListeOA(*itListeOA, ((ObjetAgrege*)(itElementOA->second)));
						((ObjetAgrege*)(itElementOA->second))->AjouterDansOA(*setIt, itElementObjet->second);
					}
				}
			}
		}
		if (cmd.numeroOperation == 3){//3=deplacer
			vector<string> vect;
			Deplacer(cmd.nom, (-1)*cmd.points[0], (-1)*cmd.points[1], vect);
		}
		if (cmd.numeroOperation == 4){//4=clear
			map<string, ElementGeo*>::iterator it = cmd.objetsCopiees.begin();
			for (it = cmd.objetsCopiees.begin(); it != cmd.objetsCopiees.end(); it++){
				if (it->second->getType() == "C" || it->second->getType() == "R" || it->second->getType() == "L" || it->second->getType() == "PL"){
					Ajouter(it->second->getType(), it->first, it->second->getPoints(), 0);
				}
				else{// c=a=d type=OA
					AjouterOA(it->first, it->second->getObjetsGeo(),0);
				}
			}
		}
	}
		//if (res == true){ cout << "OK" << endl; }
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
			while (!Redo.empty()) // on dÃÂ©pile donc Redo va etre vide
				Redo.pop();
		}

		if (!op){
			Undo.push(cmd);
			Redo.pop();


			if (cmd.numeroOperation == 1){//ajouter
				if (cmd.listeObjetString.empty())
					Ajouter(cmd.type, cmd.nom, cmd.points,0);
				else{
					AjouterOA(cmd.nom, cmd.listeObjetString,0);
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
	string chemin = ""; // optionnel
	chemin += nomFichier;
	ofstream myfile(chemin.c_str());
	if (myfile.is_open()){
		for (it = elements.begin(); it != elements.end(); it++){
			string type = it->second->getType();
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

map<string, ElementGeo*> Figure::clear(){
	map<string, ElementGeo*> objetcopiees;
	map<string, ElementGeo*>::iterator it;
	for (it = elements.begin(); it != elements.end(); it++){
		objetcopiees[it->first] = it->second;
	}
	elements.clear();

	return objetcopiees;
}

set<string> Figure::getContenuObjet(string nom){
	set<string> a;
	map<string, ElementGeo*>::iterator it;
	it = elements.find(nom);
	a = it->second->getObjetsGeo();

	return a;
}

set<string> Figure::getListeOA(string nom){
	set<string> a;
	map<string, ElementGeo*>::iterator it;
	it = elements.find(nom);
	a = it->second->getObjetsAgreges();

	return a;
}

vector<long> Figure::getPoints(string type, string nom){
	vector<long> a;
	map<string, ElementGeo*>::iterator it;
	it = elements.find(nom);
	a = it->second->getPoints();


	return a;
}


string Figure::getType(string nom){
	string type="";
	map<string, ElementGeo*>::iterator it;
	it = elements.find(nom);
	if (it != elements.end()){
		type = it->second->getType();
	}
	return type;
}

void Figure::ViderStacks(){
	while (!Undo.empty()){ // on dÃÂ©pile donc Redo va etre vide
		Undo.pop();
	}
	while (!Redo.empty()){ // on dÃÂ©pile donc Redo va etre vide
		Redo.pop();
	}
}

	Figure::Figure(){
		// TODO Auto-generated constructor stub
	}

	Figure::~Figure() {
			// TODO Auto-generated destructor stub
	}
