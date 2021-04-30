// base.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include "base.h"
#include "message.h"
#include "constantes.h"


Cercle Base::get_cercle () const 
{ 
	return position;
}

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

double Base::get_x() const{
	return get_cercle().get_centre().get_x();
	}
double Base::get_y() const{
	return get_cercle().get_centre().get_y();
}


double Base :: get_ressources () const
{
	return ressources; 
}

void Base :: set_ressources( double& ener )
{
	ressources = ener; 
}


Point Base::get_centre() const {
	return get_cercle().get_centre();
}

//Verification que au moins un robot comm est present dans la base
void Base :: robot_comm(vector <Base> listeB) {
	
	bool presence_robotC(false);
		for (size_t i(0); i < robots_base.size(); i++){
			if (robots_base[i] -> get_type() == 'C'){
				Vecteur b;
				if (b.egalite(get_centre(), robots_base[i] -> get_centre()) == true ){
					//base = i;
					presence_robotC = true;
			
				}
			}
		}
	
	if (presence_robotC == false) {
		cout<<message::missing_robot_communication(get_x(),get_y());
		exit(EXIT_FAILURE);
	}
}

//Fonction de ajout d'une base a la liste avec toutes les base

void Base :: ajout_base (	std::vector <Base> & liste_base, 
							std::vector<Gisement>& liste_gisement){

	bool intersection_base (false),intersection_gisement(false);
	int base(0),gisement(0);
	
	//Verification d'intersection base-gisement
	for ( size_t i (0); i < liste_gisement.size() ; i++ ){
		if (intersection_deux_cercles ( get_cercle(), liste_gisement[i].getCercleG())){

				intersection_gisement = true; 
				gisement= static_cast<int>(i);
		}
	}
	for ( size_t i (0); i < liste_base.size() ; i++ )		{
		if (intersection_deux_cercles ( get_cercle(), liste_base[i].get_cercle()))  {

				intersection_base = true; 
				base= static_cast<int>(i);			
		}		
	}
	//Verification d'intersection gisement-gisement		
	if (intersection_gisement==true){
		std::cout<<message::base_field_superposition(get_x(),get_y(),
													liste_gisement[gisement].get_x(),
													liste_gisement[gisement].get_y());
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


//Addition d'un robot a une base et verification de UIDs differents
void Base :: ajout_robot ( Robot* A)
{

	bool uid_egal (false);
	for ( size_t i (0) ; i < robots_base.size() ; i++ ) {
		if ( A -> get_uid() == robots_base[i] -> get_uid() ){
			uid_egal = true;
		}
	}
	if (uid_egal) {
			cout<<message::identical_robot_uid(A -> get_uid());
			exit(EXIT_FAILURE); 
	}
	
	robots_base.push_back( A );
}
