// simulation.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include <sstream>
#include <fstream>
#include "simulation.h"

using namespace std;


namespace{
	enum Etat_lecture {	NB_GISEMENT,GISEMENTS,NB_BASE,BASE,DEF,
						ROBOTP,ROBOTF,ROBOTT,ROBOTC,FIN};
	
	static int count(0);
	static int etat1(NB_GISEMENT), etat2(NB_BASE);
/***	static vector < Gisement* > liste_gisement; 
	static vector < Base* > liste_base;
	vector < Robot* > total_robots;***/
	
};

Simulation::Simulation(){}

Simulation::~Simulation(){
	for (size_t i = 0; i < liste_base.size(); i++)
	{
		effacer(liste_base[i]);
		delete liste_gisement[i];
	}
	}

void Simulation::lecture(char* nom)
{
	set_max(dim_max);
    string line;
    ifstream fichier(nom); 
    if(fichier.fail()) exit(EXIT_FAILURE);
   
	while(getline(fichier >> ws,line)) 
       {
		// ligne de commentaire à ignorer, on passe à la suivante
		if(line[0]=='#')  continue; 
		decodage_ligne1(line);
		//cout<<base_size()<<endl;
        }
    //Verification que toutes les bases ont un robot de comm au centre
    for (size_t i(0); i<liste_base.size(); i++){
		liste_base[i] -> robot_comm(liste_base);
		
		cout<<"Nb de robots: "<<liste_base[0]->get_nb_robot()<<endl;
	
	for( size_t i (0); i<liste_gisement.size(); i++){
		cout<<get_gisement(i)->getCercleG().get_rayon()<<endl;
	}
	//Remises des etats a leur valeur initiales afin de permettre 
	//la lecture d'un deuxieme fichier
	etat1= NB_GISEMENT;
	etat2= NB_BASE;
	
	}
}

//Fonction qui definit l'etat du switch de l'automate de lecture
void Simulation::set_etat (	int& etat2, double nbP, double nbF, double nbT, double nbC, 
				double bases){
	switch(etat2){
		case BASE:
			if (nbP>0) etat2 = ROBOTP;
			else if (nbF>0) etat2 = ROBOTF;
			else if (nbT>0) etat2 = ROBOTT;
			else if (nbC>0)etat2 = ROBOTC;
			else etat2= BASE;
			break;
					
		case ROBOTP:
			if (nbF>0) etat2 = ROBOTF;
			else if (nbT>0) etat2 = ROBOTT;
			else if (nbC>0)etat2 = ROBOTC;
			else etat2 = BASE;
			break;
					
		
		case ROBOTT:
			if (nbC>0)etat2 = ROBOTC;
			else etat2 = BASE;
			break;
	
		case ROBOTF:
			if (nbT>0) etat2 = ROBOTT;
			else if (nbC>0)etat2 = ROBOTC;
			else etat2 = BASE;
			break;
		
		case ROBOTC:
			etat2 = BASE;
			break;
	}
}

//Automate de lecture pour les gisement
void Simulation::decodage_ligne1(string line){
	++count;
	istringstream data(line);
	static int nombre(0), g(0);	
	static double x(0), y(0) ,rayon(0) ,ressource(0);
	switch(etat1) {
		case NB_GISEMENT:
			data >> nombre;
			etat1=GISEMENTS;
			if (nombre == 0) etat1=DEF;
			break;
			
		case GISEMENTS:
			data>>x>>y>>rayon>>ressource;
			cout << x <<" "<< y <<endl;
			if (g<nombre) g++;
			ajout_gisement(new Gisement (x,y,rayon, ressource), liste_gisement);
			if (g==nombre) etat1=DEF;
			break;
			
		case DEF:
			//cout<<"Coucou"<<endl;
			g=0;
			nombre=0;
			decodage_ligne2(line);
			break;
	}
}

