#include "Figure.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "LectureEcriture.h"
#include "Cercle.h"

using namespace std;

void TraiterCommande(LigneDeCommande& lc, Figure& myFig) {
	Commande cmd;
	cmd.nom=lc.nom;
	cmd.type=lc.type;
	cmd.points=lc.points;
	/*else if (lc.type == "LIST"){
				map<string, ElementGeo*>::iterator it;
				cout << "Nom : " << it->first << " Rayon : " << ((Cercle*)(it->second))->getRayon() << endl;
			}*/
	int ajouter=1;
	int supprimer=2;
	int deplacer=3;
	int clear=4;
	int undo=5;
	int redo=6;

	if (!lc.error) {
		if (lc.type == "PL" || lc.type == "C" || lc.type == "R" || lc.type == "L") {
			myFig.Ajouter(lc.type, lc.nom, lc.points);
			cout << "OK" << endl;
			cmd.numeroOperation=1;
		}
		else if (lc.type == "OA") {
			//myFig.Ajouter(lc.nom, lc.NomObjetUnique);
		}
		else if (lc.type == "UNDO") {
			cout << "OK " << lc.type << endl;
			cmd.numeroOperation=5;
			myFig.ExecuteUndo();
		}
		else if (lc.type == "REDO") {
			cout << "OK " << lc.type << endl;
			cmd.numeroOperation=6;
			myFig.ExecuteRedo();
				}
		else if (lc.type == "DELETE") {
			cout << "OK " << lc.type << endl;
			cmd.numeroOperation=2;
				}
		else if (lc.type == "CLEAR") {
			cout << "OK " << lc.type << endl;
			cmd.numeroOperation=4;
				}
		else if (lc.type == "MOVE") {
			cout << "OK " << lc.type << endl;
			cmd.numeroOperation=3;
						}
		else if (lc.type == "EXIT") {
			cout << "OK " << lc.type << endl;
					//myFig.Ajouter(lc.nom, lc.NomObjetUnique);
						}

		if(cmd.numeroOperation<=4 && cmd.numeroOperation>=1)
			myFig.AjouterCommandeDansStack(cmd);

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
