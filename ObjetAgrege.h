
#ifndef OBJETAGREGE_H_
#define OBJETAGREGE_H_

#include <string>
#include <map>
#include "ElementGeo.h"
using namespace std;

class ObjetAgrege :public ElementGeo
{
private :
	map<string, ElementGeo*> contenu;
public:
	ObjetAgrege(string nom):ElementGeo(nom,"OA"){};
	void Deplacer(long x, long y, vector<string> objetsDeplaces);
	~ObjetAgrege();
	//bool AjouterDansOA(ElementGeo* ajout);
};

#endif /* OBJETAGREGE_H_ */
