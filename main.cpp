#include "Figure.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "LectureEcriture.h"
<<<<<<< HEAD
#include "Cercle.h"

using namespace std;

void TraiterCommande(LigneDeCommande& lc, Figure& myFig) {
	if (!lc.error) {
		if (lc.type == "PL" || lc.type == "C" || lc.type == "R" || lc.type == "L") {
			myFig.Ajouter(lc.type, lc.nom, lc.points);
			cout << "OK" << endl;
=======

using namespace std;

void ClassificationObjetEtAjouterDansLeMap(LigneDeCommande& lc, Figure& myFig) {
	//ClassificationObjetsEtAjouterDansLeMap(lc, myFig);
	if (!lc.error) {
		if (lc.type == "PL" || lc.type == "C" || lc.type == "R") {
			myFig.Ajouter(lc.nom, lc.points);
		}
		if (lc.type == "OA") {
			myFig.Ajouter(lc.nom, lc.NomObjetUnique);
		}
		if (lc.type == "LIST" || lc.type == "UNDO" || lc.type == "REDO"
				|| lc.type == "CLEAR" || lc.type == "EXIT") {
			cout << "OK " << lc.type << endl;
		}
	} else if (lc.error) {
		cout << "ERR" << endl;
	}
}

int main() {
        Figure myFig;

        string commande;
        std::string token;
        do {
        getline(std::cin, commande);
        std::istringstream ss(commande);

        getline(ss, token, ' ');//Premier Mot

        if(token=="LOAD"){
		getline(ss, token, '\n');
		if(token.substr(token.length()-4,4) == ".txt"){
			LectureEcriture l(token.c_str());//"/home/nejat/Masaüstü/toto.txt"
			while(!l.EstFini()){
				LigneDeCommande lc;
				lc=l.ProchainLigne();
				ClassificationObjetEtAjouterDansLeMap(lc, myFig);
				 }
			}
        }
        else if(token=="C" || token=="PL" || token=="L" || token=="OA" || token=="R"){
		int a=1;
		cout << "else e girdi";
		LectureEcriture l(commande,a);
		LigneDeCommande lc;
		lc=l.ProchainLigne();
		ClassificationObjetEtAjouterDansLeMap(lc, myFig);
        }
}while(token!="EXIT");

        cout << "VOILA ce qu'on a dans le MAP:" << endl;
        myFig.Afficher();


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
>>>>>>> 2e7159e0647be8fae7bdc32e5bfdb9ca7c8d830e
		}
		else if (lc.type == "OA") {
			//myFig.Ajouter(lc.nom, lc.NomObjetUnique);
		}
		else if (lc.type == "UNDO" || lc.type == "REDO" || lc.type == "CLEAR" || lc.type == "EXIT") {
			cout << "OK " << lc.type << endl;
		}
		/*else if (lc.type == "LIST"){
			map<string, ElementGeo*>::iterator it;
			cout << "Nom : " << it->first << " Rayon : " << ((Cercle*)(it->second))->getRayon() << endl;
		}*/
	} else if (lc.error) {
		cout << "ERR" << endl;
	}
}

int main() {
        Figure myFig;

        string commande;
        std::string token;
        do {
        getline(std::cin, commande);
        std::istringstream ss(commande);

<<<<<<< HEAD
        getline(ss, token, ' ');//Premier Mot

        if(token=="LOAD"){
		getline(ss, token, '\n');
		if(token.substr(token.length()-4,4) == ".txt"){
			LectureEcriture l(token.c_str());
			while(!l.EstFini()){
				LigneDeCommande lc;
				lc=l.ProchainLigne();
				TraiterCommande(lc, myFig);
				 }
			}
        }
        else if(token=="C" || token=="PL" || token=="L" || token=="OA" || token=="R"){
		int a=1;
		LectureEcriture l(commande,a);
		LigneDeCommande lc;
		lc=l.ProchainLigne();
		TraiterCommande(lc, myFig);
        }
		else if (token == "LIST"){
			myFig.Afficher();
		}
}while(token!="EXIT");
=======
*/
	 /*Figure myfigure;
	 myfigure.ajouter(typ, nom,vect);
	 vect.clear();
	 //void figure::ajouter(string typeElement,string nom,const vector<long>& vec){*/
	 return 0;
>>>>>>> 2e7159e0647be8fae7bdc32e5bfdb9ca7c8d830e


	 return 0;
}
