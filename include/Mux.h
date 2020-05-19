#pragma once

#include "LogicGate.h"

class Mux : public LogicGate
{
public:
    int inputCount() const override
    {
        return 3;
    }

    bool compute(const std::vector<bool>& inputs) const override;

private:
    void printImpl(std::ostream& ostr) const override;
};
