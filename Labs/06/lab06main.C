#include <pda.h>
#include <stack>

using namespace std;

int main()
{
  PDA myPDA;
  string dataLine;

  myPDA.initializeMachine();
  myPDA.outputID(cout);

  while (getline(cin, dataLine))
  {
    cout << "Input:  " << dataLine << "  ";
    dataLine += "%";
    if (myPDA.implementPDA(dataLine))
      cout << "Result:  ** accepted **" << endl << endl;
    else
      cout << "Result:  -- NOT accepted --" << endl << endl;
  }

  return 0;
}

void PDA::outputID(ostream& out) const
{
  out << name << endl;
  out << "CS 4301" << endl;
  out << "Lab " << labNumber << endl;
  out << description << endl << endl;
}

bool PDA::implementPDA(string dataLine) const
{
  int currentState = 1;
  string::iterator dataItr = dataLine.begin();
  multimap<uint, TableEntry>::const_iterator pdaItr;
  stack<char> pdaStack;
  bool done;

  pdaStack.push('@');
    
  while (currentState > 0)
  {
    // Use find to return an iterator to the first entry with a key of
    // currentState
    pdaItr = machine.find(currentState);
    if (pdaItr != machine.end()) // found a key of currentState
    {
      done = false;
      while (!done && pdaItr != machine.upper_bound(currentState))
        if (pdaItr->second.getInputSymbol() == '*' &&
            (pdaItr->second.getStackSymbol() == '*' ||
             (!pdaStack.empty() &&
              pdaItr->second.getStackSymbol() == pdaStack.top())))
          done = true;
        else if (pdaItr->second.getInputSymbol() == *dataItr &&
                 (pdaItr->second.getStackSymbol() == '*' ||
                  (!pdaStack.empty() &&
                   pdaItr->second.getStackSymbol() == pdaStack.top())))
          done = true;
        else
          ++pdaItr;

      if (pdaItr != machine.upper_bound(currentState))
      {
        if (pdaItr->second.getStackSymbol() == '*' ||
            (!pdaStack.empty() &&
             pdaItr->second.getStackSymbol() == pdaStack.top()))
        {
          currentState = pdaItr->second.getNextState();
          switch (pdaItr->second.getPushPop()[0])
          {
          case '+':
            pdaStack.push(pdaItr->second.getPushPop()[1]);
            break;
          case '-':
            if (pdaStack.empty())
              currentState = -1;
            if (pdaItr->second.getPushPop()[1] != pdaStack.top())
              currentState = -1;
            pdaStack.pop();
          }
          if (*dataItr != '%' && pdaItr->second.getInputSymbol() != '*')
            ++dataItr;
        }
        else
          currentState = -1;
      }
      else
        currentState = -1;
    }
    else
      currentState = -1;
  }

  return currentState == 0 && *dataItr == '%' &&
         pdaStack.size() == 1 && pdaStack.top() == '@';
}
