// simulation.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include <sstream>
#include <fstream>
#include "simulation.h"

using namespace std;

namespace{
	enum Etat_lecture {	NB_GISEMENT,GISEMENTS,NB_BASE,BASE,DEF,
						ROBOTP,ROBOTF,ROBOTT,ROBOTC,FIN};
	
	static int count(0);
	static int etat1(NB_GISEMENT), etat2(NB_BASE);
	static vector < Gisement* > liste_gisement; 
	static vector < Base* > liste_base;
	
};

Simulation::Simulation(){}

Simulation::~Simulation(){}

void Simulation::lecture(char* nom)
{
	set_max(dim_max);
    string line;
    ifstream fichier(nom); 
    if(fichier.fail()) exit(EXIT_FAILURE);
   
	while(getline(fichier >> ws,line)) 
       {
		// ligne de commentaire à ignorer, on passe à la suivante
		if(line[0]=='#')  continue; 
		decodage_ligne1(line);
		//cout<<base_size()<<endl;
        }
    //Verification que toutes les bases ont un robot de comm au centre
    for (size_t i(0); i<liste_base.size(); i++){
		liste_base[i] -> robot_comm(liste_base);
		
		cout<<"Nb de robots: "<<liste_base[0]->get_nb_robot()<<endl;
	
	for( size_t i (0); i<liste_gisement.size(); i++){
		cout<<get_gisement(i)->get_rayon()<<endl;
	}
	//Remises des etats a leur valeur initiales afin de permettre 
	//la lecture d'un deuxieme fichier
	etat1= NB_GISEMENT;
	etat2= NB_BASE;
	
	}
}

//Fonction qui definit l'etat du switch de l'automate de lecture
void Simulation::set_etat (	int& etat2, double nbP, double nbF, double nbT, double nbC, 
				double bases){
	switch(etat2){
		case BASE:
			if (nbP>0) etat2 = ROBOTP;
			else if (nbF>0) etat2 = ROBOTF;
			else if (nbT>0) etat2 = ROBOTT;
			else if (nbC>0)etat2 = ROBOTC;
			else etat2= BASE;
			break;
					
		case ROBOTP:
			if (nbF>0) etat2 = ROBOTF;
			else if (nbT>0) etat2 = ROBOTT;
			else if (nbC>0)etat2 = ROBOTC;
			else etat2 = BASE;
			break;
					
		
		case ROBOTT:
			if (nbC>0)etat2 = ROBOTC;
			else etat2 = BASE;
			break;
	
		case ROBOTF:
			if (nbT>0) etat2 = ROBOTT;
			else if (nbC>0)etat2 = ROBOTC;
			else etat2 = BASE;
			break;
		
		case ROBOTC:
			etat2 = BASE;
			break;
	}
}

//Automate de lecture pour les gisement
void Simulation::decodage_ligne1(string line){
	++count;
	istringstream data(line);
	static int nombre(0), g(0);	
	static double x(0), y(0) ,rayon(0) ,ressource(0);
	switch(etat1) {
		case NB_GISEMENT:
			data >> nombre;
			etat1=GISEMENTS;
			if (nombre == 0) etat1=DEF;
			break;
			
		case GISEMENTS:
			data>>x>>y>>rayon>>ressource;
			cout << x <<" "<< y <<endl;
			if (g<nombre) g++;
			ajout_gisement(new Gisement (x,y,rayon, ressource), liste_gisement);
			if (g==nombre) etat1=DEF;
			break;
			
		case DEF:
			//cout<<"Coucou"<<endl;
			g=0;
			nombre=0;
			decodage_ligne2(line);
			break;
	}
}

