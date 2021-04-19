#include <iostream>
#include <array>
#include <cmath>
#include <vector>
#include "geomod.h"
#include "base.h"
#include "message.h"
#include "constantes.h"


Cercle Base::getCercle () const 
{ 
	return position;
}
/***
std::vector <Cercle> getPositionsBases ( )
{ 
	std::vector <Cercle> PB ;
	for ( size_t i (0) ; i < liste_base.size() ; ++i)
	{ 
		PB.push_back(liste_base[i].getCercle());
	}
	return PB;
}
***/
Base :: Base ( double x , double y ,  double r , int  P, int F , int T , int C )
{ 
	nbP =P; 
	nbF =F;
	nbT =T;
	nbC =C;
	position.set_centre (x, y);
	position.set_rayon(rayon_base);
	set_ressources (r); 
	
}

double Base::get_x(){
	return getCercle().get_centre().get_x();
	}
double Base::get_y(){
	return getCercle().get_centre().get_y();
}


double Base :: get_ressources () const
{
	return ressources; 
}

void Base :: set_ressources( double& ener )
{
	ressources = ener; 
}
/***
void Base :: ajout_robot (robot::Robot A)
{
	robot::Robot* a; 
	a = &A;
	for ( size_t i (0) ; i < robots_base.size() ; i++ ) 
		{
			if ( a->get_uid() == robots_base[i]->get_uid() ) 
			{
				cout << " uid deja prise " << endl; 
				exit(0); 
			}
		}
	
	robots_base.push_back(a);
}
***/

void Base :: ajout_base (	std::vector <Base> & liste_base, 
							std::vector<Gisement>& liste_gisement){

	bool intersection_base (false),intersection_gisement(false);
	int base(0),gisement(0);
	
	for ( size_t i (0); i < liste_gisement.size() ; i++ ){
		if (intersection_deux_cercles ( getCercle(), liste_gisement[i].getCercleG()))  {

				intersection_gisement = true; 
				gisement= static_cast<int>(i);
		}
	}
	for ( size_t i (0); i < liste_base.size() ; i++ )		{
		if (intersection_deux_cercles ( getCercle(), liste_base[i].getCercle()))  {

				intersection_base = true; 
				base= static_cast<int>(i);			
			
		}		
	}
			
	if (intersection_gisement==true){
		std::cout<<message::base_field_superposition(get_x(),get_y(),liste_gisement[gisement].get_x()
												,liste_gisement[gisement].get_y());
		exit ( EXIT_FAILURE );
	}
	else if (intersection_base==true){
		std::cout<<message::base_superposition(get_x(),get_y(),liste_base[base].get_x()
												,liste_base[base].get_y());
		exit ( EXIT_FAILURE );
	} 
	else if ( intersection_base == false) {
		liste_base.push_back( *this);
	}
		
	
}
/***
bool Base :: PresenceRobotCOM ()
{
	geomod::Vecteur V; 
	for ( size_t i (0) ; i < robots_base.size() ; i++ ) 
	{
		if ( V.egalite ( getCercle().get_centre() , robots_base[i] -> getRobotCentre() ) and (robots_base[i] -> get_type() == 'C') ) 
		{
			return true;  
		}
	}
	return false ; 
}
***/
