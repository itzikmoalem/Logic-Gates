#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iosfwd>
#include <fstream>
#include <sstream>

class LogicGate;

class LogicGateCalculator
{
public:
    LogicGateCalculator(std::istream& istr, std::ostream& ostr);
    void run();

private:
    void evaluate();
    void comp();
    void table();
    void del();
    void exit();
    void help();
	void read(); // read from file function
	void resize(); // resize max gates functio

    void printGates() const;

    enum class Action
    {
        Invalid,
        Eval,
        Comp,
        Table,
        Del,
        Exit,
        Help,
		Read,
		Resize,
    };

    struct ActionDetails
    {
        std::string command;
        std::string description;
        Action action;
		int numOfinputs; // to save the number of input to each gate
    };

    using ActionMap = std::vector<ActionDetails>;
    using GateList = std::vector<std::shared_ptr<LogicGate>>;

    const ActionMap m_actions;
    GateList m_gates;
	std::ifstream m_myFile;
	std::istringstream m_Stream;

    bool m_running = true;
    std::istream& m_istr;
    std::ostream& m_ostr;

	int m_ArgumentsNums; // arguments of each gate
	int m_MaxGates;		// max gates avaible
	bool m_BetweenBoth = false; // 5 to 100

	int ArgumentGet(std::string x); // get function
	void ValidateArguments(const int t); // validator to gate argument
    Action readAction();
    void runAction(Action action);
    bool validateGateIndex(int index) const; // validator to gate index
    std::vector<bool> readInputs(int count) const;

	void deleteGates(); // delete gate function when resize

    static ActionMap createActions();
    static GateList createGates();
};
