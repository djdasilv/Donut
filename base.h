#ifndef BASE_H
#define BASE_H


#include <array>
#include <vector>
#include "geomod.h"
#include "simulation.h"
//#include "robot.h"
#include "gisement.h"



	class Base {
		public:
		Base ( double x , double y , double r , int  P, int F , int T , int C );
		double get_ressources() const;
		void set_ressources ( double& ener );
		//void ajout_robot ( robot::Robot A ); 
		void ajout_base (	std::vector<Base> & liste_base, 
							std::vector<Gisement>& liste_gisement); 
		Cercle  getCercle () const;
		double get_x();
		double get_y();
		bool PresenceRobotCOM ();

		private:
		unsigned int nbP;
		unsigned int nbF;
		unsigned int nbT;
		unsigned int nbC;

	//	std::vector < robot::Robot* > robots_base;
		Cercle position;
		double ressources;
};

std::vector <Cercle> getPositionsBases ( );
 ; 

#endif
