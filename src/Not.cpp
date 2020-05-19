#include "Not.h"

#include <ostream>

bool Not::compute(const std::vector<bool>& inputs) const
{
    return !inputs[0];
}

void Not::printImpl(std::ostream& ostr) const
{
    ostr << "NOT";
}
