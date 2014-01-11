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
	//string rayon;
	vector<int> points;
	set<string> NomObjetUnique; // MAP peut-etre?????
	string commande;
	string fileName;
	bool error;
};

class LectureEcriture {
private:
	ifstream myFile;
public:
	LigneDeCommande ProchainLog();
	LectureEcriture(string nomFichier);
	bool EstFini();
	virtual ~LectureEcriture();
};

#endif /* LECTUREECRITURE_H_ */
