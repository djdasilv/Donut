// simulation
// Auteurs : Georg Schwabedal et Daniel Silva


#ifndef SIMULATION
#define SIMULATION


#include <vector>
#include <string>

using namespace std;
	
	void lecture(char* nom);
	void set_etat (	int& etat, double nbP, double nbF, double nbT, double nbC);
	void decodage_ligne1(string line);
	void decodage_ligne2(string line);
	
	
#endif


