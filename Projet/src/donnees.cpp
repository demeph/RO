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

std::vector<regroupement> donnees::generer_regroupements() const
{
    std::vector<regroupement> result;

    std::cout << *this << std::endl;
    
    for(unsigned int i = 1; i < nblieux_; ++i)//generation des premiers regroupements; ceux ne comportant qu'un seul point
        if(capacite_ >= demande_[i])
        {
            result.emplace_back( std::vector<unsigned int>{i}, demande_[i]);
            init_distance(result.back());
        }

    unsigned int start = 0;
    unsigned int stop = result.size();
    
    for(unsigned int stage = 2; stage < nblieux_; ++stage)
    {
        for(; start < stop; ++start)//parcours de chacun des points générés à l'étape précédente
        {
            for(unsigned int i = result[start].lieux().back() + 1; i < nblieux_; ++i)
            {
                if(result[start].quantite() + demande_[i] <= capacite_)
                {
                    result.push_back( result[start] );//on emplace back une copie de *start
                    result.back().add(i, demande_[i]);
                    init_distance(result.back());
                }
            }
        }
        
        start = stop;
        stop = result.size();
    }
    
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
    //std::sort(lieux.begin(), lieux.end());//on s'assure que lieux soit trié pour pouvoir parcourir toutes les permutations

    unsigned int min_dist = distance(lieux);
    unsigned int tmp_dist;
    while( std::next_permutation(lieux.begin(), lieux.end()) )
    {
        tmp_dist = distance(lieux);
        if(tmp_dist < min_dist)
            min_dist = tmp_dist;
    }
    rgrp.distance() = min_dist;
    
}

std::ostream& operator<<(std::ostream& os, donnees const& datas)
{
    os << "donnees : " << datas.nblieux() << " lieux; " << datas.capacite() << " capacite" << std::endl;
    return os;
}
