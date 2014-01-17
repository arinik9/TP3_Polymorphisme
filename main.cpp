#include "Figure.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "LectureEcriture.h"
#include "Cercle.h"

using namespace std;

void TraiterCommande(LigneDeCommande& lc, Figure& myFig,bool load,bool opChange) {
	Commande cmd;
	cmd.nom=lc.nom;
	cmd.type=lc.type;
	cmd.points=lc.points;
	cmd.listeObjetString=lc.listeObjets;
	//ajouter=1;
	// supprimer=2;
	// deplacer=3;
	// clear=4;
	// undo=5;
	// redo=6;

/*if (type == "LIST"){
		cout << "LIIIIIST" << endl;

	map<string, ElementGeo*>::iterator it;
	cout << "Nom : " << it->first << " Rayon : " << ((Cercle*)(it->second))->getRayon() << endl;
}*/

	if (!lc.error) {
		if (lc.type == "PL" || lc.type == "C" || lc.type == "R" || lc.type == "L") {
			myFig.Ajouter(lc.type, lc.nom, lc.points);
			cmd.numeroOperation=1;
		}
		else if (lc.type == "OA") {
			//myFig.Ajouter(lc.nom, lc.NomObjetUnique);

		}
		else if (lc.type == "UNDO") {
			cmd.numeroOperation=5;
			myFig.ExecuteUndo(opChange);
		}
		else if (lc.type == "REDO") {
			cmd.numeroOperation=6;
			myFig.ExecuteRedo(opChange);
				}
		else if (lc.type == "DELETE"){
			myFig.Supprimer(lc.listeObjets);
			cmd.numeroOperation=2;
				}
		else if (lc.type == "CLEAR") {
			cmd.numeroOperation=4;
				}
		else if (lc.type == "MOVE") {
			vector<string> objetsDeplaces;
			myFig.Deplacer(lc.nom, lc.points[0], lc.points[1], objetsDeplaces);
			cmd.numeroOperation=3;
						}


		if(cmd.numeroOperation<=4 && cmd.numeroOperation>=1 && !load)
			myFig.AjouterCommandeDansStack(cmd);

	} else if (lc.error) {
		cout << "ERR" << endl;
	}
}

int main() {
        Figure myFig;
        bool load=false;
        bool operationQuiChangeQqchSurEcran=false;
        string commande;
        std::string token;
        do {
        getline(std::cin, commande);
        std::istringstream ss(commande);

        getline(ss, token, ' ');//Premier Mot

        if(token=="LOAD"){
        	load=true;
		getline(ss, token, '\n');
		if(token.substr(token.length()-4,4) == ".txt"){
			LectureEcriture l(token.c_str());
			while(!l.EstFini()){
				LigneDeCommande lc;
				lc=l.ProchainLigne();
				TraiterCommande(lc, myFig,load,operationQuiChangeQqchSurEcran);
				 }
			}
		cout << "OK" << endl;
		load=false;
        }
        else if(token=="C" || token=="PL" || token=="L" || token=="OA" || token=="R" || token=="UNDO" || token=="REDO" || token=="MOVE" || token=="CLEAR" || token=="DELETE" ){
		int a=1;
		LectureEcriture l(commande,a);
		LigneDeCommande lc;
		lc=l.ProchainLigne();
		TraiterCommande(lc, myFig,load,operationQuiChangeQqchSurEcran);
		cout << "OK" << endl;

		if(token!="UNDO" && token!="REDO" && token!="UNDO")
			operationQuiChangeQqchSurEcran=true;
		else
			operationQuiChangeQqchSurEcran=false;

        }
		else if (token == "LIST"){
			cout << "OK" << endl;
			myFig.Afficher();
		}
		else if (token == "SAVE"){
			getline(ss, token, '\n');
			if(token.substr(token.length()-4,4) == ".txt"){
				myFig.Sauvegarder(token);
				cout << "OK" << endl;
			}
			else
				cout <<"ERR" << endl << "#ecrivez .txt pour le fichier!" << endl;
			}
}while(token!="EXIT");


	 return 0;
}
