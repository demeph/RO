#include "probleme.h"

probleme::probleme(std::vector<regroupement> && regroupements, unsigned int nb_points):
    regroupements_(regroupements),
    regroupements_contenant_(nb_points)
{
    init_regroupements_contenant();
}

void probleme::init_regroupements_contenant()
{
    unsigned int size_regr = regroupements_.size();
    for(unsigned int i = 0; i < size_regr; ++i)
    {
        for(unsigned int el: regroupements_[i].lieux())
        {
            regroupements_contenant_[el].push_back(i);
        }
    }
}
