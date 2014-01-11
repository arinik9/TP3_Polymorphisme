/*
 * figure.cpp
 *
 *  Created on: 7 janv. 2014
 *      Author: narinik
 */

#include "Figure.h"
#include "Cercle.h"
#include <list>
#include "string"
#include "ElementGeo.h"

using namespace std;

Figure::~Figure() {
		// TODO Auto-generated destructor stub
	}

Figure::Figure() {
	// TODO Auto-generated constructor stub

}


void Figure::ajouter(string typeElement,string nom, vector<long> vec){

	if(typeElement == "C"){

		if(vec.size() != 3){
			cout << "invalid parameters" << endl;
		}
		else{
		long x = vec[0];
		long y = vec[1];
		long rayon = vec[2];
		ElementGeo* temp = new Cercle(nom,x,y,rayon);
		elements.push_back(temp);
		cout << "New object :" << nom << endl;
		}
	}






}
