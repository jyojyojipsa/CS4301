#ifndef FSA_H
#define FSA_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class TableEntry
{
public:
	TableEntry(char ch, unsigned int state)
	{
		setInputCharacter(ch);
		setNextState(state);
	}
	void setInputCharacter(char ch)
	{
		inputCharacter = ch;
	}
	void setNextState(unsigned int state)
	{
		nextState = state;
	}
	char getInputCharacter() const
	{
		return inputCharacter;
	}
	unsigned int getNextState() const
	{
		return nextState;
	}
private:
	char inputCharacter;
	unsigned int nextState;
};

class FSA
{
public:
	// default constructor -- initializes private data members name,
	// labNumber, and description
	FSA();
	// Member function initializeMachine() initializes the private data
	// member machine, a multimap where the key is the current state and
	// the value is a class object containing the input character and
	// the next state
	void initializeMachine();
	// Member function outputID() writes name, class, lab number, and
	// lab description to output stream out
	void outputID(ostream& out) const;
	// Member function implementFSA() returns true if dataLine is
	// recognized by the FSA as valid and false otherwise
	bool implementFSA(string dataLine) const;
private:
	string name;
	int labNumber;
	string description;
	multimap<unsigned int, TableEntry> machine;
};

#endif
