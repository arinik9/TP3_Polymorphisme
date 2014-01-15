#include "Figure.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "LectureEcriture.h"
#include "Cercle.h"

using namespace std;

void TraiterCommande(LigneDeCommande& lc, Figure& myFig) {
	if (!lc.error) {
		if (lc.type == "PL" || lc.type == "C" || lc.type == "R" || lc.type == "L") {
			myFig.Ajouter(lc.type, lc.nom, lc.points);
			cout << "OK" << endl;
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


	 return 0;
}
