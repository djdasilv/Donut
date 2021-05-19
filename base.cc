// base.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include "base.h"
#include "constantes.h"


void Base :: trouver_max_uid ()
{
	int id (0); 
	for ( size_t i (0); i < robots_base.size() ; i++ ) 
	{
		if ( robots_base[i] -> get_uid () > id ) 
		{
		id = robots_base[i] -> get_uid(); 
		}
	}
max_uid = id ; 
}



int Base::get_nb_robot() const {
	return robots_base.size();
}

Robot* Base :: get_robot(int i) const{
	return robots_base[i];
}

int Base::get_nbF() const{
	return nbF;
}

int Base::get_nbP() const {
	return nbP;
}

int Base::get_nbC() const {
	return nbC;
}

int Base::get_nbT() const {
	return nbT;
}

double Base :: get_nb_robot ()
{
	return robots_base.size(); 
} 

bool Base :: get_4G () 
{
	return Active4G; 
}

bool Base :: get_vie () 
{return vie;
}
void Base :: set_vie ( bool a )
{
	vie = a; 
}

Cercle Base::get_cercle () const 
{ 
	return position;
}

Base :: Base ( double x , double y ,  double r , int  P, int F , int T , int C )
{ 
	nbP =P; 
	nbF =F;
	nbT =T;
	nbC =C;
	position.set_centre (x, y);
	position.set_rayon(rayon_base);
	set_ressources (r); 
	
}

double Base::get_x() const{
	return get_cercle().get_centre().get_x();
	}
double Base::get_y() const{
	return get_cercle().get_centre().get_y();
}


double Base :: get_ressources () const
{
	return ressources; 
}

void Base :: set_ressources( double& ener )
{
	ressources = ener; 
}


Point Base::get_centre() const {
	return get_cercle().get_centre();
}

//Verification que au moins un robot comm est present dans la base

void Base :: robot_comm(vector <Base*> listeB) {
	
	bool presence_robotC(false);
	for (size_t i(0); i < robots_base.size(); i++)
	{
			if ( presence_robotC == false ) 
				{
				if (robots_base[i] -> get_type() == 'C'){
					Vecteur b;
					if (b.egalite(get_centre(), robots_base[i] -> get_centre()) == true and b.egalite(get_centre(), robots_base[i]-> get_But()) == true ){
						presence_robotC = true;
						robots_base[i] -> set_robot_base(true); 
						robot_communication.push_back( robots_base[i]  );
					}
				}
			}
	}
	if (presence_robotC == false) {
		cout<<"message::missing_robot_communication(get_x(),get_y())";
		exit(EXIT_FAILURE);
	}

}

//Fonction de ajout d'une base a la liste avec toutes les base




//Addition d'un robot a une base et verification de UIDs differents
void Base :: ajout_robot ( Robot* A)
{

	bool uid_egal (false);
	for ( size_t i (0) ; i < robots_base.size() ; i++ ) {
		if ( A -> get_uid() == robots_base[i] -> get_uid() ){
			uid_egal = true;
		}
	}
	if (uid_egal) {
			cout<<"message::identical_robot_uid(A -> get_uid())";
			exit(EXIT_FAILURE); 
	}
	
	robots_base.push_back( A );
}

/**
void Base :: maj_gisements_connus ()
{
	for ( size_t i (0) ; i < robots_base.size() ; i++ ) 
	{
		
	}
}
**/

int Base :: get_set_nv_max_uid ()
{
max_uid = max_uid+1;
return max_uid; 	
}

