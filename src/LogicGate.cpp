#include "LogicGate.h"

#include <ostream>

//Print Table Function
void LogicGate::printTable(std::ostream& ostr) const
{
    for (auto i = 0; i < inputCount(); ++i)
    {
        ostr << "input #" << i << " | ";
    }
    ostr << "result\n";
    for (auto i = 0; i < inputCount(); ++i)
    {
        ostr << "===========";
    }
    ostr << "======\n";

    auto inputs = std::vector<bool>(inputCount(), false);
    printTableImpl(ostr, inputs, 0);
}

//Print Function
void LogicGate::print(std::ostream& ostr) const
{
    printImpl(ostr);
    ostr << " (" << inputCount() << " inputs)";
}

//Print Table Function 2
void LogicGate::printTableImpl(std::ostream& ostr, std::vector<bool>& inputs, int index) const
{
    if (index == inputs.size())
    {
        for (auto i = 0; i < static_cast<decltype(i)>(inputs.size()); ++i)
        {
            ostr << inputs[i] << "        | ";
        }
        ostr << compute(inputs) << '\n';
        return;
    }

    inputs[index] = false;
    printTableImpl(ostr, inputs, index + 1);
    inputs[index] = true;
    printTableImpl(ostr, inputs, index + 1);
}
