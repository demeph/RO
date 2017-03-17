#ifndef JAPH_TOURNEE
#define JAPH_TOURNEE

#include <vector>

class tournee
{
  public:
    tournee(std::vector<int> lieux);
    const std::vector<int>& lieux() const { return lieux_; }
  private:
    std::vector<int> lieux_;
};

#endif//JAPH_TOURNEE