//Automate de lecture pour les bases et les robots
void Simulation::decodage_ligne2(string line){		
	
	istringstream data(line);
	static double x(0) ,y(0) ,ressource(0),nbP(0) , nbT(0), nbC(0), nbF(0), dp(0), uid(0), xb(0), yb(0),
				base(0),nb_robots(0), xg(0),yg(0),rayong(0),capaciteg(0),nombre(0);			
	static string atteint,retour,found;
	
		
	switch (etat2){
		case NB_BASE:
			data >> nombre;
			etat2= BASE;
			//cout<<"Nb base:"<<nombre<<endl;
			break;
		case BASE:
			if (base <=nombre){
				data>>x>>y>>ressource>>nbP>>nbF>>nbT>>nbC;
				cout << x << " "<< y<< " "<< ressource<< " "<<nbP<<" "<<nbF<<" "<<nbT<<" "<< nbC<<endl; 
				ajout_base( new Base (x,y,ressource,nbP,nbF, nbT,nbC) , liste_base , liste_gisement);
				if (nbC == 0) {
					cout<<message::missing_robot_communication(	liste_base[base] -> get_x(),
																liste_base[base] -> get_y());
					exit(EXIT_FAILURE);
				}
				set_etat(etat2, nbP, nbF, nbT, nbC,base);
				nb_robots=0;
				++base;
				} 
			else break;
			break;
			
		case ROBOTP:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>retour>>found;
			
			cout<<uid<<" "<<dp<<"  "<<x<<" "<<y<<"  "<<xb<<"  "<<yb<< " " << atteint <<endl;
			if (found =="false") { 
				liste_base[base-1] -> ajout_robot(new Prospecteur(uid,dp,x,y,xb,yb,
															atteint,retour, found));}		
			else { 
				data>>xg>>yg>>rayong>>capaciteg;
				liste_base[base-1] -> ajout_robot(new Prospecteur(uid,dp,x,y,xb,yb,atteint,
															retour,found,xg,yg,rayong,
															capaciteg));}
			if (nb_robots+1==nbP) {
				set_etat(etat2, nbP, nbF, nbT, nbC,base);			
				nb_robots=0;
				break;} 
			nb_robots++;
			break;
			
		case ROBOTF:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
			cout<<uid<<" "<<dp<<"  "<<x<<" "<<y<<"  "<<xb<<"  "<<yb<< " " << atteint << endl;
			liste_base[base-1] -> ajout_robot(new Forage(uid, dp,x,y,xb,yb,atteint));
			if (nb_robots+1==nbF) {
				nb_robots=0;
				set_etat(etat2, nbP, nbF, nbT, nbC,base);
				break;}
			else nb_robots++;
			break;
	
		case ROBOTT:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint>>retour;
			cout<<uid<<" "<<dp<<"  "<<x<<" "<<y<<"  "<<xb<<"  "<<yb<< " " << atteint <<endl;
			liste_base[base-1] -> ajout_robot(new Transport(uid,dp,x,y,xb,yb,atteint,retour));
			if (nb_robots+1==nbT) {
				nb_robots=0;
				set_etat(etat2, nbP, nbF, nbT, nbC,base);			
				break;}
			 else  nb_robots++;
			break;
			
		case ROBOTC:
			data>>uid>>dp>>x>>y>>xb>>yb>>atteint;
			cout<<uid<<" "<<dp<<"  "<<x<<" "<<y<<" "<<xb<<"  "<<yb<<" " << atteint <<endl;
			liste_base[base-1] -> ajout_robot(new Communication(uid,dp,x,y,xb,yb,atteint));
			if (nb_robots+1==nbC) {
				set_etat(etat2, nbP, nbF, nbT, nbC,base);
				nb_robots=0;
				base=0;				
				break;}
			else nb_robots++;
			break;
	}		
	
}
/**
void effacer(){
		for (auto gisement : liste_gisement) delete gisement;
		liste_gisement.clear();
		
		for (auto base : liste_base) delete base;
		liste_base.clear();
		count=0;
}**/

Gisement* Simulation::get_gisement(int i){
	return liste_gisement[i];
}

Base* Simulation::get_base(int i){
	return liste_base[i];
}

size_t Simulation::gisement_size(){
	return liste_gisement.size();
}

size_t Simulation::base_size(){
	return liste_base.size();
}



