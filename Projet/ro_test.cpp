#include <iostream>
#include "regroupement.h"
#include "donnees.h"
#include "chrono.h"
#include "container_overload.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::string source_file(argv[1]);
    cout << "opening file" << source_file << endl;

    chrono chr;
    chr.start();
    
    donnees data(source_file);
    auto combinaisons = data.generer_regroupements();

    unsigned int threshold = 5000;
    if(combinaisons.size() < threshold)
        for(auto it = combinaisons.begin(); it != combinaisons.end(); ++it)
            cout << "\t" << *it << endl;
    
    cout << combinaisons.size() << " regroupements" << endl;

    chr.stop();

    cout << "temps : " << chr.to_ms() / 1000 << endl;

    //libération automatique de la memoire via le destructeur
	return 0;

}
