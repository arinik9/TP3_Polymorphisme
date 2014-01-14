
#include "LectureEcriture.h"

LigneDeCommande LectureEcriture::ProchainLigne()
{
	LigneDeCommande ligneEnCours;
		ligneEnCours.error=false;
		int compteur=0;
		int combienMot=0;
		ligneEnCours.lengthFile=0;
		unsigned int compteurPourSet=0;
		string s="",c="",u="";

	string input="";
	if(enVeine==1)	//commandeManuel.length()==0
		input=commandeManuel; // on saisie les commandes par la console donc on utilise cela
	else
		getline(myFile,input); //on saisi les commandes par le fichier avec option LOAD

	 ligneEnCours.tailleLigne=input.length();
	 for(int i=0;i<ligneEnCours.tailleLigne;i++){
		if(input.at(i)==' ')
			compteur+=1;
	}
	 unsigned found = input.find_last_of(" ");
	 if(found!=input.length()-1)
		 combienMot=compteur+1;
	 else
		 combienMot=compteur;

	std::istringstream ss(input);
	std::string token;
	getline(ss, u, ' ');
	int PremierMotTaille=u.length();

	if((u=="C" && combienMot == 5)|| (u=="R" && combienMot == 6) || (u=="L" && combienMot == 6) || (u=="PL" && combienMot >= 4 && combienMot%2==0) || u=="MOVE" ){
		ligneEnCours.type=u;
		getline(ss, ligneEnCours.nom, ' ');
		while(getline(ss, token, ' ')) {
			long value = atol(token.c_str());
			stringstream hh;
			string h;
		    hh << value;
		    hh >> h;
			if(token.length()==h.length()){ // a partir du 3eme element, verifier si c un entier ou pas
				ligneEnCours.points.push_back (value);
			}
			else{
				ligneEnCours.error=true;  break;//sortie du boucle for
			}
		}
	}
	else if(u=="OA" || u=="DELETE"){
		ligneEnCours.type=u;
		if(u!="DELETE")
			getline(ss, ligneEnCours.nom, ' ');

		while(getline(ss, token, ' ')) {
			compteurPourSet++;

			ligneEnCours.NomObjetUnique.insert(token);
			if(compteurPourSet != ligneEnCours.NomObjetUnique.size()){ // au lieu d'utiliser la methode find(), on compare juste les tailles
				ligneEnCours.error=true;   break;
			}
		}
	}
	else if(u=="LIST" || u=="UNDO" || u=="REDO" || u=="CLEAR" || u=="EXIT"){
		ligneEnCours.type=u;
	}
	else{
		if(PremierMotTaille>0)
		ligneEnCours.error=true;
	}
	return ligneEnCours;
}

bool LectureEcriture:: EstFini()
{
return(myFile.eof());
}

LectureEcriture::LectureEcriture(string nomFichier):myFile(nomFichier.c_str()) {
	// TODO Auto-generated constructor stub

}

LectureEcriture::LectureEcriture(string command, int a):commandeManuel(command), enVeine(a){
	// TODO Auto-generated constructor stub

}

LectureEcriture::~LectureEcriture() {
	// TODO Auto-generated destructor stub
}