void Simulation :: TabRobotsConnectBases( Base* A )
{


			rec_DEF(A ,  A -> robot_communication[0]); // voir pour détail la fonction qui est dans base.h à la fin 
			
			for ( size_t i(0) ; i < A->robots_base.size() ; i++) 
			{
				cout << A->robots_base[i]-> get_uid() << " : " << A->robots_base[i]-> get_Connect() << endl; 
			}
}

void Simulation :: TabTotalRobot () 
{
for ( size_t i(0) ; i < liste_base.size() ; i++ ) 
	{
		for (size_t j( 0) ; j < liste_base[i] -> robots_base.size() ; j++ ) 
		{ 
		total_robots.push_back( liste_base[i] -> robots_base[j] );  
		}
	}
}

void Simulation :: creation (Base* A) 																					// méthode création comme décrite dans simulation
{

for ( size_t i(0); i < A -> robots_base.size() ; i++ )																		 // fixer les coordonnées de la base pour tous les robots
	{
			A -> robots_base[i] -> set_base (  A-> get_x() , A -> get_y() );  
	}
	
	A -> TabRemoteOrAutonomous () ;																								// on forme les tableaux avec les robots connectés et les robots non connectés 
 																						// important de noter que la difference avec les robots 
			
	
	A -> MaJNbRobType();																									// ca vas mettre à jour le nombre de robots de chaque type dans la base


	A -> Creation4G(); 																						// On crée un tableau qui vas nous permettre d'établir notre stratégie -> un monde complètement connecté  
	A -> FindActive4G();																				// première chose voir si la 4G marche : la 4G est un réseau de robots de communication couvrant toute la planète et qui permet aisni de s'en assurer le control total
																										// Cette strategie est mise en place car le coût d'une telle constructin même si très faible est ridicule: de 48 ressources au total.  
																										// dès que la 4G est finie on passe le bool de active 4G à true et on peux lancer la recherche-

	
	if ( A -> get_4G() == false and A -> get_ressources() > 200. ) 																		// On decide si 4G ou recherche
	{										
		A -> launch4G_3_supplemetaires(); 																// Une fonction qui permet de construire par simulation au plus 3 robots qui peuvent s'ajouter à la 4G d'ou le choix de la boucle if ici, tant que la 4G dans son intégritée ne sera pas construite
																											// On ne lancera pas la recherche. Plus précisément le dernier tour on prendra les robots dont on a besoins et on finira la simulation
	}
	else if ( A -> get_nbP() < 10 and A -> get_ressources() > 300. )
	{	
		A -> lancement_p(); 			 																		// vas faire en sorte que l'on ait au moins 10 robots prospceteurs 
	}else{																																	
																													//On vas prendre les décisions et après les robots vont bouger;
																													// tout d'abord voir si il a de nouveaux gisements 
		for ( size_t j(0) ; j < A -> robots_connect.size() ; j++ ) 
		{
			if ( A->robots_connect[j] -> get_type() == 'P' and A -> robots_connect[j] -> P_get_found() == true ) 
			{
				A -> decision_interet_gisement ( A->robots_connect[j] -> P_get_xg() , A->robots_connect[j] -> P_get_yg() ,
												A->robots_connect[j] -> P_get_taille() , 
												A->robots_connect [j] -> P_get_capacite()) ; 
			}
		}
	}

		
}

void Simulation :: VideTabTotalConnectFalse ()
{
for ( size_t i(0)  ; i < total_robots.size() ; i ++ ) 
	{
		total_robots[i] -> set_Connect(false); 
	}
}


void Simulation :: maintenance_bases ( Base* A )
{
	 A -> maintenance (); 																				// il s'agit d'une fonction void d'ou le besoins de cette fonction de passage dans simulation
}


