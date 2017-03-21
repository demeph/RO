#include <iostream>
#include "regroupement.h"
#include "donnees.h"
#include "chrono.h"
#include "container_overload.h"
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */
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

    unsigned int threshold = 100;
    if(combinaisons.size() < threshold)
        for(auto it = combinaisons.begin(); it != combinaisons.end(); ++it)
            cout << "\t" << *it << endl;
    else
    {
        unsigned int mid = threshold/2;
        cout << "il y a plus de "
             << threshold
             << " elements. affichage des "
             << mid
             << " premiers et des "
             << mid
             << " derniers"
             << "\n" << endl;
        for(auto it = combinaisons.begin(); it != combinaisons.begin() + mid +1; ++it)
            cout << "\t" << *it << endl;
        cout << endl;
        
        for(auto it = combinaisons.end() -(mid +1) ; it != combinaisons.end(); ++it)
            cout << "\t" << *it << endl;

    }


    // cout << combinaisons.size() << " regroupements" << endl;

    // for(unsigned int i = 1; i < le_probleme.regroupements_contenant().size(); ++i)
    // {        
    //     cout << "le point " << i << " est contenu dans :" << endl;
    //     for(auto & el: le_probleme.regroupements_contenant()[i])
    //         cout << "\t" << el << endl;
    // }

// glp_prob *trumpland;
    // int *ia;
    // int *ja;
    // double *ar;

    // trumpland = glp_create_prob()
    // glp_set_prob_name(trumpland,"Probleme de trumpland");
    // glp_set_obj_dir(prob,GLP_MIN);

    

    chr.stop();

    cout << "temps : " << chr.to_ms() / 1000 << endl;

    //libération automatique de la memoire via le destructeur
	return 0;

}
