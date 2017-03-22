#include <iostream>
#include "regroupement.h"
#include "donnees.h"
#include "chrono.h"
#include "container_overload.h"
#include "glpkwrapper.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::string source_file(argv[1]);
    cout << "opening file" << source_file << endl;

    chrono chr;
    chr.start();
    
    donnees data(source_file);
    auto le_probleme = data.generer_probleme();
    std::vector<regroupement> combinaisons = le_probleme.regroupements();

    // unsigned int threshold = 100;
    // if(combinaisons.size() < threshold)
    //     for(auto it = combinaisons.begin(); it != combinaisons.end(); ++it)
    //         cout << "\t" << *it << endl;
    // else
    // {
    //     unsigned int mid = threshold/2;
    //     cout << "il y a plus de "
    //          << threshold
    //          << " elements. affichage des "
    //          << mid
    //          << " premiers et des "
    //          << mid
    //          << " derniers"
    //          << "\n" << endl;
    //     for(auto it = combinaisons.begin(); it != combinaisons.begin() + mid +1; ++it)
    //         cout << "\t" << *it << endl;
    //     cout << endl;
        
    //     for(auto it = combinaisons.end() -(mid +1) ; it != combinaisons.end(); ++it)
    //         cout << "\t" << *it << endl;

    // }


    glpkwrapper glpk(data.nblieux(),le_probleme);
    cout << "wrapper :\n" << glpk << endl;
    glpk.resoudre_probleme();

    

    chr.stop();

    cout << "temps : " << chr.to_ms() / 1000 << endl;

    //libération automatique de la memoire via le destructeur
	return 0;

}