void Simulation :: update_autonomous ( Base* A )														 // on vas agir sur tous les robots d'une certaine base qui ne sont pas connectés 
{
		for ( size_t j(0) ; j < A -> robots_base.size() ; j++ )										// parcourir tout le tableau des robots qui ne sont pas connectés
		{
			for ( size_t i(0) ; i < liste_gisement.size() ; i++)										// on donne tous les gisements à tous les robots et si ils ont quelque chose à faire avec ils 
																										// agirons sinon ils ignorerons cet argument
			{
				if ( A-> robots_base[j] -> get_Connect() == false ) 
				{
					A -> robots_base[j] -> mode_autonome ( liste_gisement[i] );
				}											 					// le mode autonome est une méthode virtuelle avec une définition propre à chaque robot.
			}			
		}	
	
		
											
	/***																												// dès que la 4G est mise
	for ( size_t j(0) ; j < A -> robots_autonomous.size() ; j++ )										// parcourir tout le tableau des robots qui ne sont pas connectés
		{
			for ( size_t i(0) ; i < liste_gisement.size() ; i++)										// on donne tous les gisements à tous les robots et si ils ont quelque chose à faire avec ils 
																										// agirons sinon ils ignorerons cet argument
			{
					A -> robots_autonomous[j] -> mode_autonome ( liste_gisement[i] ); 					// le mode autonome est une méthode virtuelle avec une définition propre à chaque robot.
			}			
		}***/
	
}

void Simulation :: update_remote ( Base* A )
{
	for ( size_t j(0) ; j < A -> robots_base.size() ; j++ )										// parcourir tout le tableau des robots qui ne sont pas connectés
		{
			for ( size_t i(0) ; i < liste_gisement.size() ; i++)										// on donne tous les gisements à tous les robots et si ils ont quelque chose à faire avec ils 
																										// agirons sinon ils ignorerons cet argument
			{
				if ( A-> robots_base[j] -> get_Connect() == true ) 
				{
					A -> robots_base[j] -> mode_autonome ( liste_gisement[i] );
				}											 					// le mode autonome est une méthode virtuelle avec une définition propre à chaque robot.
			}			
		}	
	
	
	/***
		for ( size_t j(0) ; j < A -> robots_remote.size() ; j++ )										// parcourir tout le tableau des robots qui ne sont pas connectés
		{
			for ( size_t i(0) ; i < liste_gisement.size() ; i++)												// on donne tous les gisements à tous les robots et si ils ont quelque chose à faire avec ils 
																												// agirons sinon ils ignorerons cet argument
			{ 
					A -> robots_remote[j] -> mode_remote ( liste_gisement[i] ); 							// le mode autonome est une méthode virtuelle avec une définition propre à chaque robot.
			}			
		}***/
}


	


/**
void Simulation :: creation ()
{
	for ( size_t i(0) ; i < liste_base.size() ; i++ )  
	{
		if ( liste_base[i] -> get_4G() == false ) {
		liste_base[i] -> launch4G_3_supplemetaires ();
		} 	
	}
}
**/


void update_voisins ( Base* A , Base* B ) 																	// fonction responsable de la creation du tableau des 
{ 
	Vecteur V; 																								// vecteur pour calculer la norme entre les robots
	for ( size_t i (0) ; i < A -> robots_base.size() ; ++i ) 												// pour tous les robots de la Base à qui l'on souhaite établir le tableau des robots voisins aux voisins. 
		{
			A -> robots_base[i] -> robots_voisins.clear();													// Même si cela peut se montrer inutile dans certaines situations on vide le tableau avec tous les robots
																											// voisins histoire d'être bien sur que on n'en gagne pas un de trop 
														
			for ( size_t j (0) ; j < B -> robots_base.size() ; ++j )										// Ici on vas parcourir toute la base B sur laquelle il faut tester si les robots sont voisins de ce un robot i ou pas 
			{
				V.norme_vecteur( A -> robots_base[i] -> get_centre() , B -> robots_base[j]-> get_centre() ); 					// on calcule la distance entre le Robot [i] 
																																// de la base A et chaque Robot [j] de la 
																																//cout << "norme entre robots" << V.get_norme() << endl;																		 		// base B pour voir si ils sont distants de moins de 300m
				if ( V.get_norme() <= rayon_comm ) 																				// On regarde si la distance entre les deux robots est de moins de 300 mètres. 
				{
					if ( (V.egalite(A -> get_centre(), B -> get_centre()) == true) and ( A-> robots_base[i] -> get_uid() == B -> robots_base[j] -> get_uid() )) // cette boucle est pour assurer que l'on ne se prenne pas soit même comme voisins
																																								// Ainsi la condition critque à tester est: Est ce qu'il s'agit de la mênme base ?
																																								// dans quel cas le test d'égalité revoie true et pour assurer que l'on peut se prendre 
					{}else {																																    // des robots de la même base comme voisins on fait le test uid
						A -> robots_base[i] -> robots_voisins.push_back ( B->robots_base[j]-> copie()); 																	// donc si ces deux conditions finissent par être vraies on ne fait rien, sinon on ajoute 
					}																																			//le robot de la base B numéro [j]
				}
			}
		}
	 
	
}


