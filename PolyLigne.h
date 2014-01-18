/*
 * PolyLigne.h
 *
 *  Created on: 07 Oca 2014
 *      Author: nejat
 */

#ifndef POLYLIGNE_H_
#define POLYLIGNE_H_

#include <vector>
#include <string>
#include "Ligne.h"
using namespace std;

class PolyLigne : public Ligne{
public:
	PolyLigne(string nom1, vector<long> points) :Ligne("PL",nom1, points[0], points[1], points[2], points[3]), autresPoints(points){};
	//PolyLigne(string nom1, vector<long> points) :nom(nom1)
	virtual ~PolyLigne();
	void Afficher();
	void Deplacer(long x,long y,vector<string> objetsDeplaces);
	vector<long> GetPoints();
	void Sauvegarder(ofstream& f);
protected:
	vector<long> autresPoints;
};

#endif /* POLYLIGNE_H_ */
