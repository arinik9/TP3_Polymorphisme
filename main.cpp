#include "Figure.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "LectureEcriture.h"
using namespace std;


bool TraiterCommande(LigneDeCommande& lc, Figure& myFig, bool load, bool opChange, int& loadFail) {
	Commande cmd;
	cmd.nom = lc.nom;
	cmd.type = lc.type;
	cmd.points = lc.points;
	cmd.listeObjetString = lc.listeObjets;
	// numeroOperation :
	// ajouter=1;
	// supprimer=2;
	// deplacer=3;
	// clear=4;
	// undo=5;
	// redo=6;
	bool succes=false;
	if (!lc.error) {
		if (lc.type == "PL" || lc.type == "C" || lc.type == "R" || lc.type == "L") {
			succes = myFig.Ajouter(lc.type, lc.nom, lc.points, load);
			cmd.numeroOperation = 1;
		}
		else if (lc.type == "OA") {
			int reussi = myFig.AjouterOA(lc.nom, lc.listeObjets, load);
			if(reussi==0){
				succes=false;
			}
			else if(reussi==1){
				succes=true;
			}
			else if(reussi==2){
				succes = false;
				loadFail++;
			}
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
				cmd.type=myFig.getType(*it);
				if(cmd.type=="OA"){//type=OA
					a=myFig.getContenuObjet(*it);
					set<string> b;
					b = myFig.getListeOA(*it);
					cmd.contenuEtType[*it].contenuPlusieursObjetsString=a;
					cmd.contenuEtType[*it].listeDesOA = b;
					cmd.contenuEtType[*it].type=cmd.type;// c'est efficace quand on differencie les OA et les objet simples
				}
				else if (cmd.type != ""){ //type != OA
					cmd.points=myFig.getPoints(cmd.type,*it);
					cmd.contenuEtType[*it].vects=cmd.points;
					cmd.contenuEtType[*it].type=cmd.type;
					a = myFig.getListeOA(*it);
					cmd.contenuEtType[*it].listeDesOA = a;
				}
			}
			succes = myFig.Supprimer(lc.listeObjets);

		}
		else if (lc.type == "CLEAR") {
			cmd.objetsCopiees=myFig.clear(false);
			cmd.numeroOperation = 4;
			succes = true;
		}
		else if (lc.type == "MOVE") {
			vector<string> objetsDeplaces;
			succes = myFig.Deplacer(lc.nom, lc.points[0], lc.points[1], objetsDeplaces);
			cmd.numeroOperation = 3;
		}
		if (cmd.numeroOperation <= 4 && cmd.numeroOperation >= 1 && load==false && succes==true){
			myFig.AjouterCommandeDansStack(cmd);// pour ajouter dans le Stack; il faut avoir lieu un changement sur l'ecran imaginaire
		}
	}
		else if (lc.error) {
			cout << "ERR" << endl;
			cout << "#Invalid arguments" << endl;
		}
	return succes;
}



int main() {
        Figure myFig;
	bool load = false;
	bool operationQuiChangeQqchSurEcran = false;
	int loadFail = 1;
        string commande;
        std::string token;
        do {
        getline(std::cin, commande);
        std::istringstream ss(commande);

        getline(ss, token, ' ');//Premier Mot

        if(token=="LOAD"){
			load = true;
			getline(ss, token, '\n');// on saisie la ligne entiere 
			if (token=="LOAD"){// si le nom de fichier n'est pas ecrit a cote de la commande LOAD 
				cout << "ERR" << endl;
				cout << "#Please enter a file name" << endl;
			}
			else{
				if (token.substr(token.length() - 4, 4) == ".txt"){// on oblige l'utilisation d'un fichier .txt
					bool ouverture;
					LectureEcriture l(token.c_str());
					ouverture = l.getOuverture();
					if (ouverture == true){
						myFig.clear(true);// quand on fait LOAD, on efface tout
						myFig.ViderStacks();
						while (loadFail > 0){
							LectureEcriture l(token.c_str());
							loadFail = 0;
							while (!l.EstFini()){ //jusqu'a la derniere ligne du fichier 
								LigneDeCommande lc;
								lc = l.ProchainLigne();
								TraiterCommande(lc, myFig, load, operationQuiChangeQqchSurEcran, loadFail);//Avec le booleen loadFail, on affiche pas "OK" pour chaque commande qui a l"effet de changement
							}
						}
						cout << "OK" << endl;
					}
				}
				else{
					cout << "ERR" << endl;
					cout << "#The end of the file name must be \".txt\"" << endl;
				}
			}
			load = false;
			loadFail = 1;
        }
		else if (token == "C" || token == "PL" || token == "L" || token == "OA" || token == "R" || token == "UNDO" || token == "REDO" || token == "MOVE" || token == "CLEAR" || token == "DELETE"){
			int a=1;
			LectureEcriture l(commande,a);
			LigneDeCommande lc;
			lc=l.ProchainLigne();
			bool succes=TraiterCommande(lc, myFig, load, operationQuiChangeQqchSurEcran, a);

			if (token != "UNDO" && token != "REDO" && succes){
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
			if (token == "SAVE"){
				cout << "ERR" << endl;
				cout << "#Please enter a file name" << endl;
			}
			else{
				if (token.substr(token.length() - 4, 4) == ".txt"){
					myFig.Sauvegarder(token);
					cout << "OK" << endl;
				}
				else{
					cout << "ERR" << endl;
					cout << "#The end of the file name must be \".txt\"" << endl;
				}
			}
		}
		else if(token=="EXIT"){
			myFig.clear(true);
		}
		else{
			cout << "ERR" << endl;
			cout << "#Invalid command" << endl;
		}
		}while(token!="EXIT");

	 return 0;

}

