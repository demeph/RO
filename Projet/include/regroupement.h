#ifndef JAPH_REGROUPEMENT
#define JAPH_REGROUPEMENT

#include <vector>
#include <iostream>

class regroupement
{
  public:
    regroupement(std::vector<unsigned int> lieux);
    void add(unsigned int point);
    
    const std::vector<unsigned >& lieux() const { return lieux_; }

  private:
    std::vector<unsigned int> lieux_;
};

std::ostream& operator<<(std::ostream& os, regroupement const& regr);

#endif//JAPH_REGROUPEMENT
