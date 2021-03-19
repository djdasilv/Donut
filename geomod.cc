#include <iostream>
#include <array>
#include <cmath>
#include "geomod.h"

using namespace std;


//Max et epsilon
namespace {
	double epsilon_zero;
	double max1; 
}


//Fonctions de verification de valeurs de input
void set_max(double init_max){
	if(init_max >= 0){
		max1= init_max;
		epsilon_zero = max1* pow(10,-10);
	}
}
	
double get_max(){
	return max1;
	
}

double get_epsilon(){
	return epsilon_zero;
}

double calculNormeVecteur(double x1 , double y1 , double x2 , double y2 ) 
{
	double NormeVecteur2D; 
	NormeVecteur2D = sqrt ((pow(( x1-x2 ) , 2 )) + pow ((y1-y2) , 2) ); 
	return NormeVecteur2D;  
}

// Vérifie si une valeur peut être considéré comme nul  
bool equal_zero ( double verification ) 
{
	if (abs(verification) <= epsilon_zero)
	{
		return false;
	}
	return true;
	
}

//Booléen d'egalite des points

bool Vecteur :: egalite(Point2D A, Point2D B){
	NormeVecteur ( A , B ); 
	if (getNorme () <= epsilon_zero){
		return true;
	}
	
	return false ;
}

//Fonctions de la classe Point2D

//Defini le coordonnes du point
void Point2D::setCoordonnes(double x1 , double y1)
{
	x=x1;
	y=y1;
}

//Retourne y du point
double Point2D::getX() {
	return x;
}

//Retourne y du point
double Point2D::getY() {
	
	return y;
}
	
//Normalise les x et y dans le max donné
void Point2D::Normalisation(double x3, double y3){

	if ( x3 > max1) {
	
			x = x3 - 2*max1;
	} else if ( x3 < -max1 )
		{
		x = x3 + 2*max1;
	}
	if ( y3 > max1) {
	
			y = y3 - 2*max1;
	} else if ( y3 < -max1 )
		{
		y = y3 + 2*max1;
	}
}

// Normalisation par surchage du point 
void Point2D::Normalisation(Point2D D) {
	
	Normalisation(D.x, D.y);
}

void Point2D::CoordonnesEquivalentes (){
	equivalent = {
		getX() + 2* max1  	, getY(),
		getX() - 2* max1  	, getY(),
		getX() 				, getY() + 2* max1 ,
		getX() 				, getY() - 2* max1 ,
		getX() - 2* max1 	, getY() - 2* max1 ,
		getX() + 2* max1 	, getY() + 2* max1 ,
		getX() + 2* max1 	, getY() - 2* max1 ,
		getX() - 2* max1 	, getY() + 2* max1 ,
		getX() 				, getY() 
	};
}

void Point2D::setCoordonnesEquivalentes (  int i , int j , double x) {
	equivalent[i][j]=x;
	cout << equivalent[i][j] << endl;
}

// Fonctions de la classe Vecteur

double Vecteur :: getNorme () const 
{
return norme;
}

double Vecteur :: getVectX () const 
{
return vecteurX;
} 

double Vecteur :: getVectY () const 
{
return vecteurY;
} 

double Point2D::getEquivalent(int a, int b){
	
	return equivalent[a][b];
}

void Vecteur::NormeVecteur(Point2D A, Point2D B)
{

	x_depart = A.getX () ;
	y_depart = A.getY () ;
	x_arrive = B.getX () ;
	y_arrive = B.getY () ;


	B.CoordonnesEquivalentes ();
	x_equivalent_arrive = B.getEquivalent(0,0);
	y_equivalent_arrive = B.getEquivalent(0,1);
	norme = calculNormeVecteur	(x_depart , y_depart , x_equivalent_arrive 
								,y_equivalent_arrive);


	for ( int i(1); i < 9 ; i++ )  
		{
		if ( calculNormeVecteur(x_depart, y_depart ,B.getEquivalent(i,0) , 
								B.getEquivalent(i,1)) < norme )
			{
			x_equivalent_arrive = B.getEquivalent(i,0);
			y_equivalent_arrive = B.getEquivalent(i,1);
			norme = calculNormeVecteur( x_depart , y_depart , B.getEquivalent(i,0) , 
										B.getEquivalent(i,1));
			} 
		}
 	vecteurX = x_equivalent_arrive - x_depart;
	vecteurY = y_equivalent_arrive - y_depart;
}



//Fonctions de la classe Cercle

void Cercle::setCentre ( double x1 , double x2){

	centre.setCoordonnes ( x1 , x2 ); 
} 

void Cercle::setRayon ( double R) {

	Cercle::rayon = R; 
} 

double Cercle::getRayon() {

return Cercle::rayon; 
}

Point2D Cercle::getCentre(){
	return centre;
}


bool Cercle::appartientCercle ( Point2D A) 
{
	Vecteur V;
	V.NormeVecteur(getCentre(),A); 
	if ( V.getNorme() < rayon - epsilon_zero) 
		{
		return true;	
	}
return false;			
}  

bool IntersectionDeuxCercles ( Cercle C1 , Cercle C2 )
{
	Vecteur W;
	W.NormeVecteur (C1.getCentre() , C2.getCentre()); 
	
	if ( W.getNorme() <= C1.getRayon() + C2.getRayon() - epsilon_zero) 
	{
		return true; 
	}
	 
	return false; 
}

