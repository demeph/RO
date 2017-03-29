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
    ~glpkwrapper();

    void resoudre_probleme();

    unsigned int nb_contr() const { return nb_contr_; }
    unsigned int nb_var() const { return nb_var_; }
    unsigned int nb_creux() const { return nb_creux_; }
    void afficher();
  private:
    // fonctions privées
    void construit_couts(const std::vector<regroupement> & combinaison);
    void construit_pb();
    void construit_taille_contr(probleme prob);

    void def_probleme();

    //variables
    unsigned int nb_contr_;
    unsigned int nb_var_;
    int *couts_;
    int *ia_;
    int *ja_;
    double *ar_;
    const int droite_;
    int nb_creux_;

    glp_prob *trumpland;
    const probleme& probleme_;
};

std::ostream & operator<<(std::ostream& os, glpkwrapper const& wrp);

#endif //JAPH_GLPKWRAPPER
