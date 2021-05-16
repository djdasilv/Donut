#ifndef BASE_H
#define BASE_H

#include "geomod.h"
#include "robot.h"
#include "gisement.h"

using namespace std;

	struct gis_trouve 
	{
	double xg;
	double yg;
	bool traite;
	bool ennemi;
	};

	class Base {
		public:
		Base ( double x , double y , double r , int  P, int F , int T , int C );
		Cercle  get_cercle () const;
		Point get_centre() const ;

		double get_ressources() const;
		double get_x() const;
		double get_y() const;
		
		void robot_comm(vector <Base*> listeB) ;
		void maj_gisements_connus ();  
		void set_ressources ( double& ener );
		void ajout_robot ( Robot* A ); 
		
		int get_nb_robot() const;
		Robot* get_robot(int i) const;
		
		~Base ();
		Base (const Base& other);

		public:
		int get_nbP() const;
		int get_nbC() const;
		int get_nbT() const;
		int get_nbF() const;
		
		vector < Robot* > robots_base; // faudra le remettre dans private plus tard
		vector < Robot* > robots_connect;

		private:
		
		unsigned int nbP;
		unsigned int nbF;
		unsigned int nbT;
		unsigned int nbC;
		Cercle position;
		double ressources;
	};

		void ajout_base (	Base* A  , std::vector<Base*> & liste_base, 
							std::vector<Gisement*>& liste_gisement); 
		
		vector <Cercle> getPositionsBases ( );

		void update_voisins ( Base* A , Base* B );
		void rec_DEF(Base* B  , Robot* A ); 
#endif
