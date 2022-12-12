#ifndef PDA_H
#define PDA_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class TableEntry
{
public:
	TableEntry(char stackSymbol, char inputSymbol, string pushPop, uint state)
	{
		setStackSymbol(stackSymbol);
		setInputSymbol(inputSymbol);
		setPushPop(pushPop);
		setNextState(state);
	}
	void setStackSymbol(char ch)
	{
		stackSymbol = ch;
	}
	void setInputSymbol(char ch)
	{
		inputSymbol = ch;
	}
	void setPushPop(string s)
	{
		pushPop.resize(2);
		pushPop[0] = s[0];
		if (s.length() > 1)
			pushPop[1] = s[1];
	}
	void setNextState(uint state)
	{
		nextState = state;
	}
	char getStackSymbol() const
	{
		return stackSymbol;
	}
	char getInputSymbol() const
	{
		return inputSymbol;
	}
	string getPushPop() const
	{
		return pushPop;
	}
	uint getNextState() const
	{
		return nextState;
	}
private:
	char stackSymbol;
	char inputSymbol;
	string pushPop;
	uint nextState;
};

class PDA
{
public:
	// default constructor -- initializes private data members name,
	// labNumber, and description
	PDA();
	// Member function InitializeMachine() initializes the private data
	// member machine, a multimap where the key is the current state and
	// the value is a class object containing the stack symbol, input
	// symbol, push_pop, and next state
	void initializeMachine();
	// Member function OutputID() writes name, class, lab number, and
	// lab description to output stream out
	void outputID(ostream& out) const;
	// Member function ImplementPDA() returns true if dataLine is
	// recognized by the PDA as valid and false otherwise
	bool implementPDA(string dataLine) const;
private:
	string name;
	int labNumber;
	string description;
	multimap<uint, TableEntry> machine;
};

#endif
