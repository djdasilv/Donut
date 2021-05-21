// robot.cc
// Auteurs : Georg Schwabedal et Daniel Silva
#include "robot.h"

using namespace std;

//=========================================================Robot-biblio get set========================================================================================================


Robot::Robot ( 	int id , double p , double x , double y , double x1 , double y1, 
					std::string at) {
	pos.set_coordonnes(x,y);
	uid=id;
	but.set_coordonnes(x1 ,y1 ); 
	compteur_de_distance=0;
	if (at == "true" ) atteint= true;
	else atteint = false;
	//Connect = false;  
	
}

bool Robot :: get_atteint () 
{
	return atteint; 
}

double Robot::get_x() const{
	return get_centre().get_x();
}

double Robot::get_y() const {
	return get_centre().get_y();
}

void Robot :: set_jus ( bool b ){
jus = b ; 	
}

bool Robot ::  get_jus () {
return jus; 	 
}

Robot* Robot::get_voisin(int i) const{
	return robots_voisins[i];}

int Robot::voisin_size()const{
	return robots_voisins.size();
}
void Robot :: set_base ( double xb , double yb )
{
	x_base = xb; 
	y_base = yb;
}



void Robot :: rentrer_base ()
{
	but.set_coordonnes ( x_base , y_base ); 
	retour = true; 
	atteint = false;
}

int Robot :: get_uid () const	{
	return uid;
}
	
void Robot :: set_Connect( bool a )
{
	Connect = a; 	
}

bool Robot :: get_Comm_Base ()  const 
{
	return robot_base; 
}

bool Robot :: get_Connect ()
{
	return Connect; 
}

bool Robot :: transformationStringBool ( std::string A ){
	
	if ( A == "true" or A == " true " or A == "true " or A == " true" ) {
		return true; 
	}
	else{
		return false; 
	}
}
	
Point Robot :: get_But() const{
	return but; 
}
	
void Robot :: set_but ( double x3 , double y3){
	but.set_coordonnes ( x3 , y3 );  
}

void Robot :: set_but ( Point A )
{
	but.set_coordonnes ( A.get_x() , A.get_y() ); 
}
	
	
void Robot ::  set_compteur_de_distance ( double dp ) {
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


char Robot :: get_type() {
return type; 
}

bool Robot :: get_retour() {
return retour; 
}

void Robot :: set_retour( bool a ) {
retour = a ; 	
}
Robot :: ~Robot() {}

//=========================================================Prospecteur=====================================================================================================================

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
}


Robot* Prospecteur ::  copie()  {
	return new Prospecteur(*this);
}
	
Prospecteur :: ~ Prospecteur() {}



