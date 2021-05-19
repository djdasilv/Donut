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
	//atteint =  transformationStringBool(at);
	//Connect = false;  
	atteint = false ; 
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
	
void Robot :: set_compteur_energie ( double& ener){
	compteur_energie = ener ; 
}
	
double Robot::  get_compteur_energie () const {
	return compteur_energie;
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



void Prospecteur :: mode_remote ( Gisement* C )					// on vas faire cycler tous les gisements voir si il y est 
{																						
	Vecteur V;
//	cout << " mode remote P atteint " << endl; 
	if ( found == false ) 											// on regarde si le robot de prospection n'a pas déjà trouve un gisement. En effet on veut qu'il cherche à chaque simulation
																	// même sur le chemin du retour comme la maintenance est gratuite  
	{ 																	 // plutôt faire ces checks avant une instance plus haut comme ca aucune de nos fonctions autonomous n'admet d'arguments
			V.norme_vecteur( C -> getCercleG().get_centre() , pos ); 	 // check pour l'intersection avec un gisement et vérifie qu'il ne soit pas vide
			if( C -> getCercleG().get_rayon() < V.get_norme() and C -> get_qt_resources() > deltaR ) // on vérifie qu'il ne soit pas vide ou au moins qu'il y ait un forage et on laisse la prise de décision à la base 
				{ 
					found = true;										// on indique que l'on a trouvé un Gisement					
					xg = C -> getCercleG().get_x();						// on mémorise ses données 
					yg = C-> getCercleG().get_y();
					taille = C -> getCercleG().get_rayon();
					capacite = C -> get_qt_resources();
					rentrer_base();										// on ordonne au robot de rentrer
				} 
	}
	 
	if ( found == false ) // si on n'a pas trouvé de gisement ca implique que le found est false 
	{ 
		V.norme_vecteur ( pos , but );  // on calcule la distance à la base 
		if ( (maxD_prosp - compteur_de_distance - 2* deltaD) < V.get_norme() )  // on ajoute les deltaD pour être sur que le robot rentre bien à temps même et donner de la marge
		{
			retour = true;  						// indique que le robot doit rentrer 
			rentrer_base(); 						// ordre donné 
			
		}else if ( atteint == true ){ // on crée de nouvelles coordonnes au piff si jamais on est arrivé à notre destination
				int signe = randomNb ( 4 ); // on crée une variable qui vas decider de la combinaison de notre but, ++ , -+ , +- ou -- 
				int alleX = randomNb ( 1000 ); // les deux variables qui vont prendre des coordonnées dans le monde au hasard 
				int alleY = randomNb ( 1000 );  
				
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
		} // utiliser la fonction random pour générer deux coordonnées alléatoires et yalla. Je l'ai fait mtn de telle manière qu'il prend 2 chiffres au hasard entre 0 et 1000 et on a un chiffre signe qui dit si on fait ++ +- -+ --
	}	  // il faut absolument revoir la fonction je sais pas si elle marche
	deplacement_vers_but();
}

void Prospecteur :: mode_autonome( Gisement* C ){ // ici aussi le propsecteur ne change rien dans son mode remote que dans son mode connecté, on a uniquement l'avantage que l'on connait à tout 
												// moment ce qu'il sait
Vecteur V; 


if ( (maxD_prosp - compteur_de_distance - 2* deltaD) < V.get_norme() )  // on ajoute les deltaD pour être sur que le robot rentre bien à temps même et donner de la marge
		{
			retour = true;  						// indique que le robot doit rentrer 
			rentrer_base(); 						// ordre donné 
			
		}
		
if ( atteint == true ) {						// on ne peut que rechercher si on atteint notre but
		if ( found == false ) 											// on regarde si le robot de prospection n'a pas déjà trouve un gisement. En effet on veut qu'il cherche à chaque simulation
																	// même sur le chemin du retour comme la maintenance est gratuite  
		{ 																 // plutôt faire ces checks avant une instance plus haut comme ca aucune de nos fonctions autonomous n'admet d'arguments
			V.norme_vecteur( C -> getCercleG().get_centre() , pos ); 	 // check pour l'intersection avec un gisement et vérifie qu'il ne soit pas vide
			if( C -> getCercleG().get_rayon() < V.get_norme() and C -> get_qt_resources() > deltaR ) // on vérifie qu'il ne soit pas vide ou au moins qu'il y ait un forage et on laisse la prise de décision à la base 
				{ 
					found = true;										// on indique que l'on a trouvé un Gisement					
					xg = C -> getCercleG().get_x();						// on mémorise ses données 
					yg = C-> getCercleG().get_y();
					taille = C -> getCercleG().get_rayon();
					capacite = C -> get_qt_resources();
					rentrer_base();										// on ordonne au robot de rentrer
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

//=========================================================Forage====================================================================================

Forage :: Forage (	int id,double par,double x_1,double y_1,double x3,double y3,
						string a): Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'F';
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
	double d = A -> get_qt_resources() - deltaR ;  	// prendre le gisement et déterminer sa nouvelle quantitée de ressources disponibles  
	A -> set_qt_ressources ( d );  				    // mettre à jour la qt de ressources dispo, le fait qu'il puisse supporter le prélèvement a été testé 
													// juste avant
} 

void Forage :: mode_autonome ( Gisement* C ) 	// on vas faire passer tous les gisements possible parce que sinon c'est trop compliqué 	
{	
		// on vas dans un premier temps dire que le robot vas partir vers le centre du gisement et pendant la boucle for on vas actualiser les coordonnes du but de telle manière qu'il s'arrête lors de l'arrivée au rayon 
		// de manière générale tant que ce robot n'a pas atteint le gisement il est supposé faire rien d'autre.
		 Vecteur V;  
	
		
	
	if ( atteint == false  )
	{
		deplacement_vers_but();
	} else if ( atteint == true ){ 		// en fait il faut créer ici la fonction qui appelle le robot de transport et switch son truc de retour à true pour le faire repartir
									// si son atteint est vrai alors ca implique qu'il devrait y avoir un robot autour, sauf si ce gisement a été détruit   
									// dès qu'il est arrivé il a le droit de faire quelque chose
										// Comme on est supposé il y avoir que un seul gisement dans les parages on est supposé 
		if( V.egalite( C -> getCercleG().get_centre() , pos ) )														// le trouver le reste vas sauter de la boucle
		{ 	
			GisementPlein( C );		// on vérifie que le gisement n'as pas été vidé par une autre base 
			if ( plein == true )	// on le met ici comme ca on sort plus tôt si le gisement est vide
			{	
				for ( size_t i (0) ; i < robots_voisins.size() ; i++) 
				{
						bool fait (false); // bool dit : est ce que un  chargement a été FAIT? 
						if ( fait == false and robots_voisins[i] -> get_type() == 'T') // le " fait " evite que l'on charge plusieurs fois par simulation dans le cas ou il y aurait plusieurs
																					   // robots de transport superposés 
																					   // les autres gisements ne sont pas gênants parce que l'on vas jamais les trouver
						{  
								Vecteur D ; 
								if (D.egalite( pos , robots_voisins[i] -> get_centre() ) == true and robots_voisins[i] -> get_type() == 'T') // si il y a un robot de TRANSPORT à proximité
								{			
									forage(C); 												// effectuer le forage du gisment 
									robots_voisins[i] -> set_retour(true);					// et dire au robot de transport de rentrer
									fait = true;											// et indiquer que le travail pour cette simulation a été fait 
								}
						}
				}
			}
		}
	} 
}

void Forage ::  mode_remote ( Gisement* C ){
//	cout << " mde remote F atteint " << endl; 
	mode_autonome ( C ) ;				// Ici aussi le mode remote ne change pas du mode autonomous, le robot vas vers son gisement et le tackle
}

void Forage :: P_set_found ( bool a ) {}; 

double Forage :: P_get_xg () {return 0;}
double Forage :: P_get_yg () {return 0;}
double Forage :: P_get_taille () {return 0;}
double Forage :: P_get_capacite () {return 0;}
bool Forage :: P_get_found() {return plein;}

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

void Transport :: mode_autonome ( Gisement* C )
{
	cout << " mde remote T atteint " << endl; 
	Vecteur V;  // on trouve un vecteur entre le robot et le but 
	V.norme_vecteur( pos , but ); 	// on trouve la norme 
	if ( V.get_norme() != 0 )		// on la renvoi 
	{
		deplacement_vers_but();		// on remarque ici que le robot de transport ressemble beaucoup au robot de communication
	/**}else{						// il ne fait que aller vers son but, son chargement est pris en charge par le robot de forage et 
		if (retour == true ){		// son but est fixé par le même robot ou par la base et si son but est atteint alors qu'il y reste jusqu'à nouvel ordre.
		 rentrer_base();
		}**/
	} 
}

void Transport ::  mode_remote ( Gisement* C ){ //en soit le mode remote ne change rien du mode autonome car le robot de transport fait exactement la même chose qu'il soit connecté ou pas
//	cout << " mde remote T atteint " << endl; 
	mode_autonome( C );
}


void Transport :: P_set_found ( bool a ) {}; 

double Transport :: P_get_xg () {return 0;}
double Transport :: P_get_yg () {return 0;}
double Transport :: P_get_taille () {return 0;}
double Transport :: P_get_capacite () {return 0;}
bool Transport :: P_get_found() {return true;}

// créer une fonction qui pour le robot vas check ses voisins, si il y en a un de forage vers qui la norme est nulle son bool plein est true, il est cependant impératif d'exécuter le robot de forage avant celui de transport

//=========================================================Communication====================================================================================
		
Communication :: Communication (int id,double par,double x_1,double y_1,double x3,
								double y3,std::string a)
								: Robot ( id , par , x_1 ,y_1 ,x3 , y3 , a) {
	type = 'C';
	//robot_base = false; 
}

Robot* Communication ::  copie() {
	return new Communication(*this);
}

Communication :: ~Communication() {}

void Communication :: mode_autonome ( Gisement* C )
{
	if ( atteint == false ) {			// relativement simple, si tu n'es pas immobile alors deplace toi vers le but sinon bouge pas et joue ton rôle de noeud. 
	deplacement_vers_but(); 			// ici on a affaire à un robot qui n'as rien à voir avec les gisements et tout simplement peut se permettre d'ignorer l'argument passé
	}
}

void Communication :: mode_remote ( Gisement* C )		
{
//	cout << " mde remote C atteint entrée" << atteint << endl; 
	if ( atteint == false ) {			// même chose que le remote 
	deplacement_vers_but(); 
	}
//	cout << " mde remote C atteint sortie" << endl; 
}

void Communication :: P_set_found ( bool a ) {}; 

double Communication :: P_get_xg () {return 0;}
double Communication :: P_get_yg () {return 0;}
double Communication :: P_get_taille () {return 0;}
double Communication :: P_get_capacite () {return 0;}
bool Communication :: P_get_found() {return true;}

//=========================================================Robot algos====================================================================================


void Robot :: deplacement_vers_but () 
{
double D, r, m; 
Vecteur V; 
		V.norme_vecteur( pos , but );  
		D = V.get_norme();
		r = fmod( D , deltaD ); 
		m = ( D - r) / deltaD; 
		cout << " deplacement à faire " << D << endl; 
	if ( D < deltaD ) {
		pos.set_coordonnes( but.get_x() , but.get_y() ); 
		atteint = true; 
	}else { 
		cout << " nouveaux x " << pos.get_x()   << "  nouveau y  " << pos.get_y()  << endl; 
		pos.set_coordonnes ( pos.get_x() + (V.get_vect_x()/m) , pos.get_y() + (V.get_vect_y()/m));
		cout << " xpos mis à jour" << pos.get_x() << " ypos mis à jour " << pos.get_y() << endl; 
	}
	
	pos.normalisation(pos); 
}
/***
void Robot::modifie_dp(Robot* rob)
{
	Point equi;
	double norme,deltax,deltay,alpha;
	equi=rob->get_centre().calc_vect(rob->get_but()).get_direction();
	deltax=equi.get_X()-rob->get_xr();
	deltay=equi.get_Y()-rob->get_yr();
	if(rob->get_centre().calc_vect(rob->get_but()).get_norme()>deltaD)
	{
		double xrob,yrob;
		xrob=rob->get_xr();
		yrob=rob->get_yr();
		if(deltax != 0 and deltay != 0)
		{
			alpha=atan((deltay)/(deltax));
			rob->set_xr(rob->get_xr()+(deltaD*cos(alpha)));
			rob->set_yr(rob->get_yr()+(deltaD*sin(alpha)));
			rob->set_dp(rob->get_dp()+5);
		}
		else
		{
			if(deltax==0)
			{
				if(equi.get_Y()>rob->get_yr())  rob->set_yr(rob->get_yr()+5);
				rob->set_yr(rob->get_yr()-5);
			}
			if(deltay==0)
			{
				if(equi.get_X()>rob->get_yr())  rob->set_yr(rob->get_xr()+5);
				rob->set_yr(rob->get_xr()-5);
			}
		}
	} 
	else
	{
		rob->set_dp(rob->get_dp()+norme);
		rob->set_but(rob->get_but().get_X(),rob->get_but().get_Y());
	}
	rob->get_centre().normaliser();
}

***/





