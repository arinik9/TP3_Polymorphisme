
#include "Figure.h"



bool Figure::Ajouter(string type, string nomObjet, vector<long> points, bool discret){
	//map<string,ElementGeo*>::iterator it;
	//vector<long>::iterator itVec;
	//vector<string> vide;
	if (elements.find(nomObjet) == elements.end()) { // si le nom d'objet n'est pas trouvee, donc on l'ajoute 
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
		if (!discret){
		cout << "OK" << endl;
		}
		return true;
	}
	else {
		if (!discret){
			cout << "ERR" << endl;
			cout << "#This name is already used" << endl;
		}
		return false;
	}
}

int Figure::AjouterOA(string nomObjet, set<string> listeObjets, bool discret){
	if (elements.find(nomObjet) == elements.end()) {
		bool erreur = false;
		set<string>::iterator itSet;
		map<string, ElementGeo*>::iterator itMap;
		for (itSet = listeObjets.begin(); itSet != listeObjets.end(); ++itSet){
			itMap = elements.find(*itSet);
			if (itMap == elements.end()){
				erreur = true;
				break;
			}
		}
		if (erreur == false){// si touc va bien, on peut creer le OA
			ObjetAgrege* objetAgrege = new ObjetAgrege(nomObjet);
			elements[nomObjet] = objetAgrege;
			for (itSet = listeObjets.begin(); itSet != listeObjets.end(); ++itSet){
				itMap = elements.find(*itSet);
				objetAgrege->AjouterDansOA(*itSet, itMap->second); //Ajoute l'element dans la map de l'OA
				itMap->second->AjouterDansListeOA(nomObjet, objetAgrege); //Ajoute l'OA dans la map de l'element
			}
			if (!discret){ cout << "OK" << endl; }
			return 1;
		}
		else{
			if (!discret){
				cout << "ERR" << endl;
				cout << "#At least one element does not exist" << endl;
			}
			return 2;
		}
	}
	else{
		if (!discret){
			cout << "ERR" << endl;
			cout << "#This name is already used" << endl;
		}
		return 0;
	}
}


