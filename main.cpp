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
			succes = myFig.AjouterOA(lc.nom, lc.listeObjets, load);
			if (succes== false){
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
				if(cmd.type=="OA"){
					a=myFig.getContenuObjet(*it);
					set<string> b;
					b = myFig.getListeOA(*it);
					cmd.contenuEtType[*it].contenuPlusieursObjetsString=a;
					cmd.contenuEtType[*it].listeDesOA = b;
					cmd.contenuEtType[*it].type=cmd.type;
				}
				else if (cmd.type != ""){
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
			cmd.objetsCopiees=myFig.clear();
			cmd.numeroOperation = 4;
			succes = true;
		}
		else if (lc.type == "MOVE") {
			vector<string> objetsDeplaces;
			succes = myFig.Deplacer(lc.nom, lc.points[0], lc.points[1], objetsDeplaces);
			cmd.numeroOperation = 3;
		}
		if (cmd.numeroOperation <= 4 && cmd.numeroOperation >= 1 && load==false && succes==true){
			myFig.AjouterCommandeDansStack(cmd);
		}

	}
		else if (lc.error) {
			cout << "ERR" << endl << "#Invalid arguments" << endl;
			return false;
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
			//int compte = 0;
			getline(ss, token, '\n');
			if (token=="LOAD"){
				cout << "ERR" << endl << "#Please enter a file name" << endl;
			}
			else{
				if (token.substr(token.length() - 4, 4) == ".txt"){
					bool ouverture;
					while (loadFail > 0){
						LectureEcriture l(token.c_str());//"/home/nejat/Masaüstü/toto.txt"
						loadFail = 0;
						ouverture = l.getOuverture();
						if (ouverture == true){
							myFig.clear();
							myFig.ViderStacks();
							while (!l.EstFini()){
								LigneDeCommande lc;
								lc = l.ProchainLigne();
								TraiterCommande(lc, myFig, load, operationQuiChangeQqchSurEcran, loadFail);
							}
						}
					}
					if (ouverture) cout << "OK" << endl;
				}
				else{
					cout << "ERR" << endl << "#The end of the file name must be \".txt\"" << endl;
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
				cout << "ERR" << endl << "#Please enter a file name" << endl;
			}
			else{
				if (token.substr(token.length() - 4, 4) == ".txt"){
					myFig.Sauvegarder(token);
					cout << "OK" << endl;
				}
				else
					cout << "ERR" << endl << "#The end of the file name must be \".txt\"" << endl;
			}
		}
		else{
			cout << "ERR" << endl << "#Invalid command" << endl;
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
