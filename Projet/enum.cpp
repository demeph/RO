#include <iostream>
#include <vector>
#include <array>
#include <cmath>

#define N 5 // taille de l'ensemble qui contient les valeurs de 1 à 5
#define capaciteDrone 10
std::array<int, N> volume = {2,4,2,2,4};

struct regroupLong {
	std::vector<int> regroupe;
	int longuerTour;
};

void copie(std::vector<int> & v,std::vector<int> & v1)
{
	for (int i = 0; i < v1.size();++i)
	{
		v.push_back(v1[i]);
	}
}

void genereSSensemble(std::vector<regroupLong> & liste)
{
	int nbElt = pow(2,N)-1; 
	int nbEltSaisie = 0;
	for (int i = 0; i < N; ++i)
	{
		liste.push_back(regroupLong());
		liste.back().regroupe.push_back(i+1);
		++nbEltSaisie;
	}
	int k = 0;
	while ( nbEltSaisie < nbElt )
	{
		int p = liste[k].regroupe[liste[k].regroupe.size()-1];
		for (int i = p; i <= N;++i)
		{
			for (int j = i+1; j <= N; ++j)
			{
				liste.push_back(regroupLong());
				copie(liste.back().regroupe,liste[k].regroupe);
				liste.back().regroupe.push_back(j);
				++nbEltSaisie;
			}
			++k;
		}
	}
}

std::vector<regroupLong> filterListe(std::vector<regroupLong> & liste)
{
	std::vector<regroupLong> l1;
	for (int i = 0; i < liste.size(); ++i)
	{
		int capacite = 0;
		for (int m = 0; m < liste[i].regroupe.size();++m) capacite += volume[liste[i].regroupe[m]];
		if (capacite <= capaciteDrone) 
		{
			l1.push_back(regroupLong());
			copie(l1.back().regroupe,liste[i].regroupe);
		}
	}
	return l1;
}

int main()
{
	int nbElt = pow(2,N)-1;
	std::vector<regroupLong> liste;	

	genereSSensemble(liste);

	liste = filterListe(liste);
	
	for (int cpt = 0;cpt < liste.size();++cpt)
	{
		int l = liste[cpt].regroupe.size();
		int m = 0;
		for ( m = 0; m < l;++m)
		{
			std::cout << liste[cpt].regroupe[m] << " ";
		}
		std::cout << "\n";
	}
}