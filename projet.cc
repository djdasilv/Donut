// projet.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include <iostream>
#include "geomod.h"
#include "simulation.h"
#include "message.h"
#include "gui.h"

using namespace std;


// lit le fichier dont le nom est transmis sur la ligne de commande
int main(int argc, char * argv[])
{
	//if(argc != 2) exit(EXIT_FAILURE);
//	lecture(argv[1]);
	  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

Window window;
	window.set_default_size(600, 600) ;
  //Shows the window and returns when it is closed.
  return app->run(window);
	//cout<<message::success();

	return EXIT_SUCCESS;
}
