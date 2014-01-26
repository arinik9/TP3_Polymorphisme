
#include "LectureEcriture.h"

LigneDeCommande LectureEcriture::ProchainLigne()
{
	LigneDeCommande ligneEnCours;
		ligneEnCours.error=false;
		int compteur=0;
		int combienMot=0;
		ligneEnCours.lengthFile=0;
		unsigned int compteurPourset=0;
		string s="",c="",u="";

	string input="";
	if (enVeine == 1){	//pas d'utilisation de file, c-a-d on saisie les commandes par la console
		input = commandeManuel; // on saisie les commandes par la console donc on utilise cela
	}
	else{
		getline(myFile, input); //on saisie les commandes par le fichier avec option LOAD
	}

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

	if((u=="C" && combienMot == 5)|| (u=="R" && combienMot == 6) || (u=="L" && combienMot == 6) || (u=="PL" && combienMot >= 6 && combienMot%2==0) || (u=="MOVE" && combienMot==4)){
		ligneEnCours.type=u;
		getline(ss, ligneEnCours.nom, ' ');
		if(verifierSeparateurDansLeNom(ligneEnCours.nom)){ //dans if, 0 = cas normal
			ligneEnCours.error=true;// par exemple OA oa#oa1 ...		
		}
			
		
		int position = 3;
		if(!ligneEnCours.error){
		while(getline(ss, token, ' ')) {// jusqu'a la fin d'une ligne
			long value = atol(token.c_str()); // de strong au type long
			if (u == "C" && position == 5 && value < 0){
				ligneEnCours.error = true; break;
			}
			stringstream hh;
			string h;
		    hh << value;
		    hh >> h;
			if(token.length()==h.length()){ //a partir du 3eme element, verifier si c'est un entier ou pas
				//if (token.length() == 1 && token != "0" && token != "1" && token != "2" && token != "3" && token != "4" && token != "5" && token != "6" && token != "7" && token != "8" && token != "9"){
				if (value == 0 && token != "0"){// l'utilisateur ne peu pas taper un caractere au lieu d'un nombre
					ligneEnCours.error = true; break;//si ile le tape donc error
				}
				else ligneEnCours.points.push_back (value);
				position++;
			}
			else{
				ligneEnCours.error=true;  break;//sortie du boucle for
			}
		}
	}
	}
	else if((u=="OA" && combienMot>1) || (u=="DELETE" && combienMot>1)){
		ligneEnCours.type=u;
		if(u!="DELETE"){
			getline(ss, ligneEnCours.nom, ' ');
			if(verifierSeparateurDansLeNom(ligneEnCours.nom)){ //dans if, 0 = cas normal
				ligneEnCours.error=true;
			}
	
				
			
		}
if(!ligneEnCours.error){
		while(getline(ss, token, ' ')) {
			compteurPourset++;

			ligneEnCours.listeObjets.insert(token);
			if(compteurPourset != ligneEnCours.listeObjets.size()){ // au lieu d'utiliser la methode find(), on compare juste les tailles
				ligneEnCours.error=true;   break;
			}
		}
	}
	}
	else if(u=="LIST" || u=="UNDO" || u=="REDO" || u=="CLEAR" || u=="EXIT"){
		ligneEnCours.type=u;
	}
	else{
		if (PremierMotTaille > 0)
		ligneEnCours.error=true;
	}
	return ligneEnCours;
}

bool LectureEcriture:: EstFini()
{
return(myFile.eof());
}

LectureEcriture::LectureEcriture(string nomFichier){
	// TODO Auto-generated constructor stub
	enVeine=0;
	myFile.open(nomFichier.c_str());
	if (myFile.fail() == true){
		ouverture = false;
		cout << "ERR" << endl;
		cout << "#The file does not exist" << endl;
	}
	else ouverture = true;

}

bool LectureEcriture::getOuverture(){
	return ouverture;
}

bool LectureEcriture::verifierSeparateurDansLeNom(string nom){
	bool error=false;
	int i=0,a;
	 char c;
	 while (nom.c_str()[i])
	   {
	     c=nom.c_str()[i];
	     a=toupper(c);
	     ((a>64 && a<91) || (a>47 && a<58)) ?  error=false : error=true;
		if(error == 1)
	    	    break;
	     i++;
	   }
return error;
}

LectureEcriture::LectureEcriture(string command, int a):commandeManuel(command), enVeine(a){
	// TODO Auto-generated constructor stub
ouverture=false;
}

LectureEcriture::~LectureEcriture() {
	// TODO Auto-generated destructor stub
}

