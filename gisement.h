#ifndef GISEMENT_H
#define GISEMENT_H
#include <iostream>
#include <vector>
#include <cmath>
#include "geomod.h"

class Gisement{
	public: 
	Gisement( double x , double y , double r , double qt) ;
	void set_qt_ressources (double& qt_r) ;
	double get_qt_resources () const ;
	void ajout_gisement (std::vector<Gisement> &liste);
	Cercle getCercleG () const;
	double get_x();
	double get_y();
	
	private: 
	Cercle taille_ressources;
	double quantitee_ressources;

};

std::vector <Cercle> getPositionsBases ( );

#endif
