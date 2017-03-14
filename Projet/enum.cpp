#include <iostream>
#include <vector>
#include <cmath>

struct {
	std::vector<int> regroupe;
	int longuerTour;
} regroupLong;


int main()
{
	int n = 5;
	int nbCaseBack = 0;
	int nbElt = pow(2,5)-1;
	int nbEltSaisie = 0;
	nbElt -= 1;
	regroupLong[nbElt] p;
	std::vector<std::vector<int>> vectVect;
	for (int i = 0; i < n; ++i)
	{
		p[i].regroupe.push_back(i+1);
		nbEltSaisie++;
		nbCaseBack++;
	}
	while (nbEltSaisie > nbElt )
	{
		for ( i = 0; i<n; ++i)
		{
			for (j = i+1; j<n;++j)
			{
				p[nbEltSaisie].regroupe = p[nbEltSaisie-nbCaseBack].regroupe;
			}
		}
	}
}


