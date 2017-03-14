#include <iostream>
#include <vector>
#include <cmath>

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
	/*std::cout << "--------\n";
	for(int l = 0;l < v.size();++l)
	{
		std::cout << v[l];
	}
	std::cout << "\n--------\n";*/
}

int main()
{
	int n = 5;
	int nbCaseBack = 0;
	int nbElt = pow(2,n)-1;
	int nbEltSaisie = 0;
	regroupLong liste[nbElt];
	for (int i = 0; i < n; ++i)
	{
		liste[i].regroupe.push_back(i+1);
		nbEltSaisie++;
		nbCaseBack++;
	}
	int k = nbEltSaisie-nbCaseBack;
	while (nbEltSaisie < nbElt )
	{
		//std::cout << "nbCaseBack = " << nbCaseBack << std::endl;;
		//std::cout << "k = " << k << std::endl;;
		int p;
		p = liste[k].regroupe[liste[k].regroupe.size()-1];
		//std::cout << "p = " << p << std::endl;;
		nbCaseBack = 0;
		//std::cout << "nbEltSaisie = " << nbEltSaisie << std::endl;;
		for (int j = p; j <= n;++j)
		{
			for (int i = j+1; i<=n; ++i)
			{
				copie(liste[nbEltSaisie].regroupe,liste[k].regroupe);
				liste[nbEltSaisie].regroupe.push_back(i);
				++nbEltSaisie;
				++nbCaseBack;
			}
			//std::cout << "k57 : " << k << "\n";
			// std::cout << "val : " << liste[k].regroupe[liste[k].regroupe.size()-1] << "\n";
			++k;
		}
		//k += 1;
		//std::cout << "--------\n";
	}

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


