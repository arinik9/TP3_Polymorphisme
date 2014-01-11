/*
 * figure.h
 *
 *  Created on: 7 janv. 2014
 *      Author: narinik
 */

#ifndef FIGURE_H_
#define FIGURE_H_


#include <iostream>
#include <list>
#include "string"
#include <vector>
#include "ElementGeo.h"


//using namespace std;

class Figure {

public:
	std::list<ElementGeo*> elements;
	Figure();

	void ajouter(std::string typeElement,std::string nom, vector<long> vec);
	virtual ~Figure();
};




#endif /* FIGURE_H_ */
