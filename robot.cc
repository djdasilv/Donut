// robot.cc
// Auteurs : Georg Schwabedal et Daniel Silva
#include "robot.h"

using namespace std;

//=========================================================Robot-biblio get set====================================================================================


Robot::Robot ( 	int id , double p , double x , double y , double x1 , double y1, 
					std::string at) {
	pos.set_coordonnes(x,y);
	but.set_coordonnes(x1,y1);
	compteur_de_distance=p;
	uid=id;
	atteint= transformationStringBool(at);
}
	
int Robot :: get_uid () const	{
	return uid;
}
	
void Robot :: set_Connect( bool a )
{
	Connect = a; 	
}
char Robot :: get_type () const{
	return type;
}

bool Robot :: get_comm_Base ()  const 
{
	return robot_base; 
}

bool Robot :: get_connect ()
{
	return Connect; 
}

bool Robot :: transformationStringBool ( std::string A ){
	
	if ( A == "true" ) {
		return true; 
	}
	else{
		return false; 
	}
}

double Robot::get_x() const{
	return get_centre().get_x();
}

double Robot::get_y() const {
	return get_centre().get_y();
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


void Robot :: set_robot_base ( bool f )
{
	robot_base = f; 
}
	
Point Robot :: get_centre() const{
	return pos; 
}

Robot :: ~Robot() {}

double Robot::get_xg() const {
	return get_but().get_x();
}

double Robot::get_yg() const {
	return get_but().get_y();
}

double Robot::get_rayong() const{
	return 0;
}
double Robot::get_capaciteg() const{
	return 0;
}

bool Robot::get_found() const{
	return false;}

bool Robot::get_retour() const {
	return false;}

//=========================================================Prospecteur====================================================================================

Prospecteur :: Prospecteur (int id,double par,double x_1,double y_1,double x3,
							double y3,string a,string r,string f,double x4,
							double y4,double t,double c)
							: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a){
	retour = transformationStringBool(r);
	found = transformationStringBool(f);
	xg = x4;
	yg = y4;
	taille = t;
	capacite = c;
	type = 'P';
}
Prospecteur :: Prospecteur (int id,double par,double x_1,double y_1,double x3,
							double y3,string a,string r,string f)
							: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a){
	retour = transformationStringBool(r);
	found = transformationStringBool(f);
	type = 'P';
	atteint = transformationStringBool(a);
	
}

Robot* Prospecteur ::  copie()  {
	return new Prospecteur(*this);
}
	
Prospecteur :: ~ Prospecteur() {}


/***
void Prospecteur :: mode_autonome ( double x4 , double y4 , Gisement* C )				// on donne les coordonnes du robot de communication de la base si jamais un retour est necessaire
{																						// on remarque que on a pas une grande difference entre le mode autonome et le mode remote. 
	Vecteur V;
 
	if ( found == false ) 
	{ 
			V.norme_vecteur( C -> getCercleG().get_centre() , pos ); 	 // check pour l'intersection avec un gisement
			if( C -> getCercleG().get_rayon() < V.get_norme())
				{ 
					found = true;										
					xg = C -> getCercleG().get_x();
					yg = C-> getCercleG().get_y();
					taille = C -> getCercleG().get_rayon();
					capacite = C -> get_qt_resources();
					but.set_coordonnes( x4 , y4 );
				} 
		
	}
	else
	{ 
		Point P;
		P.set_coordonnes ( x4 , y4 ) ; 
		V.norme_vecteur ( pos , P ); 
		if ( (maxD_prosp - compteur_de_distance - 2* deltaD) < V.get_norme() )   
		{
			but.set_coordonnes( x4 , y4 );
		}else{
				int alle = randomNb ( 4 );
				if ( alle == 1 ) {but.set_coordonnes(  pos.get_x() + deltaD , pos.get_y() );}
				else if ( alle == 2) {but.set_coordonnes(  pos.get_x(), pos.get_y() + deltaD );}
				else if ( alle == 3) {but.set_coordonnes(  pos.get_x(), pos.get_y() - deltaD );}
				else if ( alle == 4) {but.set_coordonnes(  pos.get_x() - deltaD , pos.get_y() );}
		}
	}
	deplacement_vers_but();
}


***/ 



void Prospecteur :: set_found ( bool i ){ found = i ; }
void Prospecteur :: set_xg ( double x1 ){ xg = x1 ; }
void Prospecteur :: set_yg ( double y1 ){ yg = y1 ; }
void Prospecteur :: set_taille( double t ){ taille = t ; } 
void Prospecteur :: set_capacite ( double c ){ capacite = c ; }
	
bool Prospecteur :: get_found () const { return found; } 
bool Prospecteur:: get_retour() const {return retour;}	
double Prospecteur :: get_xg () const{ return xg ; }
double Prospecteur :: get_yg () const{ return yg ; }
double Prospecteur :: get_taille () const{ return taille ; }
double Prospecteur :: get_capacite () const{ return capacite ; }


//=========================================================Forage====================================================================================

Forage :: Forage (	int id,double par,double x_1,double y_1,double x3,double y3,
						string a): Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'F';
}

Robot* Forage::  copie() {
	return new Forage(*this);
}
Forage :: ~ Forage() {}

//=========================================================Transport====================================================================================

Transport :: Transport (int id,double par,double x_1,double y_1,double x3,
						double y3, string a,string r)
						: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a){
	retour  = transformationStringBool(r);
	type = 'T';
	atteint = transformationStringBool(a) ;
	retour = transformationStringBool(r);
}
 Robot* Transport ::  copie()  {
	return new Transport(*this);
}

Transport :: ~Transport() {}

//=========================================================Communication====================================================================================
		
Communication :: Communication (int id,double par,double x_1,double y_1,double x3,
								double y3,std::string a)
								: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'C';
	robot_base = false; 
	atteint = transformationStringBool(a);
}

Robot* Communication ::  copie() {
	return new Communication(*this);
}

Communication :: ~Communication() {}

Point Robot :: get_but() const{
	return but; 
}

bool Robot::get_atteint() const {
	return atteint;
}
//=========================================================Robot algos====================================================================================


void Robot :: deplacement_vers_but () 
{
double D, r, m; 
Vecteur V; 
		V.norme_vecteur( pos , but );  
		D = V.get_norme();
		r = fmod( D , deltaD ); 
		m = ( D - r) / deltaD; 
	if ( D < deltaD ) {
		pos.set_coordonnes( but.get_x() , but.get_y() ); 
	}else {
		pos.set_coordonnes ( pos.get_x() + (V.get_vect_x()/m) , pos.get_y() + (V.get_vect_y()/m));
	}
	
	pos.normalisation(pos); 
}

void Robot :: set_but ( double x3 , double y3){
	but.set_coordonnes ( x3 , y3 );  
}

void Robot :: set_but ( Point A )
{
	but.set_coordonnes ( A.get_x() , A.get_y() ); 
}





