// simulation
// Auteurs : Georg Schwabedal et Daniel Silva


#ifndef SIMULATION
#define SIMULATION


#include <vector>
#include <string>
#include "base.h"
#include "constantes.h"


using namespace std;


	
	void lecture(char* nom);
	void set_etat (	int& etat, double nbP, double nbF, double nbT, double nbC);
	void effacer();
	void decodage_ligne1(string line);
	void decodage_ligne2(string line);
	Gisement* get_gisement(int i);
	size_t gisement_size();
	Base * get_base(int i);
	size_t base_size();
	
#endif


