#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>
#include<sstream>
#ifndef LECTUREECRITURE_H_
#define LECTUREECRITURE_H_

using namespace std;

struct LigneDeCommande
{
	string nom;
	string type;
	string rayon;
	vector<long> points;
	set<string> listeObjets; // MAP peut-etre?????
	string fileName;
	int tailleLigne;
	int lengthFile;
	bool error;
};

class LectureEcriture {
private:
	ifstream myFile;
	string commandeManuel;
	int enVeine;
	bool ouverture;
public:
	bool getOuverture();
	LigneDeCommande ProchainLigne();
	LectureEcriture(string nomFichier);
	LectureEcriture(string command,int a);
	bool EstFini();
	bool verifierSeparateurDansLeNom(string nom);
	virtual ~LectureEcriture();
};

#endif /* LECTUREECRITURE_H_ */
