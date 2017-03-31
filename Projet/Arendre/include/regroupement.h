#ifndef JAPH_REGROUPEMENT
#define JAPH_REGROUPEMENT

#include <vector>
#include <iostream>

class regroupement
{
  public:
    regroupement(std::vector<unsigned int> lieux, unsigned int quantite);
    void add(unsigned int point, unsigned int quantite);

    unsigned int quantite() const { return quantite_; }
    const std::vector<unsigned int>& lieux() const { return lieux_; }
    std::vector<unsigned int>& lieux() { return lieux_; }

    //getters
    unsigned int distance() const { return distance_; }
    unsigned int & distance() { return distance_; }
    unsigned int dernier_point() const;

  private:
    std::vector<unsigned int> lieux_;
    unsigned int quantite_;
    unsigned int distance_;
};

std::ostream& operator<<(std::ostream& os, regroupement const& regr);

#endif//JAPH_REGROUPEMENT
