#include <iostream>
#include "tournee.h"
#include "container_overload.h"

using namespace std;

int main()
{
    std::vector<int> test = {4, 8, 15, 16};
    tournee tour(test);

    cout << "test1" << endl << "\t" << tour.lieux() << std::endl;

    return 0;
}
