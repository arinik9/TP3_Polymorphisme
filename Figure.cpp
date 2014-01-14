
#include "Figure.h"
#include "Cercle.h"
#include "Rectangle.h"
#include "Ligne.h"
#include "PolyLigne.h"
#include <list>
#include <set>
#include <vector>
#include "string"
#include "ElementGeo.h"

using namespace std;


void Figure::Ajouter(string type, string nomObjet, vector<long> points){
	map<string,ElementGeo*>::iterator it;
	vector<long>::iterator itVec;
	//vector<string> vide;
	if (elements.find(nomObjet) == elements.end()) { // C'EST PAS LA PEINE PEUT-ETRE!!!
		if (type == "C"){
			ElementGeo* cercle = new Cercle(nomObjet, points[0], points[1], points[2]);
			elements[nomObjet] = cercle;
		}
		else if (type == "R"){
			ElementGeo* rectangle = new Rectangle(nomObjet, points[0], points[1], points[2], points[3]);
			elements[nomObjet] = rectangle;
		}
		else if (type == "L"){
			ElementGeo* ligne = new Ligne(nomObjet, points[0], points[1], points[2], points[3]);
			elements[nomObjet] = ligne;
		}
		else if (type == "PL"){
			ElementGeo* polyligne = new PolyLigne(nomObjet, points);
			elements[nomObjet] = polyligne;
		}
	}
		//http://www.dreamincode.net/forums/topic/160765-trouble-with-mapvectorstring-int/
		//elements[nomObjet].objetAgr = vide; //Liste des éléments contenus par l'OA
		//stockage[nomObjet].points = points; //Liste des points qui constituent l'élément
		//stockage[nomObjet].elementObjAgr=vide; //Liste des OA dans lequel l'élément est contenu
}

//void Figure::Ajouter(string nomObjet, set<string> QuelobjetAgraget){
//	set<string>::iterator iter;
//	map<string,Parametres>::iterator it;
//	vector<string>::iterator itVec;
//
//	for(iter=QuelobjetAgraget.begin();iter!=QuelobjetAgraget.end();iter++){
//		stockage[nomObjet].elementObjAgr.push_back(*iter);
//	}
//
//	for(iter=QuelobjetAgraget.begin();iter!=QuelobjetAgraget.end();iter++){
//		if(stockage.find(*iter) != stockage.end()) // on ajoute aussi du type OA
//				stockage[*iter].objetAgr.push_back(nomObjet);
//	}
//
//
//}



//void Figure::Ajouter(string typeElement,string nom, vector<long> vec){
//
//	if(typeElement == "C"){
//
//		if(vec.size() != 3){
//			cout << "invalid parameters" << endl;
//		}
//		else{
//		long x = vec[0];
//		long y = vec[1];
//		long rayon = vec[2];
//		ElementGeo* temp = new Cercle(nom,x,y,rayon);
//		elements.push_back(temp);
//		cout << "New object :" << nom << endl;
//		}
//	}
//
//}

void Figure::Afficher(){

	map<string,ElementGeo*>::iterator it;

	for (it = elements.begin(); it != elements.end(); it++){
		it->second->Afficher();
	}
}

	Figure::Figure(){
		// TODO Auto-generated constructor stub
	}

	Figure::~Figure() {
			// TODO Auto-generated destructor stub
	}
