#include "graphic.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr){
	ptcr= &cr;
}

void dessin_base(	int height,int width,int x ,int y, int rayon)
{	

	(*ptcr)->arc(x, y,  rayon , 0.0, 2.0 * M_PI); 

	(*ptcr)->stroke();

	//if (x+rayon> width or x < rayon or y+rayon> height or y<rayon){
		(*ptcr)->arc(x+2*dim_max, y,  rayon , 0.0, 2.0 * M_PI); 
		(*ptcr)->stroke();

		(*ptcr)->arc(x+2*dim_max, y+2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		(*ptcr)->stroke();

		(*ptcr)->arc(x+2*dim_max, y-2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		(*ptcr)->stroke();

		(*ptcr)->arc(x, y+2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		(*ptcr)->stroke();

		(*ptcr)->arc(x, y-2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		(*ptcr)->stroke();

		(*ptcr)->arc(x-2*dim_max, y,  rayon , 0.0, 2.0 * M_PI); 
		(*ptcr)->stroke();

		(*ptcr)->arc(x-2*dim_max, y+2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		(*ptcr)->stroke();

		(*ptcr)->arc(x-2*dim_max, y-2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		(*ptcr)->stroke();
	
}

void dessin_gisement(	int height,int width,int x ,int y, int rayon)
{	
	
	(*ptcr)->arc(x, y,  rayon , 0.0, 2.0 * M_PI); 
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();

	
	(*ptcr)->arc(x+2*dim_max, y,  rayon , 0.0, 2.0 * M_PI); 
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();

	(*ptcr)->arc(x+2*dim_max, y+2*dim_max,  rayon , 0.0, 2.0 * M_PI);
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();

	(*ptcr)->arc(x+2*dim_max, y-2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();

	(*ptcr)->arc(x, y+2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();

	(*ptcr)->arc(x, y-2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();
	(*ptcr)->arc(x-2*dim_max, y,  rayon , 0.0, 2.0 * M_PI); 
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();

	(*ptcr)->arc(x-2*dim_max, y+2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();
	(*ptcr)->arc(x-2*dim_max, y-2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();
	//}
}

void dessin_liens(int xa,int ya,int xb,int yb){
	(*ptcr)->set_source_rgb(0.933,0.51,0.933);
	(*ptcr)->move_to(xa,ya);
	(*ptcr)->line_to(xb,yb);
	(*ptcr)-> stroke();
	(*ptcr)->set_source_rgb(0,0,0);
}

void dessin_point(int x, int y){
	(*ptcr)->arc(x, y,  1, 0.0, 2.0 * M_PI);
	(*ptcr)->stroke();

	}

void dessin_cadre(int height, int width){
	(*ptcr)->set_line_width(5.0);
	(*ptcr)->set_source_rgb(0.5,0.5,0.5);
	(*ptcr)->move_to(-dim_max,dim_max);
	(*ptcr)->line_to(dim_max,dim_max);
	(*ptcr)->line_to(dim_max,-dim_max);
	(*ptcr)->line_to(-dim_max,-dim_max);
	(*ptcr)->line_to(-dim_max,dim_max);
	(*ptcr)-> stroke();
	(*ptcr)->set_source_rgb(0,0,0);
	(*ptcr)->set_line_width(2.0);
}
void dessin_robotC(int height,int width,int x,int y,int rayon){
	(*ptcr)->set_source_rgb(0.5,0,1);
	for (double i = 0; i < 2*M_PI; i=i+0.6)
	{
		(*ptcr)->arc(x, y,  30 , i, i+0.3);
		(*ptcr)->stroke();
	}
	(*ptcr)->set_source_rgb(0,0,0);
}


void set_couleur_base(int i){
	int valeur = i%7;
	switch (valeur){
		case 1:
			(*ptcr)->set_source_rgb(1,0,0);
			break;
		case 2:
			(*ptcr)->set_source_rgb(0,1,0);
			break;
		case 3:
			(*ptcr)->set_source_rgb(0,0,1);
			break;
		case 4:
			(*ptcr)->set_source_rgb(1,1,0);
			break;
		case 5:
			(*ptcr)->set_source_rgb(1,0,1);
			break;
		case 6:
			(*ptcr)->set_source_rgb(0,1,1);
			break;}
	
}
