  #include "ProductSet.hpp"
#include "Set.hpp"

ProductSet::ProductSet(Set a, Set b)
{
    first = a;
    second = b;
}

Set ProductSet::getFirstSet() const
{
    return first;
}
Set ProductSet::getSecondSet() const
{
    return second;
}