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
	void set_compteur_de_distance ( double dp ); 
	void set_robot_base ( bool f); 
	void deplacement_vers_but ();
	void set_but ( double x3 , double y3); 
	void set_but ( Point A ); 
	void set_Connect( bool a );
	void set_retour ( bool b ) ;  
	void rentrer_base ();
	void set_base ( double xb , double yb ) ;
	double get_compteur_energie () const ;
	double get_compteur_de_distance () const;
	int get_uid () const ; 
	
	Point get_centre() const;
	Point get_But () const; 
	
	bool transformationStringBool ( std::string A ) ;
	bool get_Comm_Base () const;
	bool get_Connect () ; 
	bool get_retour () ; 
	bool get_atteint () ; 
	
	char get_type (); 
	
	virtual void mode_autonome( Gisement* C ) = 0;  
	virtual void mode_remote ( Gisement* C ) = 0;
	virtual double P_get_xg () {return 0;};
	virtual double P_get_yg () { return 0;};
	virtual double P_get_taille () {return 0;};
	virtual double P_get_capacite () {return 0;};
	virtual bool P_get_found() {return true;};
	virtual void P_set_found ( bool a ) {}; 
	
	

	bool get_retour() const;
	double get_x() const;
	double get_y() const;
	
	vector <Robot* > robots_voisins; // faudra le remettre dans le protected plus tard

	protected:
	
	int uid;  
	
	double compteur_de_distance;
	double compteur_energie;
	double x_base;
	double y_base; 
	
	Point pos;
	Point but; 
	
	char type;
	
	bool atteint;
	bool Connect;
	bool retour; 
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
	 
	
	void mode_autonome(  Gisement* G ) override; 
	void mode_remote ( Gisement* C );
	void set_found ( bool i ); 
	void set_xg ( double x1 );
	void set_yg ( double y1 );
	void set_taille( double t ); 
	void set_capacite ( double c );

	
	bool get_found () const ; 
	
	/***
	double get_xg () const;
	double get_yg () const;
	double get_taille () const;
	double get_capacite () const;***/

	virtual double P_get_xg () override;
	virtual double P_get_yg () override;
	virtual double P_get_taille () override;
	virtual double P_get_capacite () override;
	virtual bool P_get_found() override;
	virtual void P_set_found ( bool a ) override; 
	
	Robot* copie() ;
	
	private: 
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
	void mode_autonome ( Gisement* C ) override;
	void mode_remote ( Gisement* C ) override;
	void GisementPlein ( Gisement*C ) ; 
	void forage ( Gisement* A ) ; 
	
	virtual double P_get_xg () override;
	virtual double P_get_yg () override;
	virtual double P_get_taille () override;
	virtual double P_get_capacite () override;
	virtual bool P_get_found() override;
	virtual void P_set_found ( bool a) override; 

	
	private : 
	bool plein;
};


class Transport : public Robot
{
	public:
	Transport (	int id,double par,double x_1,double y_1,double x3,double y3,string a,
				string r);
	Robot* copie()  ;
	~Transport();
	void mode_autonome( Gisement* C ) override;
	void mode_remote ( Gisement* C );
	
	virtual double P_get_xg () override;
	virtual double P_get_yg () override;
	virtual double P_get_taille () override;
	virtual double P_get_capacite () override;
	virtual bool P_get_found() override;
	virtual void P_set_found (bool a ) override; 
	
	private :

};


class Communication : public Robot
{
	public:
	Communication (	int id,double par,double x_1,double y_1 , double x3,double y3,
					string a); 
	Robot* copie() ;
	~Communication();
	void mode_autonome( Gisement* C ) override;
	void mode_remote ( Gisement* C ) override; 
	
	virtual double P_get_xg () override;
	virtual double P_get_yg () override;
	virtual double P_get_taille () override;
	virtual double P_get_capacite () override;
	virtual bool P_get_found() override;
	virtual void P_set_found ( bool a ) override; 
	
	private :
};

#endif
