#include "Mux.h"

#include <ostream>

bool Mux::compute(const std::vector<bool>& inputs) const
{
    return inputs[2] ? inputs[1] : inputs[0];
}

void Mux::printImpl(std::ostream& ostr) const
{
    ostr << "MUX";
}
