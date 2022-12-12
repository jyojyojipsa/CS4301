// Kangmin Kim
// CS 4301
// Lab 07

#include <pda.h>
#include <stack>

using namespace std;

PDA::PDA()
{
    name = "Kangmin Kim";
    labNumber = 7;
    description = string("{w | w in {a, b}* and w has twice as many a's as b's}");
}

void PDA::initializeMachine()
{
     // Example from notes
  /*
   *---------------------------------------------------------next state
   *--------------------------------------------------------push pop  |
   *----------------------------------------------input symbol     |  |
   *-----------------------------------------stack symbol    |     |  |
   *------------------------current state               |    |     |  |  */
  machine.insert(pair<uint, TableEntry>(1, TableEntry('@', '%', " *", 0)));
  machine.insert(pair<uint, TableEntry>(1, TableEntry('a', 'a', "+a", 1)));
  machine.insert(pair<uint, TableEntry>(1, TableEntry('@', 'a', "+a", 1)));
  machine.insert(pair<uint, TableEntry>(1, TableEntry('b', 'a', "-b", 1)));
  machine.insert(pair<uint, TableEntry>(1, TableEntry('a', 'b', "-a", 2)));
  machine.insert(pair<uint, TableEntry>(1, TableEntry('@', 'b', "+b", 3)));
  machine.insert(pair<uint, TableEntry>(1, TableEntry('b', 'b', "+b", 3)));
  //-------------------------------------------------------------------
  machine.insert(pair<uint, TableEntry>(2, TableEntry('a', '*', "-a", 1)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry('*', '*', "+b", 1)));
  machine.insert(pair<uint, TableEntry>(3, TableEntry('*', '*', "+b", 1)));
}
