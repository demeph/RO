#include "donnees.h"
#include "container_overload.h"
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

probleme donnees::generer_probleme() const
{
    std::vector<regroupement> regroupements;

    for(unsigned int i = 1; i < nblieux_; ++i)//on parcours tous les points de pompage
        if(capacite_ >= demande_[i])//on teste quand même la capacité
        {
            regroupements.emplace_back( std::vector<unsigned int>{i}, demande_[i]);
            init_distance(regroupements.back());
        }

    unsigned int start = 0;
    unsigned int stop = regroupements.size();
    
    for(unsigned int stage = 2; stage < nblieux_; ++stage)//génération des sous-ensembles de taille stage
    {
        for(; start < stop; ++start)//parcours de chacun des points de taille stage-1
        {
            for(unsigned int i = regroupements[start].dernier_point() + 1; i < nblieux_; ++i)
            {
                if(regroupements[start].quantite() + demande_[i] <= capacite_)
                {
                    regroupements.push_back( regroupements[start] );//on emplace back une copie de *start
                    regroupements.back().add(i, demande_[i]);
                    init_distance(regroupements.back());
                }
            }
        }
        
        start = stop;
        stop = regroupements.size();
    }
    probleme result(std::move(regroupements), nblieux_-1);
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
    std::sort(lieux.begin(), lieux.end());//on s'assure que lieux soit trié avant de faire des permutations
    std::vector<unsigned int> ordre_opti(lieux);
    
    unsigned int min_dist = distance(lieux);
    unsigned int tmp_dist;
    while( std::next_permutation(lieux.begin(), lieux.end()) )
    {
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
