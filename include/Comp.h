#pragma once

#include "LogicGate.h"

#include <memory>

class Comp : public LogicGate
{
public:
    Comp(const std::shared_ptr<LogicGate>& a, const std::shared_ptr<LogicGate>& b, int connectTo);

    int inputCount() const override;
    bool compute(const std::vector<bool>& inputs) const override;

private:
    void printImpl(std::ostream& ostr) const override;

    std::shared_ptr<LogicGate> m_a;
    std::shared_ptr<LogicGate> m_b;
    int m_connectTo;
};
