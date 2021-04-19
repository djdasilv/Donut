// simulation.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include "simulation.h"
#include "gisement.h"
#include "robot.h"
#include "base.h"
#include "constantes.h"
#include <sstream>
#include <fstream>
using namespace std;

namespace{
	enum Etat_lecture {	NB_GISEMENT,GISEMENTS,NB_BASE,BASE,
						ROBOTP,ROBOTF,ROBOTT,ROBOTC,FIN};
	
	
	static std::vector < Base > liste_base;
	static std::vector < Gisement > liste_gisement; };

void lecture(char* nom)
{
	set_max(dim_max);
    string line;
    ifstream fichier(nom); 
    if(fichier.fail()) exit(EXIT_FAILURE);
    
	// l’appel de getline filtre aussi les séparateurs
	while(getline(fichier >> ws,line)) 
       {
		// ligne de commentaire à ignorer, on passe à la suivante
		if(line[0]=='#')  continue; 
		decodage_ligne(line);
		
        }
	}

void set_etat (int& etat, double nbP, double nbF, double nbT, double nbC){
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



void decodage_ligne(string line)
{
	istringstream data(line);
	static int etat(NB_GISEMENT),nombre(0),g(0);	 // état initial
	static double x, y ,rayon ,ressource, nbP,nbT,nbC,nbF,dp, uid,xb,yb,
					bases(0),nb_robots(0), xg,yg,rayong,capaciteg;
	static string atteint,retour,found;

	switch(etat) {
		case NB_GISEMENT:{
			data >> nombre;
			etat=GISEMENTS;
			if (nombre == 0) etat= NB_BASE;
			break;}
			
		case GISEMENTS:{
			data>>x>>y>>rayon>>ressource;
			if (g<nombre)	g++;
			Gisement (x,y,rayon, ressource).ajout_gisement(liste_gisement);
			if (g==nombre) etat=NB_BASE;
			break;}
			
		case NB_BASE:{
			data >> nombre;
			etat= BASE;
			break;}
			
		case BASE:{
			if (bases <=nombre){
				data>>x>>y>>ressource>>nbP>>nbF>>nbT>>nbC;
				Base (x,y,ressource,nbP,nbF, nbT,nbC).ajout_base(liste_base, liste_gisement);
				set_etat(etat, nbP, nbF, nbT, nbC);
				nb_robots=0;
				++bases;
				
			
			} else etat = FIN;
			break;}
			
		case ROBOTP:{
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>found;
			if (found=="false")	Prospecteur(uid,dp,x,y,xb,yb,atteint,retour,found);
			else { 
				data>>xg>>yg>>rayong>>capaciteg;
				Prospecteur(uid,dp,x,y,xb,yb,atteint,retour,found,xg,yg,rayong,capaciteg);
			};
			if (nb_robots+1==nbP) {
				set_etat(etat, nbP, nbF, nbT, nbC);			
				nb_robots=0;
				break;} 
			nb_robots++;
			break;}
			
		case ROBOTF:{
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
	//		cout<<"ROBOTF ----- uid: "<<uid<<" dp: "<<dp<<" x: "<<x<<" y: "<<y<<" xb: "<<xb<<" yb: "<<yb<<" atteint: "<<atteint<<endl; 
			//Forage(uid, dp,x,y,xb,yb,atteint);
			if (nb_robots+1==nbF) {
				nb_robots=0;
				set_etat(etat, nbP, nbF, nbT, nbC);
				break;}
			else nb_robots++;
			break;}
	
		case ROBOTT:{
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>retour;	
		//	cout<<"ROBOTT ----- uid: "<<uid<<" dp: "<<dp<<" x: "<<x<<" y: "<<y<<" xb: "<<xb<<" yb: "<<yb<<" atteint: "<<atteint<<" retour: "<<retour<<endl;
			//Transport(uid,dp,x,y,xb,yb,atteint,retour);
			if (nb_robots+1==nbT) {
				nb_robots=0;
				set_etat(etat, nbP, nbF, nbT, nbC);			
				break;}
			 else  nb_robots++;
			break;}
			
		case ROBOTC:{	
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
			//cout<<"ROBOTC ----- uid: "<<uid<<" dp: "<<dp<<" x: "<<x<<" y: "<<y<<" xb: "<<xb<<" yb: "<<yb<<" atteint: "<<atteint<<endl;
			//Communication(uid,dp,x,y,xb,yb,atteint);
			if (nb_robots+1==nbC) {
				set_etat(etat, nbP, nbF, nbT, nbC);
				nb_robots=0;				
				break;}
			else nb_robots++;
			break;}
			
		case FIN:{}
	}
}


/***
bool IntersectionBaseGisement ( vector <Cercle> Pg, vector <Cercle> Pb ) 
{
	bool present(false) ;
		for ( size_t i (0) ; i < Pg.size() ; ++i) 
		{
			for ( size_t j (0) ; j < Pb.size() ; ++j) 
			{ 
			//Erreur	if (intersection_deux_cercles ( Pg[i] , Pb[j] ) )
				{
					present = true; 
				}
			}
		}
		
		if ( present == false ) 
		{
			return false;
		}
		return true; 
}
***/




/***void simulation(vector<int> bases){
	for (size_t i = 0; i < bases.size(); i++){  //Warning pour int i < que bases.size()
		for(size_t j(0) ; j < bases.size(); j++){
			update_voisin();
		}
		connexion(bases[i]);
		maintenance(bases[i]);
		creation(bases[i]);
		update_remote();
		update_autonomous();
	}
		
	for (size_t i = 0; i < bases.size(); i++){
		if(bases[i] <= 0 ){
			destruction(bases[i]);
		}
	}
}
***/
