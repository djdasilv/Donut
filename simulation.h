// simulation
// Auteurs : Georg Schwabedal et Daniel Silva


#ifndef SIMULATION
#define SIMULATION

#include "base.h"
#include "gisement.h"
#include "robot.h"
#include "constantes.h"
#include "message.h"
#include <vector>
#include <string>

using namespace std;


class Simulation{
	
	public:
	
	Simulation();
	~Simulation();
	
	bool simulation (); // genre ca ca sera probablement notre méthode "ultime qui vas faire un step"

	void lecture(char* nom);
	void set_etat (	int& etat, double nbP, double nbF, double nbT, double nbC,double bases);
	void decodage_ligne1(string line);
	void decodage_ligne2(string line);
	void TabRobotsConnectBases(Base* A );
	
	
	void TabTotalRobot ();
	void VideTabTotalConnectFalse (); 
	
	void maintenance_bases ( Base* A );
	void creation (Base* A); 
	void update_remote ( Base* A );
	void update_autonomous ( Base* A);
	
	Gisement* get_gisement(int  i);
	Base* get_base(int i);
	size_t gisement_size();
	size_t base_size();	


	void verification (Base* A);
	void AffichageRobots ();


	private:
	vector < Gisement* > liste_gisement; 
	vector < Base* > liste_base;
	vector < Robot* > total_robots;										// ce vector est la pour assurer la conservation de l'information originelle des robots
	void effacer ( Base* A );									// sinon on se retrouve dans la situation dans laquelle les robots des 
										// premières bases ont déjà changé ( au sujet pt revoir le code de la fonction update voisins) 

};



	void update_voisins ( Base* A , Base* B );
//	void rec_DEF(Base* B  , Robot* A ); 
	void ajout_base (	Base* A  , std::vector<Base*> & liste_base, 
					std::vector<Gisement*>& liste_gisement); 
	bool test();
	
	 
	
	
#endif


