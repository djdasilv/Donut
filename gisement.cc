#include <iostream>
#include <vector>
#include <cmath>
#include "constantes.h"
#include "message.h"
#include "gisement.h"


void ajout_gisement ( Gisement* A , std::vector< Gisement* > &liste) 
{
	bool presence (false);
	int tmp(0);
	for ( size_t i (0); i < liste.size() ; i++ ){
	 if (intersection_deux_cercles ( A -> getCercleG() , liste[i] -> getCercleG()))  {

				presence = true; 
				tmp= static_cast<int>(i);
			}	
	}
	if ( presence == false) {
		
		liste.push_back( A );
		
	
	} else {
		std::cout<<message::field_superposition(A -> getCercleG().get_x(), A -> getCercleG().get_y(),liste[tmp] -> getCercleG().get_x(),liste[tmp] -> getCercleG().get_y());
		exit ( EXIT_FAILURE ) ;
	} 
	
};

Gisement :: Gisement( double x , double y , double r , double qt)
{
	taille_ressources.set_centre( x , y );
	taille_ressources.set_rayon ( r ) ;
	set_qt_ressources(qt) ;


};

Gisement:: ~Gisement(){}	

void Gisement :: set_qt_ressources (double& qt_r)
{
	quantitee_ressources = qt_r * pow((rayon_max/rayon_min),2); 
};

double Gisement :: get_qt_ressources () const 
{
	return quantitee_ressources;
};


Cercle Gisement:: getCercleG () const 
{ 
	return taille_ressources;
};


double Gisement::get_x(){
	return getCercleG().get_centre().get_x();
	}
	
double Gisement::get_y(){
	return getCercleG().get_centre().get_y();
	}
	
	
double Gisement::get_rayon() {
	
	return taille_ressources.get_rayon();

}	
/**vector <Cercle> getPositionsBases ( )
{ 
	vector <Cercle> PG ;
	for ( size_t i (0) ; i < liste_gisement.size() ; ++i)
	{ 
		PG.push_back(liste_gisement[i].getCercleG());
	}
	return PG;
}
***/
