#ifndef MOOSS_CONTAINER_OVERLOAD
#define MOOSS_CONTAINER_OVERLOAD

#include <vector>
#include <array>
#include <tuple>
#include <ostream>

template<class element, std::size_t size>
std::ostream& operator<<(std::ostream& os, const std::array<element, size>& container)
{
    auto elementIter = container.begin();
    os << "[";
    if(size > 0)
    {
        os << *elementIter;
        for(++elementIter; elementIter != container.end(); ++elementIter)
            os << "; " << *elementIter;
    }
    os << "]";
    return os;
}

template<class element>
std::ostream& operator<<(std::ostream& os, const std::vector<element>& container)
{
   
    auto elementIter = container.begin();
    os << "[";
    if(container.size() > 0)
    {
        os << *elementIter;
        for(++elementIter; elementIter != container.end(); ++elementIter)
            os << "; " << *elementIter;
    }
    os << "]";
    return os;
}

#endif//MOOSS_CONTAINER_OVERLOAD
