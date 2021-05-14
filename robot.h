#ifndef	ROBOT_H
#define ROBOT_H

#include "geomod.h"
#include "constantes.h"
#include "gisement.h"

using namespace std;

class Robot{
	
	
	public:
	Robot ( int id ,double p ,double x ,double y ,double x1 ,double y1 ,string at);
	virtual ~ Robot(); 	
	virtual Robot* copie()  = 0;
	
	void set_compteur_energie ( double& ener);
	void set_compteur_de_distance ( double& dp ); 
	void set_robot_base ( bool f); 
	void deplacement_vers_but ();
	void set_but ( double x3 , double y3); 
	void set_but ( Point A ); 
	void set_Connect( bool a ); 
	
	double get_compteur_energie () const ;
	double get_compteur_de_distance () const;
	int get_uid () const ; 
	double get_x() const;
	double get_y() const;
	
	Point get_centre() const;
	Point get_but () const; 
	
	bool transformationStringBool ( std::string A ) ;
	bool get_comm_Base () const;
	bool get_connect () ;
	bool get_atteint() const; 
	
	char get_type () const;
	
//	virtual void mode_autonome( double x4 , double y4 , Gisement* C) = 0;  
//	virtual void mode_remote ( double x4 , double y4 , Gisement* C) = 0;
	
	vector <Robot* > robots_voisins; // faudra le remettre dans le protected plus tard

	protected:
	
	int uid;  
	
	double compteur_de_distance;
	double compteur_energie;
	
	Point pos;
	Point but; 
	
	char type;
	
	bool atteint;
	bool Connect;
	bool robot_base;
};



class Prospecteur : public Robot 
{
	public:
	Prospecteur (	int id,double par,double x_1,double y_1,double x3,double y3,
					std::string a,std::string r,std::string f,double x4,double y4,
					double t,double c);
					
	Prospecteur(	int id,double par,double x_1,double y_1,double x3,double y3, 
					string a, string b,string c);
	~Prospecteur();
	
//	void mode_autonome( double x4 , double y4 , Gisement* G ) override; 
//	void mode_remote ( double x4 , double y4 , Gisement* C);
	void set_found ( bool i ); 
	void set_xg ( double x1 );
	void set_yg ( double y1 );
	void set_taille( double t ); 
	void set_capacite ( double c );

	bool get_retour() const;
	bool get_found () const ; 
	
	double get_xg () const;
	double get_yg () const;
	double get_taille () const;
	double get_capacite () const;
	
	Robot* copie() ;
	
	private: 
	bool retour;
	bool found;
	double xg;
	double yg;
	double taille; 
	double capacite; 
 
};


class Forage : public Robot 
{
	public:
	Forage (int id,double par,double x_1,double y_1 , double x3,double y3,string a); 
	Robot* copie() ;
	~Forage();
//	void mode_autonome ( double x4 , double y4 , Gisement* C ) override;
//	void mode_remote ( double x4 , double y4 , Gisement* C);
	
	private :
};


class Transport : public Robot
{
	public:
	Transport (	int id,double par,double x_1,double y_1,double x3,double y3,string a,
				string r);
	Robot* copie()  ;
	~Transport();
//	void mode_autonome( double x4 , double y4 , Gisement* C ) override;
//	void mode_remote ( double x4 , double y4 , Gisement* C);
	
	private :
	bool retour; 
};


class Communication : public Robot
{
	public:
	Communication (	int id,double par,double x_1,double y_1 , double x3,double y3,
					string a); 
	Robot* copie() ;
	~Communication();
//	void mode_autonome( double x4 , double y4 , Gisement* C ) override;
//	void mode_remote ( double x4 , double y4 , Gisement* C); 
	 
	private :
};

#endif
