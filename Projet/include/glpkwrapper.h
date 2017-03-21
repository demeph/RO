#ifndef JAPH_GLPKWRAPPER
#define JAPH_GLPKWRAPPER

#include <vector>
#include <iostream>
#include "regroupement.h"
#include "probleme.h"
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */


class glpkwrapper
{
	public:
		//constructeur && deconstructeur
		glpkwrapper(unsigned int nbContr,const probleme & prob);
		~glpkwrapper() { delete ia;delete ja,delete ar;}

		void resoudre_probleme()

	private:
		// fonctions privées
		void construit_couts(std::vector<regroupement> & combinaison);
		void construit_pb();
		void construit_taille_contr(probleme prob);

		void def_probleme();

		//variables
		unsigned int nb_contr;
		unsigned int nb_var;
		int *couts;
		int *ia;
    	int *ja;
    	double *ar;
		const double droite_;
		int nb_creux;

		glp_prob *trumpland;
};

#endif //JAPH_GLPKWRAPPER