//Automate de lecture pour les bases et les robots
void Simulation::decodage_ligne2(string line){		
	
	istringstream data(line);
	static double x(0) ,y(0) ,ressource(0),nbP(0) , nbT(0), nbC(0), nbF(0), dp(0), uid(0), xb(0), yb(0),
				base(0),nb_robots(0), xg(0),yg(0),rayong(0),capaciteg(0),nombre(0);			
	static string atteint,retour,found;
	
		
	switch (etat2){
		case NB_BASE:
			data >> nombre;
			etat2= BASE;
			//cout<<"Nb base:"<<nombre<<endl;
			break;
		case BASE:
			if (base <=nombre){
				data>>x>>y>>ressource>>nbP>>nbF>>nbT>>nbC;
				cout << x << " "<< y<< " "<< ressource<< " "<<nbP<<" "<<nbF<<" "<<nbT<<" "<< nbC<<endl; 
				ajout_base( new Base (x,y,ressource,nbP,nbF, nbT,nbC) , liste_base , liste_gisement);
				if (nbC == 0) {
					cout<<message::missing_robot_communication(	liste_base[base] -> get_x(),
																liste_base[base] -> get_y());
					exit(EXIT_FAILURE);
				}
				set_etat(etat2, nbP, nbF, nbT, nbC,base);
				nb_robots=0;
				++base;
				} 
			else break;
			break;
			
		case ROBOTP:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>retour>>found;
			
			cout<<uid<<" "<<dp<<"  "<<x<<" "<<y<<"  "<<xb<<"  "<<yb<<endl;
			if (found =="false") { 
				liste_base[base-1] -> ajout_robot(new Prospecteur(uid,dp,x,y,xb,yb,
															atteint,retour, found));}		
			else { 
				data>>xg>>yg>>rayong>>capaciteg;
				liste_base[base-1] -> ajout_robot(new Prospecteur(uid,dp,x,y,xb,yb,atteint,
															retour,found,xg,yg,rayong,
															capaciteg));}
			if (nb_robots+1==nbP) {
				set_etat(etat2, nbP, nbF, nbT, nbC,base);			
				nb_robots=0;
				break;} 
			nb_robots++;
			break;
			
		case ROBOTF:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
			cout<<uid<<" "<<dp<<"  "<<x<<" "<<y<<"  "<<xb<<"  "<<yb<<endl;
			liste_base[base-1] -> ajout_robot(new Forage(uid, dp,x,y,xb,yb,atteint));
			if (nb_robots+1==nbF) {
				nb_robots=0;
				set_etat(etat2, nbP, nbF, nbT, nbC,base);
				break;}
			else nb_robots++;
			break;
	
		case ROBOTT:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>retour;
			cout<<uid<<" "<<dp<<"  "<<x<<" "<<y<<"  "<<xb<<"  "<<yb<<endl;
			liste_base[base-1] -> ajout_robot(new Transport(uid,dp,x,y,xb,yb,atteint,retour));
			if (nb_robots+1==nbT) {
				nb_robots=0;
				set_etat(etat2, nbP, nbF, nbT, nbC,base);			
				break;}
			 else  nb_robots++;
			break;
			
		case ROBOTC:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
			cout<<uid<<" "<<dp<<"  "<<x<<" "<<y<<""<<xb<<"  "<<yb<<endl;
			liste_base[base-1] -> ajout_robot(new Communication(uid,dp,x,y,xb,yb,atteint));
			if (nb_robots+1==nbC) {
				set_etat(etat2, nbP, nbF, nbT, nbC,base);
				nb_robots=0;
				base=0;				
				break;}
			else nb_robots++;
			break;
	}		
	
}
/**
void effacer(){
		for (auto gisement : liste_gisement) delete gisement;
		liste_gisement.clear();
		
		for (auto base : liste_base) delete base;
		liste_base.clear();
		count=0;
}**/

Gisement* Simulation::get_gisement(int i){
	return liste_gisement[i];
}

Base* Simulation::get_base(int i){
	return liste_base[i];
}

size_t Simulation::gisement_size(){
	return liste_gisement.size();
}

size_t Simulation::base_size(){
	return liste_base.size();
}



void TabRobotsConnectBases()
{
	for ( size_t a(0) ; a < liste_base.size() ; a++) 
		{
			for ( size_t b(0) ; b < liste_base[a]->robots_base.size(); b++) 
			{
				if(liste_base[a] -> robots_base[b]-> get_comm_Base() ) 
				{
					rec_DEF(liste_base[a] , liste_base[a] -> robots_base[b]);
				}
			} 
		}
}
