#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "geomod.h"
#include "constantes.h"
#include "graphic_gui.h"
#include <cairomm/context.h>

using namespace std;

void dessin_base(int height,int widht,
					int x,int y,int rayon);
					
void dessin_gisement(int height,int widht,
					int x,int y,int rayon);

void dessin_robot();
void dessin_cadre(int height, int width);
void dessin_liens(int x, int y);
void dessin_robotC(int height,int widht,
					int x,int y,int rayon);

void dessin_point(int x, int y);

void set_couleur_base(int i);


#endif // GTKMM_EXAMPLE_MYAREA_H
