#include "LogicGateCalculator.h"
#include "Utilities.h"

#include "LogicGate.h"
#include "Or.h"
#include "Xor.h"
#include "And.h"
#include "Not.h"
#include "Mux.h"

#include "Comp.h"

#include <istream>
#include <ostream>
#include <iostream>
#include <iosfwd>
#include <exception>

LogicGateCalculator::LogicGateCalculator(std::istream& istr, std::ostream& ostr)
    : m_actions(createActions()), m_gates(createGates()), m_istr(istr), m_ostr(ostr)
{
}

void LogicGateCalculator::run()
{
	// Get from the user the max get value
	try 
	{
		resize();
	}
	catch(std::exception &e)
	{
		std::cerr << e.what();
	}
	
	// Main loop
    do
    {
		m_ostr << '\n';
		printGates();
		m_ostr << "Enter command ('help' for the list of available commands): ";

		try 
		{
			const auto action = readAction(); // action read from user

			runAction(action);				// action run fucntion
		}

		catch(std::exception &e) // in case we get exepction
		{
			std::cerr << e.what();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
    } while (m_running);
}
// Get inputs to each gate
std::vector<bool> LogicGateCalculator::readInputs(int count) const
{
	bool in;
	int num;
    auto res = std::vector<bool>();

    for (auto i = 0; i < count; ++i)
    {
        m_istr >> num;

		if (num == 0 || num == 1)
		{
			in = num;
			res.push_back(in);
		}
		else
			throw std::runtime_error::runtime_error("You have to put bool input.\n");
    }

    return res;
}
// Delete gates in case the gates vector resized.
void LogicGateCalculator::deleteGates()
{
	for(int i=m_MaxGates-1; i<=m_gates.size(); i++)
		m_gates.pop_back();
}

// Resize the gate vector function
void LogicGateCalculator::resize()
{
	int temp = 0;
	while (!m_BetweenBoth)		//check is between the max and min values
	{
		m_ostr << "Please enter maximum gates contain: ";
		m_istr >> temp;

		if (temp >= MIN_GATES && temp <= MAX_GATES) { // 5 to 100
			m_BetweenBoth = true;
			m_MaxGates = temp;
		}
		else
			throw std::runtime_error::runtime_error("The maximum has to be between 5-100 \n");
	}

	m_BetweenBoth = false;

	if (m_MaxGates < m_gates.size()) // if the current gates are more than max gates variable
		deleteGates();
}
// Evaluate function
void LogicGateCalculator::evaluate()
{
    auto i = 0;
    m_istr >> i;
	if (validateGateIndex(i))
	{
		m_ostr << *m_gates[i] << " result: "
			<< m_gates[i]->compute(readInputs(m_gates[i]->inputCount()))
			<< '\n';
	}
	else
		throw std::runtime_error::runtime_error("Gate #" + std::to_string(i) + " isn't Found");

}
// Comp function
void LogicGateCalculator::comp()
{
    auto a = 0;
    auto b = 0;
    auto connectTo = 0;
    m_istr >> a >> b >> connectTo;
	
	validateGateIndex(a); // validate indexes
	validateGateIndex(b);

    if (connectTo < 0 || m_gates[b]->inputCount() <= connectTo) // validate inputs
    {
		throw std::runtime_error::runtime_error("Input :" + std::to_string(connectTo) + " isn't Found");
    }

	//if(!isdigit(connectTo))
	//	throw std::runtime_error::runtime_error("Input :" + std::to_string(connectTo) + " isn't Found");

	if (m_gates.size() >= m_MaxGates) // validate max gates doesnt arrived
		throw std::runtime_error::runtime_error("You arrived to maximum gates: " + std::to_string(m_MaxGates));

    m_gates.push_back(std::make_shared<Comp>(m_gates[a], m_gates[b], connectTo));
}
// print table function
void LogicGateCalculator::table()
{
    auto i = 0;
    m_istr >> i;
    if (validateGateIndex(i))
    {
        m_ostr << *m_gates[i] << " truth table:\n";
        m_gates[i]->printTable(m_ostr);
    }
}
// Delete gate function
void LogicGateCalculator::del()
{
    auto i = 0;
    m_istr >> i;
    if (validateGateIndex(i))
    {
        m_gates.erase(m_gates.begin() + i);
    }
}
// Exit function
void LogicGateCalculator::exit()
{
    m_ostr << "Goodbye!\n";
    m_running = false;
}
// Help command function
void LogicGateCalculator::help()
{
    m_ostr << "The available commands are:\n";
    for (auto i = 0; i < static_cast<decltype(i)>(m_actions.size()); ++i)
    {
        m_ostr << "* " << m_actions[i].command << ' ' << m_actions[i].description << '\n';
    }
    m_ostr << '\n';
}
// Read form file function
void LogicGateCalculator::read()
{
	std::string x;
	char keep;	//for keep answer (y/n)
	m_istr >> x;

	m_myFile.open(x.c_str(), std::ios::in);	//open file
	
	if (!m_myFile.is_open())
	{
		throw std::runtime_error::runtime_error("Cannot Open File!\n"); // Execption when file donesnt exsite
	}

	while (std::getline(m_myFile, x)) // read line by line
	{
		m_Stream = std::istringstream(x);
		LogicGateCalculator fileinput(m_Stream, m_ostr);	//the next line

		fileinput.m_gates = this->m_gates;	//update gate list
		fileinput.m_MaxGates = this->m_MaxGates;	//update maximum gates

		int Inputs = ArgumentGet(x);	//return the number of arguments give to command

		try { 
			auto action = fileinput.readAction();	//try command
			fileinput.ValidateArguments(Inputs); 
			fileinput.runAction(action);
		}

		catch (std::exception &e)
		{
			std::cerr << std::endl << "Error In: " + x << std::endl <<
				"Error Type: " << e.what() << std::endl << "Did you want to continue reading from file (Y/N)\n";

			std::cin >> keep;	//keep the answer (y/n)
			if (keep == 'N' || keep == 'n')		//negative answer
				break;
		}

		this->m_gates = fileinput.m_gates;   // update the gate list 
		this->m_MaxGates = fileinput.m_MaxGates;	//update maximum gates

		if (!fileinput.m_running) // "exit" command was read from the file -> stop the reading from the file.
			break;
	}
	m_myFile.close();
}
// Print gate function
void LogicGateCalculator::printGates() const
{
    m_ostr << "List of available gates:\n";
    for (auto i = 0; i < static_cast<decltype(i)>(m_gates.size()); ++i)
    {
        m_ostr << i << ".\t" << *m_gates[i] << '\n';
    }
	m_ostr << '\n';
	m_ostr << "The maximum gates is " + std::to_string(m_MaxGates) << '\n';
}
// Argument get function
int LogicGateCalculator::ArgumentGet(std::string x)
{
	std::string s = x.substr(0, x.find(" "));

	for (auto i = 0; i < static_cast<decltype(i)>(m_actions.size()); ++i)
	{
		if (s == m_actions[i].command)
		{
			return m_actions[i].numOfinputs;
		}
	}
	return 0;
}
// Validate argument function
void LogicGateCalculator::ValidateArguments(const int t)
{
	if (this->m_ArgumentsNums != t)
		throw std::runtime_error::runtime_error("number of arguments doesn't fit the command");
}
// Read action from user function
LogicGateCalculator::Action LogicGateCalculator::readAction()
{
    auto action = std::string();
    m_istr >> action;

    for (auto i = 0; i < static_cast<decltype(i)>(m_actions.size()); ++i)
    {
        if (action == m_actions[i].command) // if the action we read found in the vector
        {
			m_ArgumentsNums = m_actions[i].numOfinputs; // update the input to specific gate
	
            return m_actions[i].action;
        }
    }

	throw std::runtime_error::runtime_error("Invalid command\n"); // expection throwing in case the comand doenst exist
}
// Run action function
void LogicGateCalculator::runAction(Action action)
{
    switch (action)
    {
        case Action::Eval:
            evaluate();
            break;
        case Action::Comp:
            comp();
            break;
        case Action::Table:
            table();
            break;
        case Action::Del:
            del();
            break;
        case Action::Exit:
            exit();
            break;
        case Action::Help:
            help();
            break;
		case Action::Read:
			read();
			break;
		case Action::Resize:
			resize();
			break;
        default:
            m_ostr << "Unknown enum entry used!\n";
            break;
    }
}
// Validate gate index function
bool LogicGateCalculator::validateGateIndex(int index) const
{
    if (index < 0 || m_gates.size() <= index)
    {
		throw std::runtime_error::runtime_error("Gate #" + std::to_string(index) + " isn't Found");
    }
    return true;
}
// Create action function
LogicGateCalculator::ActionMap LogicGateCalculator::createActions()
{
	return ActionMap
	{
		{ "eval",
		  "<x> <param1> <param2> ... - evaluation, compute the result "
			"of gate x when the inputs are param1 param2 ...",
		  Action::Eval,EVAL_INPUT
        },
        { "comp",
          "<x1> <x2> <y> - composition, connect gate x1 output to "
            "input y of gate x2 and add it to the list of the gates",
          Action::Comp,COMP_INPUT
        },
        { "table",
          "<x> - display the truth table of gate x",
          Action::Table,TABLE_INPUT
        },
        { "del",
          "<x> - delete gate x from the list",
          Action::Del,DEL_INPUT
        },
        { "exit",
          "- print a greeting to the user and close the program",
          Action::Exit,EXIT_INPUT
        },
        { "help",
          "- print this command list",
          Action::Help,HELP_INPUT
        },
		{ "read",
		  "- read commands from file",
		  Action::Read,READ_INPUT
		},
		{ "resize",
		  "- resize the maximum gate value",
	      Action::Resize,RESIZE_INPUT
		}
    };
}
// Create basic gates function
LogicGateCalculator::GateList LogicGateCalculator::createGates()
{
    return GateList
    {
        std::make_shared<Or>(),
        std::make_shared<Xor>(),
        std::make_shared<And>(),
        std::make_shared<Not>(),
        std::make_shared<Mux>()
    };
}
