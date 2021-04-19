// simulation
// Auteurs : Georg Schwabedal et Daniel Silva


#ifndef SIMULATION
#define SIMULATION


#include <vector>
#include <string>

using namespace std;
	
	void lecture(char* nom);
	void set_etat (	int& etat, double nbP, double nbF, double nbT, double nbC);
	void decodage_ligne(string line);
	void simulation(vector<int> bases);
	void update_voisin();
	void connexion(int);
	void maintenance(int);
	void creation(int );
	void update_remote();
	void update_autonomous();
	void destruction(int);
	
	



#endif


