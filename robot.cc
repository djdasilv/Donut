// robot.cc
// Auteurs : Georg Schwabedal et Daniel Silva
#include "robot.h"

using namespace std;

Robot::Robot ( 	int id , double p , double x , double y , double x1 , double y1, 
					std::string at) {
	pos.set_coordonnes(x,y);
	uid=id;
}
	
int Robot :: get_uid () const	{
	return uid;
}
	
char Robot :: get_type () const{
	return type;
}
	
bool Robot :: transformationStringBool ( std::string A ){
	
	if ( A == "true" ) {
		return true; 
	}
	else{
		return false; 
	}
}
	
void Robot :: set_compteur_energie ( double& ener){
	compteur_energie = ener ; 
}
	
double Robot::  get_compteur_energie () const {
	return compteur_energie;
}
	
void Robot ::  set_compteur_de_distance ( double& dp ) {
	compteur_de_distance = dp ; 
}
	
double Robot :: get_compteur_de_distance () const{
	return compteur_de_distance; 
}
	
Point Robot :: get_centre() const{
	return pos; 
}
	
Robot :: ~Robot() {}

Prospecteur :: Prospecteur (int id,double par,double x_1,double y_1,double x3,
							double y3,string a,string r,string f,double x4,
							double y4,double t,double c)
							: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a){
	retour = transformationStringBool(r);
	found = transformationStringBool(f);
	xg = x4;
	yg = y4;
	taille = t;
	dispo = c;
	type = 'P';
}
Prospecteur :: Prospecteur (int id,double par,double x_1,double y_1,double x3,
							double y3,string a,string r,string f)
							: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a){
	retour = transformationStringBool(r);
	found = transformationStringBool(f);
	type = 'P';
}

Robot* Prospecteur ::  copie()  {
	return new Prospecteur(*this);
}
	
Prospecteur :: ~ Prospecteur() {}
Forage :: Forage (	int id,double par,double x_1,double y_1,double x3,double y3,
						string a): Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'F';
}

Robot* Forage::  copie() {
	return new Forage(*this);
}
Forage :: ~ Forage() {}
Transport :: Transport (int id,double par,double x_1,double y_1,double x3,
						double y3, string a,string r)
						: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a){
	retour  = transformationStringBool(r);
	type = 'T';
}
 Robot* Transport ::  copie()  {
	return new Transport(*this);
}

Transport :: ~Transport() {}
		
Communication :: Communication (int id,double par,double x_1,double y_1,double x3,
								double y3,std::string a)
								: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'C';
}
Robot* Communication ::  copie() {
	return new Communication(*this);
}

Communication :: ~Communication() {}
