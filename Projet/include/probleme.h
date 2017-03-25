#ifndef JAPH_PROBLEME
#define JAPH_PROBLEME

#include "regroupement.h"
#include <vector>

class probleme
{
  public:
    probleme(std::vector<regroupement> & regroupements, unsigned int nb_points);
    probleme()=delete;

    std::vector<regroupement> const& regroupements() const { return regroupements_; }
    std::vector< std::vector<unsigned int> > const& regroupements_contenant() const { return regroupements_contenant_; }
    
  private:
    void init_regroupements_contenant();
    std::vector<regroupement> regroupements_;
    std::vector< std::vector<unsigned int> > regroupements_contenant_;
};

#endif//JAPH_PROBLEME
