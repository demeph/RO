#include "donnees.h"
#include "container_overload.h"

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
    
    for(unsigned int i = 0; i < nblieux_; ++i)
        result.emplace_back( std::vector<unsigned int>{i} );

    for(auto it = result.begin(); it != result.end(); ++it)
        std::cout << *it << std::endl;



    auto start = result.begin();
    auto stop = result.end();
    auto last = std::prev(stop);
    
    for(unsigned int stage = 2; stage < nblieux_; ++stage)
    {
        std::cout << "damn" << std::endl;
//        std::cout << *start << std::endl;
        for(; start != stop; ++start)//parcours de chacun des points générés à l'étape précédente
        {
            for(unsigned int i = start->lieux().back() + 1; i < nblieux_; ++i)
            {
                std::cout << "\t" << i;
                std::cout.flush();
                result.emplace_back( start->lieux() );//on emplace back une copie de *start
                result.back().add(i);
            }
        }
        
        start = std::next(last);
        stop = result.end();
        last = std::prev(stop);
        
    }
    
    return result;
}

std::ostream& operator<<(std::ostream& os, donnees const& datas)
{
    os << "donnees : " << datas.nblieux() << " lieux; " << datas.capacite() << " capacite" << std::endl;
    return os;
}
