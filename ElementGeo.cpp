/*
 * ElementGeo.cpp
 *
 *  Created on: 17 déc. 2013
 *      Author: narinik
 */
#include<iostream>
#include "ElementGeo.h"


ElementGeo::~ElementGeo() {
	// TODO Auto-generated destructor stub
}

void ElementGeo::Deplacer(long x, long y, vector<string> objetsDeplaces){}

 void ElementGeo::Sauvegarder(ofstream& f){

  }

 void ElementGeo::Afficher(){}

 vector<long> ElementGeo::GetPoints(){
		std::cout<< "ELEMENT GEO" << endl;
	 vector<long> a;
	 return a;
 }

 string ElementGeo::GetType(){
	 return type;
 }
