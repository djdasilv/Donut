#include <iostream>
#include <vector>
#include <cmath>
#include "message.h"
#include "gisement.h"

double Gisement::get_rayon() {
	
	return taille_ressources.get_rayon();

}		

Gisement :: Gisement( double x , double y , double r , double qt)
{
	taille_ressources.set_centre( x , y );
	taille_ressources.set_rayon ( r ) ;
	set_qt_ressources(qt) ;


};	

void Gisement :: set_qt_ressources (double& qt_r)
{
	quantitee_ressources = qt_r ; 
};

double Gisement :: get_qt_resources () const 
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
