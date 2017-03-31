#include "donnees.h"
#include "container_overload.hpp"
#include <algorithm>//next_permutation

donnees::donnees(std::string file)
{
	unsigned int i,j;
	FILE *fin;
	
	unsigned int val;
	fin = fopen(file.c_str(), "rt");
	
	/* Lecture du nombre de villes */
	
	fscanf(fin,"%u",&val);
	nblieux_ = val;

	/* Allocation mémoire pour la demande de chaque ville, et le distancier */
	
	demande_ = (unsigned int *) malloc (nblieux_ * sizeof(int));
	C_ = (unsigned int **) malloc (nblieux_ * sizeof(int *));
	for(i = 0;i < nblieux_;i++) C_[i] = (unsigned int *) malloc (nblieux_ * sizeof(int));
	
	/* Lecture de la capacité */
	
	fscanf(fin,"%d",&val);
	capacite_ = val;
	
	/* Lecture des demandes des clients */
	
	for(i = 1; i < nblieux_; ++i)
	{
		fscanf(fin,"%d",&val);
		demande_[i] = val;
	}
	
	/* Lecture du distancier */

	for(i = 0; i < nblieux_; i++)
		for(j = 0; j < nblieux_; j++)
		{
			fscanf(fin,"%d",&val);
			C_[i][j] = val;
		}
		
	fclose(fin);
}

donnees::~donnees()
{
	unsigned int i;
	for(i = 0; i < nblieux_; ++i)
        free(C_[i]);
	free(C_);
	free(demande_);	
}

std::vector<regroupement> donnees::generer_regroupements() const
{
    std::vector<regroupement> result;

    for(unsigned int i = 1; i < nblieux_; ++i)//on parcours tous les points de pompage
        if(capacite_ >= demande_[i])//on teste quand même la capacité
            result.emplace_back( std::vector<unsigned int>{i}, demande_[i]);

    unsigned int start = 0;
    unsigned int stop = result.size();
    
    for(unsigned int stage = 2; stage < nblieux_; ++stage)
    {//génération des sous-ensembles de taille stage
        for(; start < stop; ++start)
        {//parcours de chacun des points de taille stage-1
            for(unsigned int i = result[start].dernier_point() + 1; i < nblieux_; ++i)
            {//création des result de préfixe result[start]
                if(result[start].quantite() + demande_[i] <= capacite_)
                {//filtrage. seuls les result dont la quantité d'eau est transportable sont ajoutés
                    result.push_back( result[start] );
                    //le nouveau regroupement est une copie de result[start] ...
                    result.back().add(i, demande_[i]);
                    // ... auquel on ajoute le point i et la quantité d'eau correspondante
                }
            }
        }
        
        start = stop;
        stop = result.size();
    }
    //probleme result(std::move(result), nblieux_-1);
    return result;
}

unsigned int donnees::distance( std::vector<unsigned int> lieux) const
{
    unsigned int result = 0;
    unsigned int previous = 0;

    for( auto & current : lieux)
    {
        result += C_[previous][current];
        previous = current;
    }

    result += C_[previous][0];
    return result;
}

void donnees::init_distance(regroupement& rgrp) const
{
    std::vector<unsigned int>& lieux(rgrp.lieux());
    std::vector<unsigned int> ordre_opti(lieux);
    
    unsigned int min_dist = distance(lieux);
    unsigned int tmp_dist;
    while( std::next_permutation(lieux.begin(), lieux.end()) )
    {//parcours des permutations. le parcours s'arrête lorsque la prochaine permutation est triée.
        tmp_dist = distance(lieux);
        if(tmp_dist < min_dist)
        {
            ordre_opti = lieux;
            min_dist = tmp_dist;
        }
    }
    lieux = ordre_opti;
    rgrp.distance() = min_dist;
}

std::ostream& operator<<(std::ostream& os, donnees const& datas)
{
    os << "donnees : " << datas.nblieux() << " lieux; " << datas.capacite() << " capacite" << std::endl;
    return os;
}
