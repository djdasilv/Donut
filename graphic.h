#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <gtkmm/drawingarea.h>
#include "geomod.h"
#include <cairomm/context.h>

using namespace std;

void dessin_cercle(const Cairo::RefPtr<Cairo::Context>& cr,int height,int widht,
					int x,int y,int rayon);

void dessin_ligne(const Cairo::RefPtr<Cairo::Context>& cr,int x, int y);

void dessin_point(const Cairo::RefPtr<Cairo::Context>& cr,int x, int y);



#endif // GTKMM_EXAMPLE_MYAREA_H
