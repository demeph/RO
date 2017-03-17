#ifndef DEJA_TOURNEE
#define DEJA_TOURNEE

#include <vector>

class tournee
{
  public:
    tournee(std::vector<int> lieux);
    const std::vector<int>& lieux() const { return lieux_; }
  private:
    std::vector<int> lieux_;
};

#endif//DEJA_TOURNEE