void Base :: Creation4G () // Cette fonction a pour but d'établir toutes les coordonnees nécessaires à occuper pour avoir un monde 
{						   // sous le control total de la 4G l'idée initiale était de construire la 4G pendant la recherche de gisements mais 
						   // mais pour des raisons de simplification d'algos nous nous sommes décidés à attendre la mise en place de la 4G 
						   // avant de passer au mode recherche. Cependant nous avons conserver ces coordonnées pour avoir l'ordre de formation de la 4G ceci 
						   // permet que au fur à mesure que la 4G se construit les robots communication restent connectés. ( les coordonnes forment des anneaux autour de la base)
						   // la troisième collone de la matrice est un code binaire pour indiquer la présence d'un robot de communication ou pas
	Monde4G ={
	position.get_x() + 0 * rayon_comm , position.get_y() + 0 * rayon_comm , 1 ,	//debut premier niveau
	position.get_x() + 1 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,	
	position.get_x() + 0 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,	//debut deuxieme niveau
	position.get_x() - 1 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 , // debut troisieme niveau 
	position.get_x() - 2 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() - 1 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() + 3 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() + 3 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() + 2 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() + 1 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() + 0 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,	
	position.get_x() - 1 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() - 2 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() - 3 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() - 2 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() - 1 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() + 0 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() + 1 * rayon_comm , 0 ,
	position.get_x() - 3 * rayon_comm , position.get_y() + 2 * rayon_comm , 0 ,
	0 , 0 , 1 , // compteur de robots de la 4G qui ont été créé ( inutile retrospectivement ) 
	};
	
	for ( size_t i(0); i < 49 ; i ++ ) // fonction très très importante, elle permet de normaliser les coordonnees 
									   // que l'on vient de trouver grace au passage par référence de la fonction dans geomod
	{
		normalisationGlobal( Monde4G[i][0] , Monde4G[i][1]); 
	}
}

Base :: ~Base ()
{ 
	 for(auto rob : robots_base) { 
		 delete rob;
	}	 
}

Base :: Base(const Base& other) 
	: nbP(other.nbP), nbF(other.nbF), nbT(other.nbT), nbC(other.nbC),
	position(other.position), ressources(other.ressources) 
{
	for (size_t i(0) ; i < robots_base.size() ; ++i) {
		robots_base.push_back((*(other.robots_base[i])).copie());
	}
	vie = true;
}

void Base :: maintenance () // en fait c'est rien d'autre que le compteurs des robots à zéro et prendre un coût pour cela. 
{
	Vecteur V; // Vecteur initialisé pour le calcul de la distance
	for ( size_t i (0) ; i < robots_base.size() ;  i++ ) // on vas prendre tous les robots de notre base car on veut éviter que
														 // l'on se mette à faire la maintenance pour "l'ennemi" 
	{
		if ( robots_base[i] -> get_Connect() ){ 		// cette condition est inutile et n'est la que pour faire en sorte que l'on s'arrête dès
														// le robot n'est pas à proximité, tout robot à qui on doit faire la maintenance devrait être connecté à la base 
			V.norme_vecteur ( position.get_centre() , robots_base[i] -> get_centre() ); // on fait un vecteur entre les deux pour trouver la norme et regarder si il est bien superposé à la base 
			if ( V.get_norme() == 0 ) 	// on check si il y a superposition 
			{							// si c'est le cas :
				if ( robots_base[i] -> get_compteur_de_distance() != 0) // pour savoir si il y besoins d'une maintenance sinon on crée les varibles suivantes pour rien mais c'est aussi inutile. 
				{
					double rep; // coût de réparation
					rep = robots_base[i]-> get_compteur_de_distance() * cost_repair; // calculé 
					double nv_qt = get_ressources() - rep ;	// on trouve la nouvelle qt de ressouces de la base 
					set_ressources ( nv_qt ); // on la fixe 
					double null (0);	
					robots_base[i]-> set_compteur_de_distance( null ) ; // mise à zéro du compteur de distance
				}
			}
		}	
	}
	
	ViderRobotsT(); // ici on ajoute en quelque sortes les ressources apportées par les robots le choix de cette construction aplusieurs raisons. 
					// La plus simple étant que cela nous permet de rentrer avec un quantitée de ressources déterminée dans le reste de la simulation
}

