#include "regroupement.h"

regroupement::regroupement(std::vector<unsigned int> lieux, unsigned int quantite):
    lieux_(lieux),
    quantite_(quantite)
{}

void regroupement::add(unsigned int point, unsigned int quantite)
{
    lieux_.push_back(point);
    quantite_+=quantite;
}

unsigned int regroupement::dernier_point() const
{
    return lieux_.back();
}

std::ostream& operator<<(std::ostream& os, regroupement const& regr)
{
    
    os << "lieux : [";
    auto it = regr.lieux().begin();
    auto end = regr.lieux().end();
    if(it != end)
    {
        os << *it;
        ++it;
    }
    
    for(; it != end; ++it)
    {
        os << "; " << *it;
    }

    os << "] quantite : "
       << regr.quantite()
       << " distance : "
       << regr.distance();
        
    return os;
}
