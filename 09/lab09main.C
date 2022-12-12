#include <turing.h>

using namespace std;

int main()
{
  Turing myTuring;
  string dataLine, tape;

  myTuring.initializeMachine();
  myTuring.outputID(cout);

  while (getline(cin, dataLine))
  {
    cout << "Input:  " << dataLine << endl;
    tape = "          " + dataLine;
    tape.resize(3 * tape.length(), ' ');
    cout << "Output:  ";
    myTuring.implementTuring(tape);
    while (tape.back() == ' ')
      tape.pop_back();
    cout << tape << endl << endl;
  }

  return 0;
}

void Turing::outputID(ostream& out) const
{
  out << name << endl;
  out << "CS 4301" << endl;
  out << "Lab " << labNumber << endl;
  out << description << endl << endl;
}

void Turing::implementTuring(string& tape) const
{
  int currentState = 1;
  string::iterator tapeItr = tape.begin();
  multimap<uint, TableEntry>::const_iterator turingItr;
    
  while (currentState > 0)
  {
    // Use find to return an iterator to the first entry with a key of
    // currentState
    turingItr = machine.find(currentState);
    if (turingItr != machine.end()) // found a key of currentState
    {
      while (turingItr != machine.upper_bound(currentState) &&
             turingItr->second.getReadCharacter() != *tapeItr)
        ++turingItr;
      if (turingItr != machine.upper_bound(currentState))
      {
        currentState = turingItr->second.getNextState();
        *tapeItr = turingItr->second.getWriteCharacter();
        tapeItr += turingItr->second.getMove();
      }
      else
      {
        currentState = -1;
        *tapeItr = '~';
      }
    }
    else
    {
      currentState = -1;
      *tapeItr = '~';
    }
  }
}