/**
void update_voisins ( Base* A , Base* B ) // fonction responsable de la creation du tableau des 
{ 
	Vecteur V; // vecteur pour calculer la norme entre les robots
	for ( size_t i (0) ; i < A -> robots_base.size() ; ++i ) // pour tous les robots de la Base à qui l'on souhaite établir le tableau des robots voisins aux voisins. 
		{
			A -> robots_base[i] -> robots_voisins.clear();	// Même si cela peut se montrer inutile dans certaines situations on vide le tableau avec tous les robots
															// voisins histoire d'être bien sur que on n'en gagne pas un de trop 
															
			for ( size_t j (0) ; j < B -> robots_base.size() ; ++j )		// Ici on vas parcourir toute la base B sur laquelle il faut tester si les robots sont voisins de ce un robot i ou pas 
			{
				V.norme_vecteur( A -> robots_base[i] -> get_centre() , B -> robots_base[j]-> get_centre() ); // on calcule la distance entre le Robot [i] 
																											 // de la base A et chaque Robot [j] de la 
																											 // base B pour voir si ils sont distants de moins de 300m
				if ( V.get_norme() <= rayon_comm ) 			// On regarde si la distance entre les deux robots est de moins de 300 mètres. 
				{
					if ( (V.egalite(A -> get_centre(), B -> get_centre()) == true) and ( A-> robots_base[i] -> get_uid() == B -> robots_base[j] -> get_uid() )) // cette boucle est pour assurer que l'on ne se prenne pas soit même comme voisins
																																								// Ainsi la condition critque à tester est: Est ce qu'il s'agit de la mênme base ?
																																								// dans quel cas le test d'égalité revoie true et pour assurer que l'on peut se prendre 
					{}else {																																    // des robots de la même base comme voisins on fait le test uid
						A -> robots_base[i] -> robots_voisins.push_back ( B->robots_base[j]); 																	// donc si ces deux conditions finissent par être vraies on ne fait rien, sinon on ajoute 
					}																																			//le robot de la base B numéro [j]
				}
			}
		}
	 
	
}
**/

/**void rec_DEF(Base* B  , Robot* A ) // fonction récurente qui construit le tableau du graphe de la base
{
A -> set_Connect( true );  	// si le robot A passe par cette fonction c'est qu'il est connecté à la base d'ou le besoins de mettre son connect à true 
B -> robots_connect.push_back( A ); // on ajoute ce robot au tableau avec tous les robots connectés 	
for ( size_t j(0) ; j < A -> robots_voisins.size() ; j++ ) // on parcourt tous les robots voisins du robot qui est connecté car alors ces derniers le sont aussi 
	{											
		if( A -> robots_voisins[j] -> get_Connect() == false )		 // ici on vérifie que le robot n'a pas déjà été visité et n'a donc pas été inclus.
		{
		rec_DEF( B , A -> robots_voisins[j]); // appel à la fonction récurente pour ce robot
		}		
	}
}
	**/
	
	
/**	
void Base :: launch4G_3_supplemetaires () // faut que je la revoie; 
{
	if ( Monde4G[50][0] < 50){
		for ( int i (0) ; i < 3 ; i++ ) 
		{
			double x7 = Monde4G[(Monde4G[50][0])][0];
			double y7 = Monde4G[(Monde4G[50][0])][1];
			Monde4G[50][0]= Monde4G[50][0] + 1;
			robots_base.push_back(new Communication ( Monde4G[50][0] , 0 , Monde4G[0][0] , Monde4G[0][1] , x7 , y7 , "false" ));   
		} 
	}else{
	Active4G = true; 
	}
}
**/

void Base :: launch4G_3_supplemetaires () // envoi au plus 3 nouveaux robots dans la 4G
{
	int i (0); 		// compteurs de robots lancés ( rappel au plus 3 )
	int static j (0);		// vas compter les lignes de la matrice du Monde4G quer l'on vas parcourir
					// on parcourir la le tableau des coordonnes jusuq'à trouver un couple de coordonnees qui n'est pas occupé par un robot de comm et si tel est le cas on s'emprèsse
					// de lui en attribuer un	
													
		do {	
			if ( Monde4G[j][2] == 0 )  // on regarde la condition qui est : est ce que il n'y a pas de robot attribué donc est ce que Monde[j][2] == 0 d'après le code bianire mis en place 
			{
				double x7 = Monde4G[j][0];		// si il y a besoins on vas chercher ses coordonnées
				double y7 = Monde4G[j][1];
				robots_base.push_back(new Communication ( get_set_nv_max_uid() , 0 , Monde4G[0][0] , Monde4G[0][1] , x7 , y7 , "false" )); // on initialise le nouveau robot de communication
																																		// get_set_nv_max_uid donne la première plus grande udi disponible
				i = i + 1;																												// on incrémente de un le compteur de robots 				
//				Monde4G[j][2] = 1; 																										// on indique que la position de la 4G est prise
				ressources = ressources - cost_com ; 																					// on fixe la nouvelle variation de ressources
			}
			j = j + 1; 																													// On incrémente la colonne à check
	} while ( i < 3 and j < 49 ); 																										// les deux conditions qui déterminent de la continuité de la fonction
																																		// il faut bien mettre and parce que on ne peut que continuer 
																																		// si les deux conditions sont respectées 
	
	if ( i == 0 )													// seulement si il n'y a pas eu besoins de créer de nouveaux robots on peut affirmer que la 4G est établie
	{
		Active4G = true; 											// on passe la 4G alors à true 
	}
}


