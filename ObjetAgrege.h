#ifndef OBJETAGREGE_H_
#define OBJETAGREGE_H_

#include <string>
#include <map>
#include <set>
#include "ElementGeo.h"
using namespace std;

class ObjetAgrege:public ElementGeo
{
private :
	map<string, ElementGeo*> contenu;
public:
	ObjetAgrege(string nom) :ElementGeo(nom, "OA"){};
	~ObjetAgrege();
	void AjouterDansOA(string nomElement, ElementGeo* elementAjoute);
	void EnleverDansOA(string nomElement);
	void RetirerDesObjets();
	void Afficher();
	void Deplacer(long x, long y, vector<string>& objetsDeplaces);
	void Sauvegarder(ofstream& f);
    set<string> getObjetsGeo();
};

#endif /* OBJETAGREGE_H_ */
