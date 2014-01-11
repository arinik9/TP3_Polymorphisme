
#include "LectureEcriture.h"

LigneDeCommande LectureEcriture::ProchainLog()
{
	LigneDeCommande ligneEnCours;
	ligneEnCours.error=false;
	int compteur=0;
	unsigned int compteurPourSet=0;
	string s="",c="";
	getline(myFile,s);
	int tailleLigne=s.length();
	myFile.seekg (0, myFile.beg);
	for(int i=0;i<tailleLigne;i++){
		if(s.at(i)==' ')
			compteur+=1;
	}
	int combienMot=compteur+1;


	getline(myFile,s,' ');
	if((s=="C" && combienMot == 5)|| (s=="R" && combienMot == 6) || (s=="L" && combienMot == 6) || (s=="PL") || s=="MOVE" ){
		ligneEnCours.type=s;
		getline(myFile,ligneEnCours.nom,' ');
		for(int i=0;i<combienMot-2;i++){
			getline(myFile,c,' ');
			int value = atoi(c.c_str());
			stringstream hh;
			string h;
		    hh << c;
		    hh >> h;
			if(c.length()==h.length()) // a partir du 3eme element, verifier si c un entier ou pas
			ligneEnCours.points.push_back (value);
			else
				ligneEnCours.error=true;  break;//sortie du boucle for
		}
	}
	else if(s=="OA" || s=="DELETE"){
		ligneEnCours.type=s;
		getline(myFile,ligneEnCours.nom,' ');

		for(int i=0;i<combienMot-2;i++){
			compteurPourSet++;
			getline(myFile,c,' ');
			ligneEnCours.NomObjetUnique.insert(c);
			if(compteurPourSet != ligneEnCours.NomObjetUnique.size()) // au lieu d'utiliser la methode find(), on compare juste les tailles
				ligneEnCours.error=true;  break;
		}
	}
	else if(s=="LIST" || s=="UNDO" || s=="REDO" || s=="CLEAR" || s=="EXIT"){
		ligneEnCours.commande=s;
	}
	else if(s=="LOAD" || s=="SAVE"){
		ligneEnCours.type=s;
		getline(myFile,c,' ');
		if(c.substr(c.length()-4,4) == ".txt")
			ligneEnCours.fileName=c;
		else
			ligneEnCours.error=true;
	}
	else
		ligneEnCours.error=true;

	return ligneEnCours;
}

bool LectureEcriture:: EstFini()
{
return(myFile.eof());
}

LectureEcriture::LectureEcriture(string nomFichier):myFile(nomFichier.c_str()) {
	// TODO Auto-generated constructor stub

}

LectureEcriture::~LectureEcriture() {
	// TODO Auto-generated destructor stub
}

