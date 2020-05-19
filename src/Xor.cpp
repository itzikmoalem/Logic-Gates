#include "Xor.h"

#include <ostream>

bool Xor::compute(const std::vector<bool>& inputs) const
{
    return inputs[0] != inputs[1];
}

void Xor::printImpl(std::ostream& ostr) const
{
    ostr << "XOR";
}
