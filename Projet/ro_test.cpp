#include <iostream>
#include "regroupement.h"
#include "donnees.h"
#include "chrono.h"
#include "container_overload.hpp"
#include "glpkwrapper.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::string source_file(argv[1]);

    double data_loading_time,
        regr_compute_time,
        shortest_path_compute_time,
        glpk_solving_time,
        problem_creation_time;

    chrono chr;

    cout << "chargement des donnees du fichier " << source_file << " ... ";

    chr.start();
    donnees data(source_file);
    chr.stop();

    data_loading_time = chr.to_sec();
    cout << data_loading_time << " secondes" << endl;

    cout << "\ncalcul des regroupements réalisables ... ";

    chr.start();
    auto regroupements_realisables = data.generer_regroupements();
    chr.stop();
    
    regr_compute_time = chr.to_sec();
    cout << regr_compute_time << " secondes\n"
         << "nombre de regroupements générés : " << regroupements_realisables.size() << endl;

    cout << "\ncalcul des plus courts chemins ... ";

    chr.start();
    for(auto & el : regroupements_realisables)
        data.init_distance(el);
    chr.stop();

    shortest_path_compute_time = chr.to_sec();
    cout << shortest_path_compute_time << " secondes" << endl;

    cout << "\ngénération du problème ... ";
    chr.start();
    probleme le_probleme(regroupements_realisables, data.points_de_pompage());
    chr.stop();

    problem_creation_time = chr.to_sec();
    cout << problem_creation_time << " secondes " << endl;
    

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

    cout << "\nrésolution du problème avec glpk\n" << endl;
    
    chr.start();
    glpkwrapper glpk(data.nblieux(),le_probleme);
    //cout << "wrapper :\n" << glpk << endl;
    glpk.resoudre_probleme();
    chr.stop();

    glpk_solving_time = chr.to_sec();
    cout << "\nla résolution du problème avec glpk a pris " << glpk_solving_time << " secondes\n" << endl;

    glpk.afficher();

    cout << "\ntemps de calcul total : " << 
        data_loading_time +
        regr_compute_time +
        shortest_path_compute_time +
        glpk_solving_time +
        problem_creation_time << endl;

    //libération automatique de la memoire via le destructeur
	return 0;

}
