#include <fsa.h>

using namespace std;

int main()
{
  FSA myFSA;
  string dataLine;

  myFSA.initializeMachine();
  myFSA.outputID(cout);

  while (getline(cin, dataLine))
  {
    cout << "Input:  " << dataLine;
    dataLine += "%";
    if (myFSA.implementFSA(dataLine))
      cout << " *** valid input ***" << endl << endl;
    else
      cout << " --- invalid input ---" << endl << endl;
  }

  return 0;
}

void FSA::outputID(ostream& out) const
{
  out << name << endl;
  out << "CS 4301" << endl;
  out << "Lab " << labNumber << endl;
  out << description << endl << endl;
}

bool FSA::implementFSA(string dataLine) const
{
  int currentState = 1;
  string::iterator dataItr = dataLine.begin();
  multimap<uint, TableEntry>::const_iterator fsaItr;
    
  while (currentState > 0)
  {
    // Use find to return an iterator to the first entry with a key of
    // currentState
    fsaItr = machine.find(currentState);
    if (fsaItr != machine.end()) // found a key of currentState
    {
      while (fsaItr != machine.upper_bound(currentState) &&
             fsaItr->second.getInputCharacter() != *dataItr)
        ++fsaItr;
      if (fsaItr != machine.upper_bound(currentState))
      {
        currentState = fsaItr->second.getNextState();
        ++dataItr;
      }
      else
        currentState = -1;
    }
    else
      currentState = -1;
  }

  return currentState == 0 && dataItr == dataLine.end();
}