bool Figure::Supprimer(set<string> listeObjets){
	bool erreur = false;
	set<string>::iterator itSet;
	map<string, ElementGeo*>::iterator itMap;
	for (itSet = listeObjets.begin(); itSet != listeObjets.end(); ++itSet){
		itMap = elements.find(*itSet);
		if (itMap == elements.end()){
			erreur = true;
			break;
		}
	}
	if (erreur == false){
		for (itSet = listeObjets.begin(); itSet != listeObjets.end(); ++itSet){
			itMap = elements.find(*itSet);
			itMap->second->RetirerDesOA();
			if (itMap->second->getType() == "OA"){
				((ObjetAgrege*)(itMap->second))->RetirerDesObjets();
			}
			//delete itMap->second;
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

	for (it = elements.begin(); it != elements.end(); ++it){
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
	if (Undo.empty()){ //si il n'y a pas eu de commande  a faire 
		res = false;
	}

	if (res){
		if (op == true){
			while (!Redo.empty()) // on dépile donc Redo va etre vide
				Redo.pop();
		}

		cmd = Undo.top();
		Redo.push(cmd); // transferer le dernier commande
		Undo.pop(); //Undo.pop(); supprimer le dernier commande qui est inseré

		if (cmd.numeroOperation == 1){//1=ajouter
			//donc supprimer
			set<string> temp;
			temp.insert(cmd.nom);
			Supprimer(temp);
		}
		else if (cmd.numeroOperation == 2){//2=supprimer
			//donc ajouter
			set<string>::iterator setIt;
			set<string>::iterator itListeOA;
			map<string, ElementGeo*>::iterator itElementOA;
			map<string, ElementGeo*>::iterator itElementObjet;
			int reussi = 0;
			int addFail = 1;
			for (setIt = cmd.listeObjetString.begin(); setIt != cmd.listeObjetString.end(); ++setIt){//cmd.listeObjetString=les parametres (objets) utilisee a cote de la type commande -->> par exemple;  DELETE objet1 objet2
				if (cmd.contenuEtType[*setIt].type != "OA"){ //type!=OA
					Ajouter(cmd.contenuEtType[*setIt].type, *setIt, cmd.contenuEtType[*setIt].vects, 1);
					//Recreation de la liste des OA contenant l'objet et reinsertion de l'objet dans les OA correspondants
					for (itListeOA = cmd.contenuEtType[*setIt].listeDesOA.begin(); itListeOA != cmd.contenuEtType[*setIt].listeDesOA.end(); ++itListeOA){ //listeDesOA= les objets agregees dans lesquels l'objet simple se trouve  
						itElementOA = elements.find(*itListeOA); //recherche l'une des objets agregees dans lequel l'objet simple se trouve, selon le map qu'on utilise pour stocker l'informations au cours d'utilisation de la commande 'UNDO' dans notre map 'elements' 
						itElementObjet = elements.find(*setIt);
						if (itElementOA != elements.end()){
							itElementObjet->second->AjouterDansListeOA(*itListeOA, ((ObjetAgrege*)(itElementOA->second)));
							((ObjetAgrege*)(itElementOA->second))->AjouterDansOA(*setIt, itElementObjet->second);
						}
					}
				}
			}
			while(addFail > 0){ // pour empecher une creation d'un objet agregee a partir d'un objet inexistant
				addFail=0;
				for (setIt = cmd.listeObjetString.begin(); setIt != cmd.listeObjetString.end(); ++setIt){
					if (cmd.contenuEtType[*setIt].type == "OA"){ // type = OA
						reussi = AjouterOA(*setIt, cmd.contenuEtType[*setIt].contenuPlusieursObjetsString, 1);
						if(reussi==2){
							addFail++;
						}
						//Recreation de la liste des OA contenant l'objet et r�insertion de l'objet dans les OA correspondants
						if(reussi==1){
							set<string>::iterator itListeOA;
							map<string, ElementGeo*>::iterator itElementOA;
							map<string, ElementGeo*>::iterator itElementObjet;
							for (itListeOA = cmd.contenuEtType[*setIt].listeDesOA.begin(); itListeOA != cmd.contenuEtType[*setIt].listeDesOA.end(); ++itListeOA){
								itElementOA = elements.find(*itListeOA);
								itElementObjet = elements.find(*setIt);
								if (itElementOA != elements.end()){
									itElementObjet->second->AjouterDansListeOA(*itListeOA, ((ObjetAgrege*)(itElementOA->second)));
									((ObjetAgrege*)(itElementOA->second))->AjouterDansOA(*setIt, itElementObjet->second);
								}

							}
						}
					}
				}
			}
			cout << "OK" << endl;
		}
		else if (cmd.numeroOperation == 3){//3=deplacer
			vector<string> vect;
			Deplacer(cmd.nom, (-1)*cmd.points[0], (-1)*cmd.points[1], vect); 
		}
		else if (cmd.numeroOperation == 4){//4=clear
			map<string, ElementGeo*>::iterator it;
			int addFail = 1;
			int reussi = 0;
			while (addFail > 0){ //pour empecher une creation d'un objet agregee a partir d'un objet in existant 
				addFail = 0;
				for (it = cmd.objetsCopiees.begin(); it != cmd.objetsCopiees.end(); ++it){// cmd.objetCopiees= le dernier version de la map qui est copiee avant d'etre effacer dans le methode clear() 
					if (it->second->getType() == "C" || it->second->getType() == "R" || it->second->getType() == "L" || it->second->getType() == "PL"){// si type= simple
						Ajouter(it->second->getType(), it->first, it->second->getPoints(), 1);
					}
					else{// c-a-d type=OA
						reussi =AjouterOA(it->first, it->second->getObjetsGeo(),1);
						if(reussi==2){
							addFail++;
						}
					}
				}
			}
			cout << "OK" << endl;
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
		if (op){ // si il y a un changement sur l'ecran imaginaire, on depile tous les commandes qui sont dans le stack Redo
			while (!Redo.empty()) // on depile donc Redo va etre vide
				Redo.pop();
		}

		if (!op){ //Suite de commande UNDO
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
			clear(false);
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
		for (it = elements.begin(); it != elements.end(); ++it){
			string type = it->second->getType();
			if (type != "OA")
				it->second->Sauvegarder(myfile);//La methode Sauvegarder(ofstream) appelle la methode virtuale Sauvegarder() dans ElementGeo.h
			else{//on met les OA a cote pour ne pas permettre une creation d'un OA a partir d'un objet inexistant
				temp.insert(*it);//tampon
			}
		}

		for (it = temp.begin(); it != temp.end(); ++it){
			it->second->Sauvegarder(myfile);//maintenant l'ecriture des OA dans le fichiers
		}

		myfile.close();
	}
}

map<string, ElementGeo*> Figure::clear(bool del){
	map<string, ElementGeo*> objetcopiees;
	map<string, ElementGeo*>::iterator it;
	for (it = elements.begin(); it != elements.end(); ++it){
		objetcopiees[it->first] = it->second;
		if(del==true){// pour les desallocation des objets qui sont dans le map 'elements', utilisation unique juste pour la commande "EXIT"
			delete (it->second);
		}
	}
	elements.clear();
	if(del==false){
		cout << "OK" << endl;
	}
	return objetcopiees; //retourne un map
}

set<string> Figure::getContenuObjet(string nom){
	set<string> a;
	map<string, ElementGeo*>::iterator it;
	it = elements.find(nom);// a partir d'un nom de OA, on obtient les elements de ce OA  
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
	it = elements.find(nom);   // a partir du nom d'un objet simple, on obtient les points utilisees
	a = it->second->getPoints();


	return a;
}


string Figure::getType(string nom){
	string type="";
	map<string, ElementGeo*>::iterator it;
	it = elements.find(nom);
	if (it != elements.end()){
		type = it->second->getType(); // grace a la methode GetType() virtuale
	}
	return type;
}

void Figure::ViderStacks(){
	while (!Undo.empty()){ // on depile donc Redo va etre vide
		Undo.pop();
	}
	while (!Redo.empty()){ // on depile donc Redo va etre vide
		Redo.pop();
	}
}

	Figure::Figure(){
		// TODO Auto-generated constructor stub
	}

	Figure::~Figure() {
			// TODO Auto-generated destructor stub
	}
