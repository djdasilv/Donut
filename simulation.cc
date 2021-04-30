// simulation.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include <sstream>
#include <fstream>
#include "base.h"
#include "constantes.h"
#include "message.h"

using namespace std;

namespace{
	enum Etat_lecture {	NB_GISEMENT,GISEMENTS,NB_BASE,BASE,DEF,
						ROBOTP,ROBOTF,ROBOTT,ROBOTC,FIN};
	
	
	static vector < Base > liste_base;
	static vector < Gisement > liste_gisement; 
	
};

void lecture(char* nom)
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
		
        }
    //Verification que toutes les bases ont un robot de comm au centre
    for (size_t i(0); i<liste_base.size(); i++){
		liste_base[i].robot_comm(liste_base);
	}
}

//Fonction qui definit l'etat du switch de l'automate de lecture
void set_etat (	int& etat, double nbP, double nbF, double nbT, double nbC, 
				double bases){
	switch(etat){
		case BASE:
			if (nbP>0) etat = ROBOTP;
			else if (nbF>0) etat = ROBOTF;
			else if (nbT>0) etat = ROBOTT;
			else if (nbC>0)etat = ROBOTC;
			else etat= BASE;
			break;
					
		case ROBOTP:
			if (nbF>0) etat = ROBOTF;
			else if (nbT>0) etat = ROBOTT;
			else if (nbC>0)etat = ROBOTC;
			else etat = BASE;
			break;
					
		
		case ROBOTT:
			if (nbC>0)etat = ROBOTC;
			else etat = BASE;
			break;
	
		case ROBOTF:
			if (nbT>0) etat = ROBOTT;
			else if (nbC>0)etat = ROBOTC;
			else etat = BASE;
			break;
		
		case ROBOTC:
			etat = BASE;
			break;
	}
}

//Automate de lecture pour les gisement
void decodage_ligne1(string line){
	
	istringstream data(line);
	static int etat(NB_GISEMENT),nombre(0), g(0);	
	static double x, y ,rayon ,ressource;
	

	switch(etat) {
		case NB_GISEMENT:
			data >> nombre;
			etat=GISEMENTS;
			if (nombre == 0) etat=DEF;
			break;
			
		case GISEMENTS:
			data>>x>>y>>rayon>>ressource;
			if (g<nombre)	g++;
			Gisement (x,y,rayon, ressource).ajout_gisement(liste_gisement);
			if (g==nombre) etat=DEF;
			break;
			
		case DEF:
			decodage_ligne2(line);
			break;
	}
}

//Automate de lecture pour les bases et les robots
void decodage_ligne2(string line){		
	
	istringstream data(line);
	static double x ,y ,ressource,nbP , nbT, nbC, nbF, dp, uid, xb, yb,
				base(0),nb_robots(0), xg,yg,rayong,capaciteg,nombre;			
	static string atteint,retour,found;
	static int etat(NB_BASE);
		
	switch (etat){
		case NB_BASE:
			data >> nombre;
			etat= BASE;
			break;
		case BASE:
			if (base <=nombre){
				data>>x>>y>>ressource>>nbP>>nbF>>nbT>>nbC;
				Base (x,y,ressource,nbP,nbF, nbT,nbC).ajout_base(	liste_base, 
																	liste_gisement);
				if (nbC == 0) {
					cout<<message::missing_robot_communication(	liste_base[base].
																get_x(),
																liste_base[base].
																get_y());
					exit(EXIT_FAILURE);
				}
				set_etat(etat, nbP, nbF, nbT, nbC,base);
				nb_robots=0;
				++base;
				} 
			else break;
			break;
			
		case ROBOTP:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>retour>>found;
			if (found =="false") { 
				liste_base[base-1].ajout_robot(new Prospecteur(uid,dp,x,y,xb,yb,
															atteint,retour, found));}		
			else { 
				data>>xg>>yg>>rayong>>capaciteg;
				liste_base[base-1].ajout_robot(new Prospecteur(uid,dp,x,y,xb,yb,atteint,
															retour,found,xg,yg,rayong,
															capaciteg));}
			if (nb_robots+1==nbP) {
				set_etat(etat, nbP, nbF, nbT, nbC,base);			
				nb_robots=0;
				break;} 
			nb_robots++;
			break;
			
		case ROBOTF:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
			liste_base[base-1].ajout_robot(new Forage(uid, dp,x,y,xb,yb,atteint));
			if (nb_robots+1==nbF) {
				nb_robots=0;
				set_etat(etat, nbP, nbF, nbT, nbC,base);
				break;}
			else nb_robots++;
			break;
	
		case ROBOTT:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>retour;	
			liste_base[base-1].ajout_robot(new Transport(uid,dp,x,y,xb,yb,atteint,retour));
			if (nb_robots+1==nbT) {
				nb_robots=0;
				set_etat(etat, nbP, nbF, nbT, nbC,base);			
				break;}
			 else  nb_robots++;
			break;
			
		case ROBOTC:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
			liste_base[base-1].ajout_robot(new Communication(uid,dp,x,y,xb,yb,atteint));
			if (nb_robots+1==nbC) {
				set_etat(etat, nbP, nbF, nbT, nbC,base);
				nb_robots=0;				
				break;}
			else nb_robots++;
			break;
	}
}
