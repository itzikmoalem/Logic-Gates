#pragma once

#include "LogicGate.h"

class Not : public LogicGate
{
public:
    int inputCount() const override
    {
        return 1;
    }

    bool compute(const std::vector<bool>& inputs) const override;

private:
    void printImpl(std::ostream& ostr) const override;
};
