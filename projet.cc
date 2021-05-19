// projet.cc
// Auteurs : Georg Schwabedal et Daniel Silva


#include <iostream>
#include "geomod.h"
#include "simulation.h"
#include "message.h"
#include <gtkmm.h>
#include "gui.h"


using namespace std;



// lit le fichier dont le nom est transmis sur la ligne de commande
int main(int argc, char * argv[])
{
	Simulation simulation;
	auto app= Gtk::Application::create(); 
	
	if(argc == 2) simulation.lecture(argv[1]);
		
	Windowx window;

	Simulation* sim = new Simulation(simulation);		//on initialise une instance de sim et de window 
	set_simulation(sim);								// passe le pointeur sim au module gui 
	window.set_default_size(900, 900);

return app->run(window);}
