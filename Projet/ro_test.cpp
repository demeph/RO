#include <iostream>
#include "regroupement.h"
#include "donnees.h"
#include "container_overload.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::vector<unsigned int> test = {4, 8, 15, 16};
    regroupement tour(test);

    cout << "test1" << endl << "\t" << tour.lieux() << std::endl;


    std::string source_file(argv[1]);
    cout << "opening file" << source_file << endl;
    donnees data(source_file);
    auto combinaisons = data.generer_regroupements();

    for(auto it = combinaisons.begin(); it != combinaisons.end(); ++it) cout << "\t" << it->lieux() << endl;
	
	return 0;

}
