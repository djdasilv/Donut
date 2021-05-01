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
	//if(argc != 2) exit(EXIT_FAILURE);
	
	
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

	Windowx window;
	window.set_default_size(900, 900);

	return app->run(window);
	
	//lecture(argv[1]);
	

	cout<<message::success();

	return EXIT_SUCCESS;
}