void Prospecteur :: mode_remote ( vector < Robot* >& rob ,vector < Gisement* > tabg )										// on vas faire cycler tous les gisements voir si il y est 
{																						
	Vecteur V;
																								//	cout << " mode remote P atteint " << endl; 
	if ( found == false ) 																			// on regarde si le robot de prospection n'a pas déjà trouve un gisement. En effet on veut qu'il cherche à chaque simulation
																									// même sur le chemin du retour comme la maintenance est gratuite  
	{ 	
		for ( size_t i (0); i < tabg.size() ; i++ ) 
		 {																														 // plutôt faire ces checks avant une instance plus haut comme ca aucune de nos fonctions autonomous n'admet d'arguments
			V.norme_vecteur( tabg[i] -> getCercleG().get_centre() , pos ); 	 													// check pour l'intersection avec un gisement et vérifie qu'il ne soit pas vide
			if( tabg[i] -> getCercleG().get_rayon() > V.get_norme() and tabg[i] -> get_qt_resources() > deltaR ) 					// on vérifie qu'il ne soit pas vide ou au moins qu'il y ait un forage et on laisse la prise de décision à la base 
				{ 
					// mettre un bool de presence de robot de forage dans les voisins ici pour ignorer le gisement au bseoins
					found = true;																										// on indique que l'on a trouvé un Gisement					
					xg = tabg[i] -> getCercleG().get_x();																				// on mémorise ses données 
					yg = tabg[i] -> getCercleG().get_y();
					taille = tabg[i] -> getCercleG().get_rayon();
					capacite = tabg[i] -> get_qt_resources();
					rentrer_base();																										// on ordonne au robot de rentrer
				} 
		}	
	}
	 
	if ( found == false ) 																												// si on n'a pas trouvé de gisement ca implique que le found est false 
	{ 
		Point P ;
		P.set_coordonnes ( x_base , y_base ) ; 
		V.norme_vecteur ( pos , P );  																									// on calcule la distance à la base 
		if ( (maxD_prosp - compteur_de_distance - 2* deltaD) < V.get_norme() ) 															 // on ajoute les deltaD pour être sur que le robot rentre bien à temps même et donner de la marge
		{
			retour = true;  																											// indique que le robot doit rentrer 
			rentrer_base(); 																											// ordre donné 
			
		}
		else if ( atteint == true )
		{ 																										// on crée de nouvelles coordonnes au piff si jamais on est arrivé à notre destination
				int signe = randomNb ( 4 ); 																								// on crée une variable qui vas decider de la combinaison de notre but, ++ , -+ , +- ou -- 
				double alleX = randomNb ( 1000 );																							 // les deux variables qui vont prendre des coordonnées dans le monde au hasard 
				double alleY = randomNb ( 1000 );  
				
				if ( signe == 1 ) // on donne les 4 cas du signe 
				{
				but.set_coordonnes( alleX , alleY );
				}else if ( signe == 2) 
				{
				but.set_coordonnes(  alleX , - alleY );
				}else if ( signe == 3) 
				{
				but.set_coordonnes(  - alleX , alleY );
				}else if ( signe == 4) 
				{
				but.set_coordonnes(  - alleX , - alleY );
				}
				atteint = false; 
		} // utiliser la fonction random pour générer deux coordonnées alléatoires et yalla. Je l'ai fait mtn de telle manière qu'il prend 2 chiffres au hasard entre 0 et 1000 et on a un chiffre signe qui dit si on fait ++ +- -+ --
	}	  // il faut absolument revoir la fonction je sais pas si elle marche 
	
	deplacement_vers_but();
}

void Prospecteur :: mode_autonome(vector < Robot* >& rob , vector < Gisement* > tabg){ 												// ici aussi le propsecteur ne change rien dans son mode remote que dans son mode connecté, on a uniquement l'avantage que l'on connait à tout 
																											// moment ce qu'il sait
Vecteur V; 


if ( (maxD_prosp - compteur_de_distance - 2* deltaD) < V.get_norme() )  									// on ajoute les deltaD pour être sur que le robot rentre bien à temps même et donner de la marge
		{
			retour = true;  																				// indique que le robot doit rentrer 
			rentrer_base(); 																				// ordre donné 
			
		}

if ( atteint == true and retour == false and found == false ) {
																					// on ne peut que rechercher si on atteint notre but
		for ( size_t i (0); i < tabg.size() ; i++ )																				// on regarde si le robot de prospection n'a pas déjà trouve un gisement. En effet on veut qu'il cherche à chaque simulation																											// même sur le chemin du retour comme la maintenance est gratuite  
		{ 																 									// plutôt faire ces checks avant une instance plus haut comme ca aucune de nos fonctions autonomous n'admet d'arguments
			V.norme_vecteur( tabg[i] -> getCercleG().get_centre() , pos ); 	 									// check pour l'intersection avec un gisement et vérifie qu'il ne soit pas vide
			if( tabg[i] -> getCercleG().get_rayon() < V.get_norme() and tabg[i] -> get_qt_resources() > deltaR ) 		// on vérifie qu'il ne soit pas vide ou au moins qu'il y ait un forage et on laisse la prise de décision à la base 
				{ 
					found = true;																			// on indique que l'on a trouvé un Gisement					
					xg = tabg[i]  -> getCercleG().get_x();															// on mémorise ses données 
					yg =  tabg[i] -> getCercleG().get_y();	
					taille = tabg[i]  -> getCercleG().get_rayon();
					capacite = tabg[i]  -> get_qt_resources();
					rentrer_base();																			// on ordonne au robot de rentrer
				} 
		}
	
	atteint = false;
	rentrer_base();	
	
}else{
deplacement_vers_but (); 									
}

}


