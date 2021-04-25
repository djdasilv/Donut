#ifndef	ROBOT_H
#define ROBOT_H

#include "gisement.h"
#include "geomod.h"

using namespace std;

class Robot{
	
	
	public:
	Robot ( int id ,double p ,double x ,double y ,double x1 ,double y1 ,string at); 	
	void set_compteur_energie ( double& ener);
	double get_compteur_energie () const ;
	void set_compteur_de_distance ( double& dp ); 
	double get_compteur_de_distance () const;
	Point get_centre() const;
	int get_uid () const ; 
	bool transformationStringBool ( std::string A ) ;
	char get_type () const;
	
	protected:
	int uid;  
	double compteur_de_distance;
	Point pos;
	Point but; 
	bool atteint;
	double compteur_energie;
	char type; 
};

class Prospecteur : public Robot 
{
	public:
	Prospecteur (	int id,double par,double x_1,double y_1,double x3,double y3,
					std::string a,std::string r,std::string f,double x4,double y4,
					double t,double c);
					
	Prospecteur(	int id,double par,double x_1,double y_1,double x3,double y3, 
					string a, string b,string c);
	private: 
	bool retour;
	bool found;
	double xg;
	double yg;
	double taille; 
	double dispo; 
};

class Forage : public Robot 
{
	public:
	Forage (int id,double par,double x_1,double y_1 , double x3,double y3,string a); 
	private :
};

class Transport : public Robot
{
	public:
	Transport (	int id,double par,double x_1,double y_1,double x3,double y3,string a,
				string r);
	private :
	bool retour; 
};

class Communication : public Robot
{
	public:
	Communication (	int id,double par,double x_1,double y_1 , double x3,double y3,
					string a); 
	private :
};

#endif
