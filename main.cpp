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
	//ajouter=1;
	// supprimer=2;
	// deplacer=3;
	// clear=4;
	// undo=5;
	// redo=6;

	if (!lc.error) {
		if (lc.type == "PL" || lc.type == "C" || lc.type == "R" || lc.type == "L") {
			myFig.Ajouter(lc.type, lc.nom, lc.points);
		//	cout << "OK" << endl;
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
			myFig.Deplacer(lc.nom,lc.points[0],lc.points[1]);
			cmd.numeroOperation=3;
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
		cout << "OK" << endl;
        }
        else if(token=="C" || token=="PL" || token=="L" || token=="OA" || token=="R" || token=="UNDO" || token=="REDO" || token=="MOVE" || token=="CLEAR" ){
		int a=1;
		LectureEcriture l(commande,a);
		LigneDeCommande lc;
		lc=l.ProchainLigne();
		TraiterCommande(lc, myFig);
		cout << "OK" << endl;
        }
		else if (token == "LIST"){
			cout << "OK" << endl;
			myFig.Afficher();
		}
}while(token!="EXIT");


	 return 0;
}
