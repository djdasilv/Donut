#ifndef GEOMOD_H
#define GEOMOD_H
#include <array>
	
using namespace std;
		
	bool equal_zero (double verification);

	void set_max(double init_max);

	double get_max();

	double get_epsilon();

	double calculNormeVecteur(double x_1 , double y_1 , double x_2 , double y_2 ) ;

	
	class Point2D{
		public:
		
		void setCoordonnes(double x1 , double y1);
		double getX() ;
		double getY() ;
		void setCoordonnesEquivalentes ( int a , int b , double  c) ;
		void Normalisation(double x3,double y3);
		void Normalisation(Point2D D);
		void CoordonnesEquivalentes();
		double getEquivalent(int a, int b); // Accede au array "equivalent"
											// Elle est la pour que l'array "equivalent" puisse etre private
		
		private:
		array<array<double , 2 > , 9 > equivalent;
		double x; 
		double y;
	};


	class Vecteur{ 
		public: 
		double getNorme () const;
		double getVectX () const;
		double getVectY () const;
		void NormeVecteur(Point2D Depart, Point2D Arrive);
		bool egalite(Point2D A, Point2D B);
		
		
		private: 
		double x_depart;
		double y_depart;
		double x_arrive; 
		double y_arrive;
		double x_equivalent_arrive;	
		double y_equivalent_arrive; 
		double norme;
		double vecteurX;
		double vecteurY;
	};

	class Cercle{
		public:
		void setCentre(double x1, double x2);
		void setRayon(double R);
		Point2D getCentre();
		double getRayon();
		bool appartientCercle(Point2D Verificcation);
		
		
		private:
		Point2D centre; 
		double rayon;
	};


	bool IntersectionDeuxCercles(Cercle C_1, Cercle C_2);

#endif
