#ifndef BASE_H
#define BASE_H

#include "geomod.h"
#include "simulation.h"
#include "robot.h"
#include "gisement.h"

using namespace std;

	class Base {
		public:
		Base ( double x , double y , double r , int  P, int F , int T , int C );
		double get_ressources() const;
		void set_ressources ( double& ener );
		void ajout_robot ( Robot* A ); 
		void ajout_base (	std::vector<Base> & liste_base, 
							std::vector<Gisement>& liste_gisement); 
		Cercle  get_cercle () const;
		double get_x() const;
		double get_y() const;
		Point get_centre() const ;
		void robot_comm(vector <Base> listeB) ;
	

		private:
		
		unsigned int nbP;
		unsigned int nbF;
		unsigned int nbT;
		unsigned int nbC;
		Cercle position;
		double ressources;
		vector <Robot* > robots_base;
	};

vector <Cercle> getPositionsBases ( );
 ; 

#endif
