// simulation
// Auteurs : Georg Schwabedal et Daniel Silva


#ifndef SIMULATION
#define SIMULATION

#include "base.h"
#include "constantes.h"
#include "message.h"
#include <vector>
#include <string>

using namespace std;



class Simulation{
	
	public:
	
	Simulation();
	~Simulation();
	bool simulation();
	void lecture(char* nom);
	void set_etat (	int& etat, double nbP, double nbF, double nbT, double nbC,double bases);
	void decodage_ligne1(string line);
	void decodage_ligne2(string line);
	void TabRobotsConnectBases();
	Gisement* get_gisement(int  i);
	Base* get_base(int i);
	size_t gisement_size();
	size_t base_size();	


	private:
	vector < Gisement* > liste_gisement; 
	vector < Base* > liste_base;

};
	 
	
	
#endif


