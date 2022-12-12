
// CS 4301
// Lab 09
 
#include <turing.h>
 
using namespace std;
 
Turing::Turing()
{
  name = "";
  labNumber = 9;
  description = "{(x=, x=ans) | x is in {a,b,c}*,\n               ans = 1 if x is of the form a^ib^jc^k where i + k = j and i, j, k >= 0, and\n               ans = 0 otherwise}";
}
 
void Turing::initializeMachine()
{
	//errors on c
  machine.insert(pair<uint, TableEntry>(1, TableEntry(' ', ' ',  1, 1)));
  machine.insert(pair<uint, TableEntry>(1, TableEntry('c', 'c',  1, 2)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry('a', 'a',  1, 2)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry('b', 'b',  1, 2)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry('c', 'c',  1, 2)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry('=', '=',  1, 2)));
  //exit
  machine.insert(pair<uint, TableEntry>(2, TableEntry(' ', '0',  0, 0)));
}