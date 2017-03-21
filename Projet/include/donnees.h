#ifndef JAPH_DONNEES
#define JAPH_DONNEES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regroupement.h"

#include <string>
#include <iostream>

class donnees
{
  public:
    donnees(std::string file);
    ~donnees();
    std::vector<regroupement> generer_regroupements() const;
    unsigned int distance( std::vector<unsigned int> lieux ) const;
    unsigned int nblieux() const { return nblieux_; }
    unsigned int capacite() const { return capacite_; }
    unsigned int distancier(unsigned int x,unsigned int y) const {return C_[x][y];}
    unsigned int demande(unsigned int x) const {return demande[x];}

  private:
    void init_distance(regroupement& rgrp) const;
    
	unsigned int nblieux_; /* Nombre de lieux (incluant le dépôt) */
	unsigned int capacite_; /* Capacité du véhicule de livraison */
	unsigned int *demande_; /* Demande de chaque lieu (la case 0 est inutilisée car le dépôt n'a aucune demande à voir satisfaire) */
	unsigned int **C_; /* distancier (les lignes et colonnes 0 correspondent au dépôt) */
};

std::ostream& operator<<(std::ostream& os, donnees const& datas);

#endif//JAPH_DONNEES
