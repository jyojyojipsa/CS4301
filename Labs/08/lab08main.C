#include <pdt.h>
#include <stack>

using namespace std;

int main()
{
  PDT myPDT;
  string dataLine;

  myPDT.initializeMachine();
  myPDT.outputID(cout);

  while (getline(cin, dataLine))
  {
    cout << "Input:  " << dataLine << "  ";
    dataLine += "%";
    cout << "Output:  ";
    if (myPDT.implementPDT(dataLine, cout))
      cout << "     ** accepted **" << endl << endl;
    else
      cout << "     -- NOT accepted --" << endl << endl;
  }

  return 0;
}

void PDT::outputID(ostream& out) const
{
  out << name << endl;
  out << "CS 4301" << endl;
  out << "Lab " << labNumber << endl;
  out << description << endl << endl;
}

bool PDT::implementPDT(string dataLine, ostream& out) const
{
  int currentState = 1;
  string::iterator dataItr = dataLine.begin();
  multimap<uint, TableEntry>::const_iterator pdtItr;
  stack<char> pdtStack;
  bool done;

  pdtStack.push('@');
    
  while (currentState > 0)
  {
    // Use find to return an iterator to the first entry with a key of
    // currentState
    pdtItr = machine.find(currentState);
    if (pdtItr != machine.end()) // found a key of currentState
    {
      done = false;
      while (!done && pdtItr != machine.upper_bound(currentState))
        if (pdtItr->second.getInputSymbol() == '*' &&
            (pdtItr->second.getStackSymbol() == '*' ||
             (!pdtStack.empty() &&
              pdtItr->second.getStackSymbol() == pdtStack.top())))
          done = true;
        else if (pdtItr->second.getInputSymbol() == *dataItr &&
                 (pdtItr->second.getStackSymbol() == '*' ||
                  (!pdtStack.empty() &&
                   pdtItr->second.getStackSymbol() == pdtStack.top())))
          done = true;
        else
          ++pdtItr;

      if (pdtItr != machine.upper_bound(currentState))
      {
        if (pdtItr->second.getStackSymbol() == '*' ||
            (!pdtStack.empty() &&
             pdtItr->second.getStackSymbol() == pdtStack.top()))
        {
          currentState = pdtItr->second.getNextState();
          switch (pdtItr->second.getPushPop()[0])
          {
          case '+':
            pdtStack.push(pdtItr->second.getPushPop()[1]);
            break;
          case '-':
            if (pdtStack.empty())
              currentState = -1;
            if (pdtItr->second.getPushPop()[1] != pdtStack.top())
              currentState = -1;
            pdtStack.pop();
          }
          if (pdtItr->second.getInputSymbol() != '*' && *dataItr != '%')
            ++dataItr;
          if (pdtItr->second.getOutputSymbol() != '*')
            out << pdtItr->second.getOutputSymbol();
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
         pdtStack.size() == 1 && pdtStack.top() == '@';
}
