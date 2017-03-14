#include <iostream>
#include <vector>
#include <cmath>

#define N 5 // taille de l'ensemble qui contient les valeurs de 1 à 5

typedef struct {
	std::vector<int> regroupe;
	int longuerTour;
}regroupLong;

void copie(std::vector<int> & v,std::vector<int> & v1)
{
	for (int i = 0; i < v1.size();++i)
	{
		v.push_back(v1[i]);
	}
}

void genereSSensemble(regroupLong l[])
{
	int nbElt = pow(2,N)-1; 
	int nbEltSaisie = 0;
	for (int i = 0; i < N; ++i)
	{
		l[i].regroupe.push_back(i+1);
		nbEltSaisie++;
	}
	int k = 0;
	while (nbEltSaisie < nbElt )
	{
		int p = l[k].regroupe[l[k].regroupe.size()-1];
		for (int i = p; i <= N;++i)
		{
			for (int j = i+1; j <= N; ++j)
			{
				copie(l[nbEltSaisie].regroupe,l[k].regroupe);
				l[nbEltSaisie].regroupe.push_back(j);
				++nbEltSaisie;
			}
			++k;
		}
	}
}

int main()
{
	int nbElt = pow(2,N)-1;
	regroupLong liste[nbElt];	

	genereSSensemble(liste);

	for (int cpt = 0;cpt < nbElt;++cpt)
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


