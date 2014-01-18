/*
 C c1 1 2 3
OA oa1 c1 r1
R r1 1 2 3 4
DELETE c1 oa1 r1
*/

#include "Figure.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "LectureEcriture.h"
//#include "Cercle.h"

using namespace std;

void TraiterCommande(LigneDeCommande& lc, Figure& myFig, bool load, bool opChange) {
	Commande cmd;
	cmd.nom = lc.nom;
	cmd.type = lc.type;
	cmd.points = lc.points;
	cmd.listeObjetString = lc.listeObjets;
	//ajouter=1;
	// supprimer=2;
	// deplacer=3;
	// clear=4;
	// undo=5;
	// redo=6;
	if (!lc.error) {
		if (lc.type == "PL" || lc.type == "C" || lc.type == "R" || lc.type == "L") {
			myFig.Ajouter(lc.type, lc.nom, lc.points);
			cmd.numeroOperation = 1;
		}
		else if (lc.type == "OA") {
			myFig.AjouterOA(lc.nom, lc.listeObjets);
			cmd.numeroOperation = 1;
		}
		else if (lc.type == "UNDO") {
			cmd.numeroOperation = 5;
			myFig.ExecuteUndo(opChange);
		}
		else if (lc.type == "REDO") {
			cmd.numeroOperation = 6;
			myFig.ExecuteRedo(opChange);
		}
		else if (lc.type == "DELETE"){
			cmd.numeroOperation = 2;
			set<string>::iterator it;
			for(it=lc.listeObjets.begin();it!=lc.listeObjets.end();it++){
				set<string> a;
				cmd.type=myFig.GetType(*it);
				if(cmd.type=="OA"){
					a=myFig.GetContenuObjet(cmd.type,*it);
					cmd.contenuEtType[*it].contenuPlusieursObjetsString=a;
					cmd.contenuEtType[*it].type=cmd.type;
				}
				else{
					cmd.points=myFig.GetPoints(cmd.type,*it);
					cmd.contenuEtType[*it].vects=cmd.points;
					cmd.contenuEtType[*it].type=cmd.type;
				}
			}
			myFig.Supprimer(lc.listeObjets);

		}
		else if (lc.type == "CLEAR") {
			//map<string, ElementGeo*> objetCopiees;
			cmd.objetsCopiees=myFig.clear();
			cout << "size"<<cmd.objetsCopiees.size()<< endl;
			cmd.numeroOperation = 4;
		}
		else if (lc.type == "MOVE") {
			vector<string> objetsDeplaces;
			myFig.Deplacer(lc.nom, lc.points[0], lc.points[1], objetsDeplaces);
			cmd.numeroOperation = 3;
		}


		if (cmd.numeroOperation <= 4 && cmd.numeroOperation >= 1 && !load){
			myFig.AjouterCommandeDansStack(cmd);

		}
	}
		else if (lc.error) {
			cout << "ERR" << endl;
		}
}

/*void TraiterCommande(string type){
	if (type == "LIST"){
		cout << "LIIIIIST" << endl;
	}

		map<string, ElementGeo*>::iterator it;
		cout << "Nom : " << it->first << " Rayon : " << ((Cercle*)(it->second))->getRayon() << endl;
	}*/
//}

int main() {
        Figure myFig;
		bool load = false;
		bool operationQuiChangeQqchSurEcran = false;
        string commande;
        std::string token;
        do {
        getline(std::cin, commande);
        std::istringstream ss(commande);

        getline(ss, token, ' ');//Premier Mot

        if(token=="LOAD"){
			load = true;
			getline(ss, token, '\n');
			if(token.substr(token.length()-4,4) == ".txt"){
				LectureEcriture l(token.c_str());//"/home/nejat/Masaüstü/toto.txt"
				while(!l.EstFini()){
					LigneDeCommande lc;
					lc=l.ProchainLigne();
					TraiterCommande(lc, myFig, load, operationQuiChangeQqchSurEcran);
				}
			}
			cout << "OK" << endl;
			load = false;
        }
		else if (token == "C" || token == "PL" || token == "L" || token == "OA" || token == "R" || token == "UNDO" || token == "REDO" || token == "MOVE" || token == "CLEAR" || token == "DELETE"){
		int a=1;
		LectureEcriture l(commande,a);
		LigneDeCommande lc;
		lc=l.ProchainLigne();
		TraiterCommande(lc, myFig, load, operationQuiChangeQqchSurEcran);
		cout << "OK" << endl;

		if (token != "UNDO" && token != "REDO"){
			operationQuiChangeQqchSurEcran = true;
		}
		else{
			operationQuiChangeQqchSurEcran = false;
		}
        }
		else if (token == "LIST"){
			myFig.Afficher();
		}
		else if (token == "SAVE"){
			getline(ss, token, '\n');
			if (token.substr(token.length() - 4, 4) == ".txt"){
				myFig.Sauvegarder(token);
				cout << "OK" << endl;
			}
			else
				cout << "ERR" << endl << "#ecrivez .txt pour le fichier!" << endl;
		}
		}while(token!="EXIT");



	/*

	string commande;
	vector<long> vect;
	//cout << "C:  ";
	getline(std::cin, commande);
	string temp;
	int counter = 0;
	string toPush;
	long li;
	string comp = " ";

	for (unsigned int i = 0; i < commande.length(); i++) {
		if (commande.at(i) == ' ') {
			 if (counter >= 2) {
				stringstream ss;
			    ss << toPush;
			    ss >> li;
			    vect.push_back(li);
			    toPush = "";
			    counter++;
			}
			else {
				counter++;
			}
		}
		else {
			if(counter >= 2){
			toPush = toPush + commande[i];
			}
		}

	}
	stringstream ss1;
	 ss1 << toPush;
	 ss1 >> li;

	 cout << "R:  OK"<< endl;
	std::cout << "our vectors: ";
	for (std::vector<long>::iterator it = vect.begin(); it != vect.end();
			++it)
		std::cout << ' ' << *it;


*/
	 /*Figure myfigure;
	 myfigure.ajouter(typ, nom,vect);
	 vect.clear();
	 //void figure::ajouter(string typeElement,string nom,const vector<long>& vec){*/
	 return 0;

	// test imprimer le vector

}