// getter et setter pour bouriner 
void Prospecteur :: P_set_found ( bool a ) { found = a; }; 

void Prospecteur :: set_found ( bool i ){ found = i ; }
void Prospecteur :: set_xg ( double x1 ){ xg = x1 ; }
void Prospecteur :: set_yg ( double y1 ){ yg = y1 ; }
void Prospecteur :: set_taille( double t ){ taille = t ; } 
void Prospecteur :: set_capacite ( double c ){ capacite = c ; }
	
bool Prospecteur :: get_found () const { return found; } 

/***
double Prospecteur :: get_xg () const{ return xg ; }
double Prospecteur :: get_yg () const{ return yg ; }
double Prospecteur :: get_taille () const{ return taille ; }
double Prospecteur ::  get_capacite () const{ return capacite ; }
***/
	
double Prospecteur :: P_get_xg () { return xg; }
double Prospecteur :: P_get_yg () { return yg; }
double Prospecteur :: P_get_taille () { return taille ; }
double Prospecteur :: P_get_capacite () { return capacite ; }
bool Prospecteur :: P_get_found() { return found; }

void Prospecteur :: deplacement_vers_but () 
{
	if ( compteur_de_distance < maxD_prosp ) {
		double D, r, m; 
		Vecteur V; 
				V.norme_vecteur( pos , but );  
				D = V.get_norme();
				r = fmod( D , deltaD ); 
				m = ( D - r) / deltaD; 
			if ( D < deltaD ) {
				pos.set_coordonnes( but.get_x() , but.get_y() ); 
				atteint = true; 
				compteur_de_distance= compteur_de_distance + 5. ; 
			}else { 
				pos.set_coordonnes ( pos.get_x() + (V.get_vect_x()/m) , pos.get_y() + (V.get_vect_y()/m));
				compteur_de_distance = compteur_de_distance + 5. ; 
			}
			
			pos.normalisation(pos); 
	}
}

//=========================================================Forage====================================================================================

Forage :: Forage (	int id,double par,double x_1,double y_1,double x3,double y3,
						string a): Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'F';
	jus = true; 
}


void Forage :: GisementPlein ( Gisement*C ) 
{
	if( C-> get_qt_resources() < deltaR ){
	plein = false;
	}else{
	plein = true; 
	}
}


Robot* Forage::  copie() {
	return new Forage(*this);
}

Forage :: ~ Forage() {}

void Forage :: forage ( Gisement* A )
{ 
double d = A -> get_qt_resources() - deltaR ;  
A -> set_qt_ressources ( d );  				   												
} 

void Forage :: mode_autonome ( vector < Robot* >& rob ,vector < Gisement* > tabg ) 		
{	
	Vecteur V;  
	
	if ( atteint == false  )
	{
		deplacement_vers_but();
	} 
	else if ( atteint == true )
	{ 	
		for ( size_t j (0) ; j < tabg.size() ; j++ )
		{
			if( V.egalite( tabg[j] -> getCercleG().get_centre() , pos ) )														
			{ 	
				GisementPlein( tabg[j] );																						 
				if ( plein == true )																					
				{	
					for ( size_t i (0) ; i < robots_voisins.size() ; i++) 
					{
						bool fait (false); 																			
						if ( fait == false and robots_voisins[i] -> get_type() == 'T' and robots_voisins[i] -> get_retour() == false) 																																
						{  
								Vecteur D ; 
								if (D.egalite( pos , robots_voisins[i] -> get_centre() ) == true) 
								{	
									for ( size_t t (0) ; t < rob.size() ; t++ ) 
									{	
										if ( rob[t]-> get_uid() == 	robots_voisins[i] -> get_uid() ) 
										{											
											forage(tabg[j]);
											rob[i] -> set_retour ( true ) ; 																	
											rob[i] -> set_but( x_base , y_base );											
											fait = true;	
										}
									}																
								}
						}
					}
				}else {
				jus = false ; 
					for ( size_t i (0) ; i < robots_voisins.size() ; i++) 
					{ 																			
						if ( robots_voisins[i] -> get_type() == 'T' and robots_voisins[i] -> get_retour() == false) 																																
						{  
								Vecteur D ; 
								if (D.egalite( pos , robots_voisins[i] -> get_centre() ) == true) 
								{	
									for ( size_t t (0) ; t < rob.size() ; t++ ) 
									{	
										if ( rob[t]-> get_uid() == 	robots_voisins[i] -> get_uid() ) 
										{					
											rob[i] -> set_retour ( true ) ; 																	
											rob[i] -> set_but( x_base , y_base );												
										}
									}																
								}
						}
					}
					
				}
			}
		} 
	}
}