bool Base :: decision_interet_gisement ( double x , double y , double r , double c )
{
	Vecteur V; 
	Point P ; 
	P.set_coordonnes( x ,y ); 
	V.norme_vecteur( P , get_centre() ); 
	double reste = fmod ( c , deltaR ); 
	double passages = (c-reste)/deltaR; 
	double cout_gisement = cost_forage + cost_transp + ( V.get_norme() - r ) * cost_repair * passages * 2 ;  
	if ( c > cout_gisement) {
	return true; 
	}else {
	return false; 
	}	
}


void Base :: commande_gisement () {
	for ( size_t i (0); i < robots_connect.size() ; i++) 
	{
		if ( robots_connect[i] -> get_type() == 'P' ) 
		{
			if ( robots_connect[i]-> P_get_found() == true )
			{
				if (decision_interet_gisement( robots_connect[i]-> P_get_xg() , robots_connect[i]-> P_get_yg() , robots_connect[i]-> P_get_taille() , robots_connect[i]-> P_get_capacite()) )
				{
					robots_base.push_back( new Forage ( get_set_nv_max_uid() , 0 , get_x() ,  get_y() , robots_connect[i]-> P_get_xg() , robots_connect[i]-> P_get_yg() , "false" )); // il faut encore faire en sorte qu'elle s'arrete au moment ou on est au bord du gisement. 
					ressources = ressources - cost_forage; 
					robots_base.push_back( new Transport ( get_set_nv_max_uid() , 0 , get_x() ,  get_y() , robots_connect[i]-> P_get_xg() , robots_connect[i]-> P_get_yg() , "false" , "false" )); 
					ressources = ressources - cost_transp;
					robots_connect[i] -> set_retour ( false) ;
					robots_connect[i] -> P_set_found ( false ) ; 
					robots_connect[i] -> set_but ( robots_connect[i] -> get_centre() );			
				}
			}
		}
	}	
}

void Base :: FindActive4G ()
{
	for ( size_t i (0) ; i < 49; i++ ) // on vas parcourir chaque case du tableau 
	{
		for ( size_t j(0) ; j < robots_remote.size() ; j++ ) 
		{
			if ( robots_remote[j] -> get_type() == 'C' ) 
			{
				if (  Monde4G[i][0] == robots_remote[j] -> get_But().get_x() and Monde4G[i][1] == robots_remote[j] -> get_But().get_y()) 
				{
					Monde4G[i][2] = 1;
				}
			}
		}
	}
}


void Base :: MaJNbRobType () // appelée lors de l'étape de création d 
{
	nbF = 0;
	nbP = 0;
	nbC = 0;
	nbT = 0;
	cout << robots_base.size() << endl;
	for( size_t i(0) ; i < robots_base.size() ; i++ ) // on parcourt tous les robots de la base et en fonction de son type on incrémente de 1 un certain nombre 
	{

		if ( robots_base[i] -> get_type() == 'F' ) 
		{ 
			nbF = nbF + 1 ; 
		}
		else if  ( robots_base[i] -> get_type() == 'P' )
		{ 
			nbP = nbP + 1 ;
		}
		else if  ( robots_base[i] -> get_type() == 'C' ) 
		{ 
			nbC = nbC + 1 ; 
		}
		else if ( robots_base[i] -> get_type() == 'T' ) 
		{ 
			nbT = nbT + 1 ; 
		}
	} 
}



