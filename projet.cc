// projet.cc
// Auteurs : Georg Schwabedal et Daniel Silva
// Version : 

#include <iostream>
#include <vector>
#include "geomod.h"
#include "message_geomod.h"

using namespace std;

void scenario_1(double init_max);

void scenario_2(double init_max, double init_x, double init_y);

void scenario_3(double init_max, double init_x1, double init_y1,double  init_x2, 
				double init_y2);
				
void scenario_4(double init_max, double init_x1, double init_y1, double init_x2, 
				double init_y2);
				
void scenario_5(double init_max, double init_x, double init_y, double init_xc,
				double init_yc, double init_r);
				
void scenario_6(double init_max, double init_xc1, double init_yc1, double init_r1, 
				double init_xc2, double init_yc2, double init_r2);
				
void verification(int argc, vector<double> var,char *argv[]);

int main(int argc, char *argv[]){
	
	vector<double> var (argc-1);
	
	for (int i = 0; i < argc-1; i++){
		var[i]= stod(argv[i+1]);
		}

	verification(argc, var, argv);
	
	return 0;
}

void verification(int argc, vector<double> var,char *argv[]){
	switch(stoi(argv[1])){
		case 1:{
			if(argc== 3){
				scenario_1(var[1]);
				} else { message_geomod::bad_argc();}
			break;}
		case 2:	{
			if(argc== 5) {
				scenario_2(var[1], var[2], var[3]);
				}else { message_geomod::bad_argc();}
			break;}
		case 3:	{
			if(argc== 7){
				scenario_3(var[1], var[2], var[3], var[4], var[5]);
				}else { message_geomod::bad_argc();}
			break;}
		case 4:{
			if(argc== 7){
				scenario_4(var[1], var[2], var[3], var[4], var[5]);
				}else { message_geomod::bad_argc();}
			break;}
		case 5:	{
			if(argc== 8){
				scenario_5( var[1], var[2], var[3], var[4], var[5],var[6]);
				} else { message_geomod::bad_argc();}
			break;}
		case 6:	{
			if(argc== 9){
				scenario_6( var[1], var[2], var[3], var[4], var[5],	var[6], var[7]);
				}else { message_geomod::bad_argc();}	
			break;}
		default: {
			message_geomod::bad_argc();
			}
	}
}


// Defini le max et epsilon

void scenario_1(double init_max){
	set_max(init_max);
	message_geomod::print_max(init_max, get_max(), get_epsilon());
	}

//Defini le max, epsilon, et un point 

void scenario_2(double init_max, double init_x, double init_y){
	set_max(init_max);
	Point p1;
	p1.set_coordonnes(init_x,init_y);
	p1.normalisation(p1);
	message_geomod::print_point(init_x,init_y, p1.get_x(),p1.get_y());
}



//Defini deux points et consruit un le vecteur le plus court
void scenario_3(double init_max, double init_x1, double init_y1,double  init_x2, 
				double init_y2){
	set_max(init_max);
	Point p1;
	p1.set_coordonnes(init_x1, init_y1);

	Point p2;
	p2.set_coordonnes(init_x2,init_y2);
	
	p1.normalisation(p1);
	p2.normalisation(p2);
	
	Vecteur V1;
	V1.norme_vecteur( p1 , p2 );
	message_geomod::print_vect( V1.get_norme() , V1.get_vect_x() , V1.get_vect_y() );
};
				
				
				
				
//Defini deux points et compare s'ils sont égaux				
void scenario_4(double init_max, double init_x1, double init_y1, double init_x2,
				double init_y2){;
	
	set_max(init_max);
	Point p1, p2;
	p1.set_coordonnes(init_x1,init_y1);
	p2.set_coordonnes(init_x2, init_y2);	
	p1.normalisation(p1);
	p2.normalisation(p2);
	Vecteur W; 
	message_geomod::print_equal_point	(W.egalite(p1, p2), init_x1,init_y1,init_x2,
										init_y2);
}

//Defini un cercle et un point, puis verifie que le point appartien au cercle
void scenario_5(double init_max, double init_x, double init_y, double init_xc,
				double init_yc, double init_r){

	
	set_max(init_max);
	Point p1;
	Cercle c1;
	
	p1.set_coordonnes(init_x,init_y);
	p1.normalisation(p1);
	c1.set_centre(init_xc,init_yc);
	c1.set_rayon(init_r);
	c1.get_centre().normalisation(c1.get_centre());
	
	message_geomod::print_include_point(c1.appartient_cercle (p1), p1.get_x(),
										p1.get_y(), c1.get_centre().get_x() ,
										c1.get_centre().get_y(), c1.get_rayon() );				
	};
			
			
//Defini deux cercles et verifie s'il s'intersectent	
void scenario_6(double init_max, double init_xc1, double init_yc1, double init_r1, 
				double init_xc2, double init_yc2, double init_r2){
	
	set_max(init_max);
	Cercle c1,c2;
	c1.set_centre(init_xc1 , init_yc1 );
	c2.set_centre(init_xc2 , init_yc2 );
	c1.set_rayon(init_r1);
	c2.set_rayon(init_r2);
	c1.get_centre().normalisation(c1.get_centre());
	c2.get_centre().normalisation(c2.get_centre());

	message_geomod::print_intersect(intersection_deux_cercles( c1 , c2 ),init_xc1,
									init_yc1,init_r1,init_xc2,init_yc2,init_r2);
};