void Forage ::  mode_remote (vector < Robot* >& rob , vector < Gisement* > tabg){
 
	Vecteur V;  
	
	if ( atteint == false  )
	{
		deplacement_vers_but();
	} 
	else if ( atteint == true )
	{ 	
		for ( size_t j (0) ; j < tabg.size() ; j++ )
		{
			if( V.egalite( tabg[j] -> getCercleG().get_centre() , pos ) )														
			{ 	
				GisementPlein( tabg[j] );																						 
				if ( plein == true )																					
				{
					for ( size_t i (0) ; i < robots_voisins.size() ; i++) 
					{
						bool fait (false); 																			
						if ( fait == false and robots_voisins[i] -> get_type() == 'T' and robots_voisins[i] -> get_retour() == false) 																																
						{  
								Vecteur D ; 
								if (D.egalite( pos , robots_voisins[i] -> get_centre() ) == true) 
								{	
									for ( size_t t (0) ; t < rob.size() ; t++ ) 
									{	
										if ( rob[t]-> get_uid() == 	robots_voisins[i] -> get_uid() ) 
										{ 
											forage(tabg[j]);
											rob[t] -> set_retour ( true ) ; 																	
											rob[t] -> set_but( x_base , y_base ); 											
											fait = true;	
										}
									}																
								}
						}
					}
				}else {
					for ( size_t i (0) ; i < robots_voisins.size() ; i++) 
					{ 																			
						if ( robots_voisins[i] -> get_type() == 'T' and robots_voisins[i] -> get_retour() == false) 																																
						{  
							Vecteur D ; 
							if (D.egalite( pos , robots_voisins[i] -> get_centre() ) == true) 
							{	
								for ( size_t t (0) ; t < rob.size() ; t++ ) 
								{	
									if ( rob[t]-> get_uid() == 	robots_voisins[i] -> get_uid() ) 
									{					
										rob[i] -> set_retour ( true ) ; 																	
										rob[i] -> set_but( x_base , y_base );												
									}
								}																
							}
						}
					}
					
				}
			}
		} 
	}			
}

void Forage :: P_set_found ( bool a ) {}; 

double Forage :: P_get_xg () {return 0;}
double Forage :: P_get_yg () {return 0;}
double Forage :: P_get_taille () {return 0;}
double Forage :: P_get_capacite () {return 0;}
bool Forage :: P_get_found() {return plein;}

void Forage :: deplacement_vers_but () 
{
	if ( compteur_de_distance < maxD_forage ) {
		double D, r, m; 
		Vecteur V; 
				V.norme_vecteur( pos , but );  
				D = V.get_norme();
				r = fmod( D , deltaD ); 
				m = ( D - r) / deltaD; 
			if ( D < deltaD ) {
				pos.set_coordonnes( but.get_x() , but.get_y() ); 
				atteint = true; 
				compteur_de_distance= compteur_de_distance + r ; 
			}else { 
				pos.set_coordonnes ( pos.get_x() + (V.get_vect_x()/m) - (r/m), pos.get_y() + (V.get_vect_y()/m) - (r/m));
				compteur_de_distance = compteur_de_distance + 5. ; 
			}
			
			pos.normalisation(pos); 
	}
}


//=========================================================Transport====================================================================================

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

void Transport :: mode_autonome ( vector < Robot* >& rob ,vector < Gisement* > tabg)
{
	cout << " mode autonaume de T " << endl ; 
	Vecteur V;  
	V.norme_vecteur( pos , but ); 	// on trouve la norme 
	if ( V.get_norme() != 0 )		// on la renvoi 
		{
			deplacement_vers_but();		// on remarque ici que le robot de transport ressemble beaucoup au robot de communication
		}else{						// il ne fait que aller vers son but, son chargement est pris en charge par le robot de forage et 
			if (retour == true ){		// son but est fixé par le même robot ou par la base et si son but est atteint alors qu'il y reste jusqu'à nouvel ordre.
			 rentrer_base();
		}
	} 
}

