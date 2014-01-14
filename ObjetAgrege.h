
#ifndef OBJETAGREGE_H_
#define OBJETAGREGE_H_

#include <string>
#include <map>
#include "ElementGeo.h"
using namespace std;

class ObjetAgrege :public ElementGeo
{
private :
	map<string, ElementGeo*> elements;
	string nom;
public:
	ObjetAgrege(string nom1):nom(nom1){}
	~ObjetAgrege();
	//bool AjouterDansOA(ElementGeo* ajout);
};

#endif /* OBJETAGREGE_H_ */
