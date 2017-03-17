#include "regroupement.h"

regroupement::regroupement(std::vector<unsigned int> lieux):
    lieux_(lieux)
{}

void regroupement::add(unsigned int point)
{
    lieux_.push_back(point);
}

std::ostream& operator<<(std::ostream& os, regroupement const& regr)
{
    
    os << "regroupement : [";
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

    os << "]";
        
    return os;
}
