/*
 * ObjetAgrege.cpp
 *
 *  Created on: 14 Oca 2014
 *      Author: nejat
 */
#include <algorithm>

#include "ObjetAgrege.h"
/*
ObjetAgrege::ObjetAgrege() {
	// TODO Auto-generated constructor stub

}
*/

void ObjetAgrege::Deplacer(long x, long y, vector<string> objetsDeplaces){
	map<string, ElementGeo*>::iterator itMap;
	for (itMap = contenu.begin(); itMap != contenu.end(); itMap++){
		if (find(objetsDeplaces.begin(), objetsDeplaces.end(), itMap->first) == objetsDeplaces.end()){
			itMap->second->Deplacer(x, y, objetsDeplaces);//recursif
			objetsDeplaces.push_back(itMap->first);
		}
	}
}

ObjetAgrege::~ObjetAgrege() {
	// TODO Auto-generated destructor stub
}