void ajout_base ( Base* A , std::vector <Base*> & liste_base, 
							std::vector<Gisement*>& liste_gisement){

	bool intersection_base (false),intersection_gisement(false);
	int base(0),gisement(0);
	
	//Verification d'intersection base-gisement
	for ( size_t i (0); i < liste_gisement.size() ; i++ ){
		if (intersection_deux_cercles ( A -> get_cercle(), liste_gisement[i] -> getCercleG())){

				intersection_gisement = true; 
				gisement= static_cast<int>(i);
		}
	}
	for ( size_t i (0); i < liste_base.size() ; i++ )		{
		if (intersection_deux_cercles ( A -> get_cercle(), liste_base[i] -> get_cercle()))  {

				intersection_base = true; 
				base= static_cast<int>(i);			
		}		
	}
	//Verification d'intersection gisement-gisement		
	if (intersection_gisement==true){
		std::cout<<message::base_field_superposition(A -> get_x(), A -> get_y(),
													liste_gisement[gisement] -> get_x(),
													liste_gisement[gisement] -> get_y());
		exit ( EXIT_FAILURE );
	}
	else if (intersection_base==true){
		std::cout<<message::base_superposition(A -> get_x(), A-> get_y(),liste_base[base] -> get_x()
												,liste_base[base] -> get_y());
		exit ( EXIT_FAILURE );
	} 
	else if ( intersection_base == false) {
		liste_base.push_back( A );
	}
}




void Simulation :: effacer ( Base* A )
{
	for ( size_t i(0) ; i < liste_base.size() ; i++ ) 
	{
		if ( liste_base[i] -> get_ressources() <= 0 ) 
		{
			for ( size_t j(0) ; i< liste_base[i] -> robots_base.size(); j++ )
			{
				cout << " point critique pour éffacer " << endl; 
			delete liste_base[i] -> robots_base[j]; 
			}
		} 
	}
}
	
void Simulation :: verification (Base* A) 
{
	/***
	for ( size_t i(0) ; i < A -> robots_base.size() ; i++ ) 
		{

			cout << A->robots_base[i] -> get_uid()<< " " <<  A -> robots_base[i] -> get_Connect() <<endl;
			for ( size_t j(0) ; j < A -> robots_base[i] -> robots_voisins.size() ; j++ ) 
			{
				cout << "		" << A->robots_base[i] -> robots_voisins[j] -> get_uid() << "	" << A->robots_base[i] -> robots_voisins[j] -> get_type() << endl; 
			}  
		}
	for (size_t a (0) ; a < A -> robots_connect.size() ; a++ ) 
	{
		cout << A -> robots_connect[a] -> get_uid() << "	"<< A -> robots_connect[a] -> get_type() << endl; 
	}
	
	for (size_t a (0) ; a < A -> robots_autonomous.size() ; a++ ) 
	{
		cout << A -> robots_autonomous[a] -> getuid() << "	"<< A -> robots_connect[a] -> get_type() << endl; 
	}***/
	
}
void Simulation :: AffichageRobots () 
{
	for ( size_t j (0) ; j < total_robots.size() ; j++ )
	{
		//cout << total_robots[j]->get_uid() << "  " << total_robots[j]-> get_compteur_de_distance() << " " << total_robots[j]-> get_x() << " " 
		//	<< total_robots[j]-> get_y() << " " <<  total_robots[j]-> get_But().get_x() << " " << total_robots[j]-> get_But().get_y() << " " << total_robots[j]->get_atteint() << endl; 
	
	
	
	}
	
}
bool test () 
{return true; 
}





