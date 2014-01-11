
#include "Figure.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

int main() {

	string commande;
	vector<long> vect;
	cout << "C:  ";
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



	 /*Figure myfigure;
	 myfigure.ajouter(typ, nom,vect);
	 vect.clear();
	 //void figure::ajouter(string typeElement,string nom,const vector<long>& vec){*/
	 return 0;

	// test imprimer le vector

}

