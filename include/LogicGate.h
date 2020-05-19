#pragma once

#include <iosfwd>
#include <vector>

class LogicGate
{
public:
    virtual ~LogicGate() = default;
    virtual int inputCount() const = 0;
    virtual bool compute(const std::vector<bool>& inputs) const = 0;
    void printTable(std::ostream& ostr) const;

    friend inline std::ostream& operator<<(std::ostream& ostr, const LogicGate& gate)
    {
        gate.print(ostr);
        return ostr;
    }

private:
    void print(std::ostream& ostr) const;
    void printTableImpl(std::ostream& ostr, std::vector<bool>& inputs, int index) const;
    virtual void printImpl(std::ostream& ostr) const = 0;
};
