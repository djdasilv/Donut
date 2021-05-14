#include "graphic.h"
#include <stdlib.h>

using namespace std;


void dessin_cercle(	const Cairo::RefPtr<Cairo::Context>& cr,int height,int width,int x ,int y, int rayon)
{	

	cr->arc(x, y,  rayon , 0.0, 2.0 * M_PI); 
	cr->stroke();

	//if (x+rayon> width or x < rayon or y+rayon> height or y<rayon){
		cr->arc(x+2*dim_max, y,  rayon , 0.0, 2.0 * M_PI); 
		cr->stroke();

		cr->arc(x+2*dim_max, y+2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		cr->stroke();

		cr->arc(x+2*dim_max, y-2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		cr->stroke();

		cr->arc(x, y+2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		cr->stroke();

		cr->arc(x, y-2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		cr->stroke();

		cr->arc(x-2*dim_max, y,  rayon , 0.0, 2.0 * M_PI); 
		cr->stroke();

		cr->arc(x-2*dim_max, y+2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		cr->stroke();

		cr->arc(x-2*dim_max, y-2*dim_max,  rayon , 0.0, 2.0 * M_PI); 
		cr->stroke();
	//}
}


void dessin_ligne(const Cairo::RefPtr<Cairo::Context>& cr,int x,int y){
	cr->line_to(x,y);
	cr-> stroke();

}

void dessin_point(const Cairo::RefPtr<Cairo::Context>& cr,int x, int y){
	cr->arc(x, y,  1, 0.0, 2.0 * M_PI);
	cr->stroke();

	}
