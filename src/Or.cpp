#include "Or.h"

#include <ostream>

void Or::printImpl(std::ostream& ostr) const
{
    ostr << "OR";
}

bool Or::compute(const std::vector<bool>& inputs) const
{
    return inputs[0] || inputs[1];
}
