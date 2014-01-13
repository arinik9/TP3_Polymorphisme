
#include "Figure.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "LectureEcriture.h"

using namespace std;

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
					if(!lc.error){
						if(lc.type=="PL" || lc.type=="C" || lc.type=="R"){
							//cout  << "OK "<< lc.nom;//std::cout << ' ' << *it;
							//for (std::vector<long>::iterator it = lc.points.begin(); it != lc.points.end(); ++it)
								myFig.Ajouter(lc.nom,lc.points);
							//cout <<endl;
						}
						if(lc.type=="OA"){
							//cout << "OK " << lc.nom;// std::cout << ' ' << *it;
							//for (std::set<string>::iterator it=lc.NomObjetUnique.begin(); it!=lc.NomObjetUnique.end(); ++it)
								myFig.Ajouter(lc.nom,lc.NomObjetUnique);
							//cout << endl;
						}
						if(lc.type=="LIST" || lc.type=="UNDO" || lc.type=="REDO" || lc.type=="CLEAR" || lc.type=="EXIT"){
							cout  << "OKi "<< lc.type << endl;
						}
					}
					else if(lc.error)
						cout <<"ERR" << endl;
				}



		}
	}
	else{
		getline(ss, token, '\n');
		cout << "OK " << token << endl;
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

