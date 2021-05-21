#ifndef BASE_H
#define BASE_H

#include "geomod.h"
#include "robot.h"
#include <fstream>
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
		double get_nb_robot () ; 
		int get_set_nv_max_uid ();
		bool get_4G () ; 
		
		int get_nbP() const; 
		int get_nbC() const;
		int get_nbT() const;
		int get_nbF() const;
		
		bool get_vie () ;
		void set_vie ( bool a );
		Point GisementPlusLoin () ; 
		
		int robot_comm(vector <Base*> listeB) ;
//		void maj_gisements_connus ();  
		void set_ressources ( double& ener );
		void MaJNbRobType (); 
		int ajout_robot ( Robot* A ); 
		void Creation4G ();
		void maintenance () ; 
		void launch4G_3_supplemetaires ();
		void add_gisement_connus (); 
		void commande_gisement () ; 
		void trouver_max_uid ();
		void FindActive4G () ; 
		void ViderRobotsT () ; 
		void TabRemoteOrAutonomous ();
		void lancement_p();
		int get_couleur();
		void set_couleur(size_t i);
		bool decision_interet_gisement ( double x , double y , double r , double c ) ; 
		int generate_uid () ;
		int get_nb_robot() const;
		void saveBase1(ofstream& myfile);
		void saveBase2(ofstream& myfile);
		Robot* get_robot(int i) const;

		
		~Base ();
		Base (const Base& other);

		
		vector < Robot* > robots_base; // faudra le remettre dans private plus tard
		vector < Robot* > robots_connect;
		vector < Robot* > robot_communication;
		vector < Robot* > robots_remote;  
		vector < Robot* > robots_autonomous;
		array<array<double , 3 > , 50 > Monde4G;
		
		private:
		
		int compteur;
		int max_uid; 
		int couleur;
		unsigned int nbP;
		unsigned int nbF;
		unsigned int nbT;
		unsigned int nbC;
		Cercle position;
		double ressources;
		bool Active4G; 
		bool vie; 
	};

//		void ajout_base (	Base* A  , std::vector<Base*> & liste_base, 
//							std::vector<Gisement*>& liste_gisement); 
		
		string boolToString(bool a);
		vector <Cercle> getPositionsBases ( );
		void rec_DEF( Base* B , Robot* A );
		
#endif


/**		void update_voisins ( Base* A , Base* B );
		void rec_DEF(Base* B  , Robot* A ); **/
