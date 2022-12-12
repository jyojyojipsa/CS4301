// Kangmin Kim
// CS 4301
// Lab 09
 
#include <turing.h>
 
using namespace std;
 
Turing::Turing()
{
  name = "Kangmin Kim";
  labNumber = 9;
  description = "{(x=, x=ans) | x is in {a,b,c}*,\n               ans = 1 if x is of the form a^ib^jc^k where i + k = j and i, j, k >= 0, and\n               ans = 0 otherwise}";
}

 
 
void Turing::initializeMachine()
{
  /*
   *-------------------------------------------------------next state
   *----------------------------------------------------------move  |
   *-------------------------------------------write character   |  | 
   *---------------------------------------read character    |   |  |
   *------------------------current state               |    |   |  |   */
  
  machine.insert(pair<uint, TableEntry>(1, TableEntry(' ', ' ',  1, 1)));
  //---------------------------------------------------a----------------
  machine.insert(pair<uint, TableEntry>(1, TableEntry('a', ' ',  1, 2)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry('a', 'a',  1, 2)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry('b', 'b',  1, 2)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry('c', 'c',  1, 2)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry('=', '=',  1, 2)));
  machine.insert(pair<uint, TableEntry>(2, TableEntry(' ', 'a', -1, 3)));
  machine.insert(pair<uint, TableEntry>(3, TableEntry('a', 'a', -1, 3)));
  machine.insert(pair<uint, TableEntry>(3, TableEntry('b', 'b', -1, 3)));
  machine.insert(pair<uint, TableEntry>(3, TableEntry('c', 'c', -1, 3)));
  machine.insert(pair<uint, TableEntry>(3, TableEntry('=', '=', -1, 3)));
  machine.insert(pair<uint, TableEntry>(3, TableEntry(' ', 'a',  1, 1)));
  //---------------------------------------------------b----------------
  machine.insert(pair<uint, TableEntry>(1, TableEntry('b', ' ',  1, 4)));
  machine.insert(pair<uint, TableEntry>(4, TableEntry('a', 'a',  1, 4)));
  machine.insert(pair<uint, TableEntry>(4, TableEntry('b', 'b',  1, 4)));
  machine.insert(pair<uint, TableEntry>(4, TableEntry('c', 'c',  1, 4)));
  machine.insert(pair<uint, TableEntry>(4, TableEntry('=', '=',  1, 4)));
  machine.insert(pair<uint, TableEntry>(4, TableEntry(' ', 'b', -1, 5)));
  machine.insert(pair<uint, TableEntry>(5, TableEntry('a', 'a', -1, 5)));
  machine.insert(pair<uint, TableEntry>(5, TableEntry('b', 'b', -1, 5)));
  machine.insert(pair<uint, TableEntry>(5, TableEntry('c', 'c', -1, 5)));
  machine.insert(pair<uint, TableEntry>(5, TableEntry('=', '=', -1, 5)));
  machine.insert(pair<uint, TableEntry>(5, TableEntry(' ', 'b',  1, 1)));
  //---------------------------------------------------c----------------
  machine.insert(pair<uint, TableEntry>(1, TableEntry('c', ' ',  1, 6)));
  machine.insert(pair<uint, TableEntry>(6, TableEntry('a', 'a',  1, 6)));
  machine.insert(pair<uint, TableEntry>(6, TableEntry('b', 'b',  1, 6)));
  machine.insert(pair<uint, TableEntry>(6, TableEntry('c', 'c',  1, 6)));
  machine.insert(pair<uint, TableEntry>(6, TableEntry('=', '=',  1, 6)));
  machine.insert(pair<uint, TableEntry>(6, TableEntry(' ', 'c', -1, 7)));
  machine.insert(pair<uint, TableEntry>(7, TableEntry('a', 'a', -1, 7)));
  machine.insert(pair<uint, TableEntry>(7, TableEntry('b', 'b', -1, 7)));
  machine.insert(pair<uint, TableEntry>(7, TableEntry('c', 'c', -1, 7)));
  machine.insert(pair<uint, TableEntry>(7, TableEntry('=', '=', -1, 7)));
  machine.insert(pair<uint, TableEntry>(7, TableEntry(' ', 'c',  1, 1)));
    //--------------------------------------------Errors-----------------
  machine.insert(pair<uint, TableEntry>(11, TableEntry('a', 'a', 0, 20)));
  machine.insert(pair<uint, TableEntry>(12, TableEntry('a', 'a', 0, 20)));
  machine.insert(pair<uint, TableEntry>(12, TableEntry('=', '=', 1, 20)));
  machine.insert(pair<uint, TableEntry>(16, TableEntry('c', 'c', 0, 20)));
  machine.insert(pair<uint, TableEntry>(16, TableEntry('=', '=', 1, 20)));
  machine.insert(pair<uint, TableEntry>(20, TableEntry('a', 'a', 1, 20)));
  machine.insert(pair<uint, TableEntry>(20, TableEntry('b', 'b', 1, 20)));
  machine.insert(pair<uint, TableEntry>(20, TableEntry('c', 'c', 1, 20)));
  machine.insert(pair<uint, TableEntry>(20, TableEntry(' ', ' ',-1, 21)));
  machine.insert(pair<uint, TableEntry>(21, TableEntry('a', ' ',-1, 21)));
  machine.insert(pair<uint, TableEntry>(21, TableEntry('b', ' ',-1, 21)));
  machine.insert(pair<uint, TableEntry>(21, TableEntry('c', ' ',-1, 21)));
  machine.insert(pair<uint, TableEntry>(21, TableEntry('=', '=', 1, 22)));
  machine.insert(pair<uint, TableEntry>(22, TableEntry(' ', '0', 0, 0)));
  //---------------------------------------------body-------------------
  machine.insert(pair<uint, TableEntry>(9, TableEntry('a', 'a',  1, 10)));
  machine.insert(pair<uint, TableEntry>(9, TableEntry('b', 'b',  1, 10)));
  machine.insert(pair<uint, TableEntry>(9, TableEntry('c', 'c',  1, 10)));
  machine.insert(pair<uint, TableEntry>(10, TableEntry('a', 'a',  1, 10)));
  machine.insert(pair<uint, TableEntry>(10, TableEntry('b', 'b',  1, 10)));
  machine.insert(pair<uint, TableEntry>(10, TableEntry('c', 'c',  1, 10)));
  machine.insert(pair<uint, TableEntry>(10, TableEntry(' ', ' ', -1, 11)));
  machine.insert(pair<uint, TableEntry>(23, TableEntry('a', 'a',  0, 10)));
  machine.insert(pair<uint, TableEntry>(23, TableEntry('b', 'b',  0, 10)));
  machine.insert(pair<uint, TableEntry>(23, TableEntry('c', 'c',  0, 10)));
  //--------------------------------------------roadtoC-----------------
  machine.insert(pair<uint, TableEntry>(11, TableEntry('c', ' ', -1, 12)));
  machine.insert(pair<uint, TableEntry>(12, TableEntry('c', 'c', -1, 12)));
  machine.insert(pair<uint, TableEntry>(12, TableEntry('b', ' ',  1, 13)));
  machine.insert(pair<uint, TableEntry>(13, TableEntry('c', 'c',  1, 13)));
  machine.insert(pair<uint, TableEntry>(13, TableEntry(' ', ' ', -1, 14)));
  machine.insert(pair<uint, TableEntry>(14, TableEntry('c', ' ', -1, 15)));
  machine.insert(pair<uint, TableEntry>(14, TableEntry(' ', ' ', -1, 23)));
  machine.insert(pair<uint, TableEntry>(15, TableEntry('c', 'c', -1, 15)));
  machine.insert(pair<uint, TableEntry>(15, TableEntry(' ', 'c',  1, 10)));
  //--------------------------------------------roadtoB-----------------
  machine.insert(pair<uint, TableEntry>(11, TableEntry('b', ' ', -1, 16)));
  machine.insert(pair<uint, TableEntry>(14, TableEntry('b', ' ', -1, 16)));
  machine.insert(pair<uint, TableEntry>(16, TableEntry('b', 'b', -1, 16)));
  machine.insert(pair<uint, TableEntry>(16, TableEntry('a', ' ',  1, 17)));
  machine.insert(pair<uint, TableEntry>(17, TableEntry('b', 'b',  1, 17)));
  machine.insert(pair<uint, TableEntry>(17, TableEntry(' ', ' ', -1, 18)));
  machine.insert(pair<uint, TableEntry>(18, TableEntry('b', ' ', -1, 19)));
  machine.insert(pair<uint, TableEntry>(18, TableEntry(' ', ' ', -1, 23)));
  machine.insert(pair<uint, TableEntry>(19, TableEntry('b', 'b', -1, 19)));
  machine.insert(pair<uint, TableEntry>(19, TableEntry(' ', 'b',  1, 10)));
  //--------------------------------------------Errors-----------------
  machine.insert(pair<uint, TableEntry>(11, TableEntry('a', 'a', 0, 20)));
  machine.insert(pair<uint, TableEntry>(12, TableEntry('a', 'a', 0, 20)));
  machine.insert(pair<uint, TableEntry>(12, TableEntry('=', '=', 1, 20)));
  machine.insert(pair<uint, TableEntry>(16, TableEntry('c', 'c', 0, 20)));
  machine.insert(pair<uint, TableEntry>(16, TableEntry('=', '=', 1, 20)));
  machine.insert(pair<uint, TableEntry>(20, TableEntry('a', 'a', 1, 20)));
  machine.insert(pair<uint, TableEntry>(20, TableEntry('b', 'b', 1, 20)));
  machine.insert(pair<uint, TableEntry>(20, TableEntry('c', 'c', 1, 20)));
  machine.insert(pair<uint, TableEntry>(20, TableEntry(' ', ' ',-1, 21)));
  machine.insert(pair<uint, TableEntry>(21, TableEntry('a', ' ',-1, 21)));
  machine.insert(pair<uint, TableEntry>(21, TableEntry('b', ' ',-1, 21)));
  machine.insert(pair<uint, TableEntry>(21, TableEntry('c', ' ',-1, 21)));
  machine.insert(pair<uint, TableEntry>(21, TableEntry('=', '=', 1, 22)));
  machine.insert(pair<uint, TableEntry>(22, TableEntry(' ', '0', 0, 0)));
  //---------------------------------------------------exit------------
  machine.insert(pair<uint, TableEntry>(1, TableEntry('=', '=',  1, 9)));
  machine.insert(pair<uint, TableEntry>(9, TableEntry(' ', '1',  0, 0)));
  machine.insert(pair<uint, TableEntry>(10,TableEntry(' ', ' ', -1,23)));
  machine.insert(pair<uint, TableEntry>(23,TableEntry('=', '=',  1, 9)));
}
