#include "And.h"

#include <ostream>

bool And::compute(const std::vector<bool>& inputs) const
{
    return inputs[0] && inputs[1];
}

void And::printImpl(std::ostream& ostr) const
{
    ostr << "AND";
}
