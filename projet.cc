// projet.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include "geomod.h"
#include "simulation.h"
#include "message.h"
#include "gisement.h"
#include <iostream>

using namespace std;



// lit le fichier dont le nom est transmis sur la ligne de commande
int main(int argc, char * argv[])
{
	if(argc != 2) exit(EXIT_FAILURE);
	
	lecture(argv[1]);

	cout<<message::success();

	return EXIT_SUCCESS;
}
