#include "Comp.h"

#include <ostream>

Comp::Comp(const std::shared_ptr<LogicGate>& a, const std::shared_ptr<LogicGate>& b, int connectTo)
    : m_a(a), m_b(b), m_connectTo(connectTo)
{
}

int Comp::inputCount() const
{
    return m_a->inputCount() + m_b->inputCount() - 1;
}

bool Comp::compute(const std::vector<bool>& inputs) const
{
    auto aInputs = std::vector<bool>();
    for (auto i = m_connectTo; i < m_connectTo + m_a->inputCount(); ++i)
    {
        aInputs.push_back(inputs[i]);
    }

    auto aRes = m_a->compute(aInputs);

    auto bInputs = std::vector<bool>();
    for (auto i = 0; i < m_connectTo; ++i)
    {
        bInputs.push_back(inputs[i]);
    }
    bInputs.push_back(aRes);
    for (auto i = m_connectTo + m_a->inputCount(); i < inputs.size(); ++i)
    {
        bInputs.push_back(inputs[i]);
    }

    return m_b->compute(bInputs);
}

void Comp::printImpl(std::ostream& ostr) const
{
    ostr << "{" << *m_a << "->[" << m_connectTo << "]" << *m_b << "}";
}