bool Simulation :: simulation ()
{

	
	TabTotalRobot();  																	 // je crée unb tableau avec tous les robots
																						// j'appelle en fin de simulation ou je fais la 
																						// boucle pour chaque base une fonction qui me met tous le bools connect à zéro de telle
																						// manière que la prochaine base ai une "fondation" propre  
						
	
																							//AffichageRobots(); 
	for ( size_t i(0) ; i < liste_base.size() ; i++ )
	{
		if ( liste_base[i] -> get_vie() )
		{ 
		 
			for ( size_t j(0) ; j < liste_base.size() ; j++) 
			{
			update_voisins ( liste_base[i] , liste_base[j] ); 								// je vais parcourir pour la base i et toutes les autres bases et les voir si elles ont des robots qui sont connectés avec la sienne. ( des commentaires sont inclus dans les fonctions )
			}
			
		
		cout << " affichage robots " << endl; 
		 
		TabRobotsConnectBases(liste_base[i]); 								 					 // une fonction qui crée les tableaux robots_connect qui est le tableau avec tous les robots connectés à la base 
		maintenance_bases(liste_base[i]);
		verification(liste_base[i]) ;

	
		cout << " accès robots " << endl; 
																									// fonction qui vas faire la maintenance de tous les robots on vas aussi en profiter pour vider tous les robots transporteurs comme ca on fixe la quantitée de ressources disponibles à chaque tour

		creation (liste_base[i]) ;																	// on vas créer la fonction qui vas construire les tableaux avec les robots_remote et les robots_autonomous. De plus on vas déterminer le nombre de Robots de chaque sorte et on vas fixer les coordonnées de la base pour tous les robots
		
		cout<< "robot base: "  <<liste_base[i]-> robots_base.size() << endl;
		cout<< "robot remote: " << liste_base[i]-> robots_remote.size() << endl;
		cout<< "robot autonomous: " << liste_base[i]-> robots_autonomous.size() << endl; 
		cout<< "robot de la base : " << liste_base[i] -> robot_communication.size() << endl; 
		
		
		for ( size_t k(0) ; k < 49 ; k++ ) 
		{
			cout << " x" << liste_base[i]->Monde4G[k][0] << " y " << liste_base[i]-> Monde4G[k][1] << " binaire " << liste_base[i]-> Monde4G[k][2] << endl; 
		}
		
		for ( size_t j (0) ; j < liste_base[i]->robots_remote.size() ; j++ ) 
		{
			cout << " xpos " << liste_base[i]-> robots_remote[j]-> get_centre().get_x()
			 << " ypos " <<  liste_base[i]-> robots_remote[j]->get_centre().get_y()
			 << "xbut: " << liste_base[i]-> robots_remote[j]->get_But().get_x()
			 << " ybut: " << liste_base[i]-> robots_remote[j]->get_But().get_y() 
			 << " atteint " << liste_base[i]-> robots_remote[j]->get_atteint() << endl; 
		}
/***		


	
																												/***for (size_t k(0) ; k < liste_base[i]->robots_connect.size() ; k++ ) 
																												{
																													cout << liste_base[i] -> robots_connect[k] -> get_type() << " "
																													 << liste_base[i] -> robots_connect[k] -> get_uid()
																													 << "	" << liste_base[i]->robots_connect[k]->get_atteint() 
																													<<  liste_base[i]->robots_connect[k] -> get_x() << " " << endl;   
																												}***/
																												
		
		cout << " mouvement des robots remote" << endl; 
		update_remote (liste_base[i]);																			// on vas dire aux robots non connectés d'accomplir leurs tâches de manière autonome
		
			cout << " mouvement des robots autonomous " << endl; 
		update_autonomous ( liste_base[i]); 																							// on vas s'intéresser aux robots connectés  
			cout << " fin algo " << endl;  
		}
	}
	
	/***
	for ( size_t i(0) ; i < liste_base.size() ; i++ ) 
	{
		effacer ( liste_base[i] ) ; 
	}
***/
return true;	
}