void Transport ::  mode_remote ( vector < Robot* >& rob ,vector < Gisement* > tabg ){ //en soit le mode remote ne change rien du mode autonome car le robot de transport fait exactement la même chose qu'il soit connecté ou pas
	cout << " mode remote de T " << endl; 
	mode_autonome( rob , tabg );
	Vecteur V;  
	V.norme_vecteur( pos , but ); 	
	if ( V.get_norme() != 0 )		
		{
			deplacement_vers_but();		
		}else{						
			if (retour == true ){		
			 rentrer_base();
		}
	} 
	cout << " but x T : " << get_But().get_x() << " but y T : " << get_But().get_y() << endl;  
}


void Transport :: P_set_found ( bool a ) {}; 

double Transport :: P_get_xg () {return 0;}
double Transport :: P_get_yg () {return 0;}
double Transport :: P_get_taille () {return 0;}
double Transport :: P_get_capacite () {return 0;}
bool Transport :: P_get_found() {return true;}


void Transport :: deplacement_vers_but () 
{
	if ( compteur_de_distance < maxD_transp ) {
		double D, r, m; 
		Vecteur V; 
				V.norme_vecteur( pos , but );  
				D = V.get_norme();
				r = fmod( D , deltaD ); 
				m = ( D - r) / deltaD; 
			if ( D < deltaD ) {
				pos.set_coordonnes( but.get_x() , but.get_y() ); 
				atteint = true; 
				compteur_de_distance= compteur_de_distance + 5. ; 
			}else { 
				pos.set_coordonnes ( pos.get_x() + (V.get_vect_x()/m) , pos.get_y() + (V.get_vect_y()/m));
				compteur_de_distance = compteur_de_distance + 5. ; 
			}
			
			pos.normalisation(pos); 
	}
}

//=========================================================Communication====================================================================================
		
Communication :: Communication (int id,double par,double x_1,double y_1,double x3,
								double y3,std::string a)
								: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'C';
	if (a == "true" ) atteint= true;
	else atteint = false;

}

Robot* Communication ::  copie() {
	return new Communication(*this);
}

Communication :: ~Communication() {}

void Communication :: mode_autonome (vector < Robot* >& rob , vector < Gisement* > tabg )
{
	if ( atteint == false ) {															// relativement simple, si tu n'es pas immobile alors deplace toi vers le but sinon bouge pas et joue ton rôle de noeud. 
	deplacement_vers_but(); 															// ici on a affaire à un robot qui n'as rien à voir avec les gisements et tout simplement peut se permettre d'ignorer l'argument passé
	}
}

void Communication :: mode_remote (vector < Robot* >& rob , vector < Gisement* > tabg )		
{

	if ( atteint == false ) {			
	deplacement_vers_but(); 
	}

}

void Communication :: P_set_found ( bool a ) {}; 

double Communication :: P_get_xg () {return 0;}
double Communication :: P_get_yg () {return 0;}
double Communication :: P_get_taille () {return 0;}
double Communication :: P_get_capacite () {return 0;}
bool Communication :: P_get_found() {return false;}

void Communication :: deplacement_vers_but () 
{
	if ( compteur_de_distance < maxD_com ) {
		double D, r, m; 
		Vecteur V; 
				V.norme_vecteur( pos , but );  
				D = V.get_norme();
				r = fmod( D , deltaD ); 
				m = ( D - r) / deltaD; 
			if ( D < deltaD ) {
				pos.set_coordonnes( but.get_x() , but.get_y() ); 
				atteint = true; 
				compteur_de_distance= compteur_de_distance + 5. ; 
			}else { 
				pos.set_coordonnes ( pos.get_x() + (V.get_vect_x()/m) , pos.get_y() + (V.get_vect_y()/m));
				compteur_de_distance = compteur_de_distance + 5. ; 
			}
			
			pos.normalisation(pos); 
	}
}

//=========================================================Robot algos====================================================================================