void Base :: ViderRobotsT ()
{
	Vecteur V ; 
	for ( size_t i (0) ; i < robots_base.size() ; i++) 
	{
		V.norme_vecteur ( robots_base[i]->get_centre() , position.get_centre() ) ; // qu'il soit à la base 
		if ( V.get_norme() == 0 and robots_base[i] -> get_type() == 'T' and robots_base[i] -> get_retour() == true )  		// que ca soit un robot de transport de retour d'un gisement 
		{
			ressources = ressources + deltaR; 
			robots_base[i]-> set_retour(false); 
			robots_base[i]-> set_but ( GisementPlusLoin() ); 
		}
	}
} 



Point Base :: GisementPlusLoin () 
{
	Vecteur V; 
	Point P; 
	double d_g_max (0); 
	for ( size_t i(0) ; i < robots_base.size() ; i++ )
	{
		if ( robots_base[i] -> get_type() == 'F' and robots_base[i] -> P_get_found() == true  ) // ici le P_get_found même si le nom est mal choisi renvoi l'état du gisement si il est plein ou pas
																								// ceci permet de le choisir comme un potentiel gisement ou pas  
		{ 
			if ( robots_base[i] -> get_Connect() )  {
				V.norme_vecteur( position.get_centre() , robots_base[i]-> get_centre() ); 
				if ( V.get_norme() >  d_g_max ) {
					P.set_coordonnes ( robots_base[i]-> get_centre().get_x() , robots_base[i]-> get_centre().get_y() );
					d_g_max = V.get_norme(); 
				}
			}
		}
	}
	return P; 
}

void Base :: TabRemoteOrAutonomous(){
	
	cout << robots_base.size() << "nb de robots" << endl; 
	robots_remote.clear();
	robots_autonomous.clear();
	for ( size_t i(0) ; i < robots_base.size() ; i++ )
	{
		if ( robots_base[i] -> get_Connect() == true) 
		{
			robots_remote.push_back(robots_base[i] -> copie());
		} else {
			robots_autonomous.push_back(robots_base[i] -> copie());
		}
	} 
}


void Base :: lancement_p()
{
	int i(0); 
	do{
		robots_base.push_back(new Prospecteur ( get_set_nv_max_uid() , 0 , position.get_x() , position.get_y() , position.get_x() + 10 , position.get_y() + 10 , "false" , "false" , "false" , 0 , 0 , 0 , 0 ));
		nbP = nbP + 1; // dès que le robot a atteint son but il devrait partir au hasard quelque part 
		i = i + 3; 
		ressources = ressources - cost_prosp ; 
	} while ( i < 3 and nbP < 10) ;
}


void rec_DEF(Base* B ,  Robot* A ) 													// fonction récurente qui construit le tableau du graphe de la base
{
	for ( size_t i (0) ; i < B -> robots_base.size() ; i++ ) 
	{
		if ( B -> robots_base[i] -> get_uid() == A -> get_uid() ) 			// on trouve dans le tableau de la base le pointeur du robot traité et on le met à true 
		{
			B -> robots_base[i]-> set_Connect ( true ) ; 
		}
	}

																					// si le robot A passe par cette fonction c'est qu'il est connecté à la base d'ou le besoins de mettre son connect à true 
																				//robots_connect.push_back( A -> copie ()); 			// on ajoute ce robot au tableau avec tous les robots connectés 	
	for ( size_t j(0) ; j < A -> robots_voisins.size() ; j++ ) 							
	{
		for ( size_t i (0) ; i < B -> robots_base.size() ; i++ ) 
			{
				if ( B -> robots_base[i] -> get_uid() == A ->robots_voisins[j] ->get_uid() and B-> robots_base[i] -> get_Connect() == false) 									// on trouve le robot voisin dans le tableau des robots de base 
	
					{																																											//if( A-> robots_voisins[j] -> get_Connect() == false )		 							// ici on vérifie que le robot n'a pas déjà été visité et n'a donc pas été inclus.
																																		//{
					cout << "uid du robot connecté" << B -> robots_base[i]-> get_uid() << endl;  
					rec_DEF( B , B-> robots_base[i] ); // appel à la fonction récurente pour ce robot
					}
			}		
				
	}
}









