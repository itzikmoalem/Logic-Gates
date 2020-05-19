#pragma once

#include "LogicGate.h"

class Or : public LogicGate
{
public:
    int inputCount() const override
    {
        return 2;
    }

    bool compute(const std::vector<bool>& inputs) const override;

private:
    void printImpl(std::ostream& ostr) const override;
};
