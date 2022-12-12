// Kangmin Kim
// CS 4301
// Lab 10
 
#include <turing.h>
 
using namespace std;
 
Turing::Turing()
{
  name = "Kangmin Kim";
  labNumber = 10;
  description = "{(x=, x=ans) | x is in {a,b}* and\n               ans = 1 if x has twice as many a's as b's, and\n               ans = 0 otherwise}";
}

void Turing::initializeMachine()
{
	machine.insert(pair<uint, TableEntry>(1, TableEntry(' ', ' ',  1, 1)));
	//----------------------------moveb---------------------------------
	machine.insert(pair<uint, TableEntry>(1, TableEntry('a','a',  1, 1)));
	machine.insert(pair<uint, TableEntry>(1, TableEntry('b',' ',  1, 2)));
	machine.insert(pair<uint, TableEntry>(2, TableEntry('a', 'a', 1, 2)));
	machine.insert(pair<uint, TableEntry>(2, TableEntry('b', 'b', 1, 2)));
	machine.insert(pair<uint, TableEntry>(2, TableEntry('=', '=', 1, 2)));
	machine.insert(pair<uint, TableEntry>(2, TableEntry(' ', 'b',-1, 3)));
	machine.insert(pair<uint, TableEntry>(3, TableEntry('a', 'a',-1, 3)));
	machine.insert(pair<uint, TableEntry>(3, TableEntry('b', 'b',-1, 3)));
	machine.insert(pair<uint, TableEntry>(3, TableEntry('=', '=',-1, 3)));
	machine.insert(pair<uint, TableEntry>(3, TableEntry(' ', 'b', 1, 1)));
	//----------------------------transit---------------------------------
	machine.insert(pair<uint, TableEntry>(1, TableEntry('=', '=',-1, 4)));
	machine.insert(pair<uint, TableEntry>(4, TableEntry('a', 'a',-1, 4)));
	machine.insert(pair<uint, TableEntry>(4, TableEntry('b', 'b',-1, 4)));
	machine.insert(pair<uint, TableEntry>(4, TableEntry(' ', ' ', 1, 5)));
	//----------------------------movea---------------------------------
	machine.insert(pair<uint, TableEntry>(5, TableEntry('b', 'b', 1, 5)));
	machine.insert(pair<uint, TableEntry>(5, TableEntry('a', ' ', 1, 6)));
	machine.insert(pair<uint, TableEntry>(5, TableEntry('=', '=', 1, 8)));
	machine.insert(pair<uint, TableEntry>(6, TableEntry('a', 'a', 1, 6)));
	machine.insert(pair<uint, TableEntry>(6, TableEntry('b', 'b', 1, 6)));
	machine.insert(pair<uint, TableEntry>(6, TableEntry('=', '=', 1, 6)));
	machine.insert(pair<uint, TableEntry>(6, TableEntry(' ', 'a',-1, 7)));
	machine.insert(pair<uint, TableEntry>(7, TableEntry(' ', 'a', 1, 5)));
	machine.insert(pair<uint, TableEntry>(7, TableEntry('a', 'a',-1, 7)));
	machine.insert(pair<uint, TableEntry>(7, TableEntry('b', 'b',-1, 7)));
	machine.insert(pair<uint, TableEntry>(7, TableEntry('=', '=',-1, 7)));
	//----------------------------aaa------------------------------------
	machine.insert(pair<uint, TableEntry>(8, TableEntry('a', ' ', 1, 9)));
	machine.insert(pair<uint, TableEntry>(9, TableEntry('a', ' ', 1, 9)));
	machine.insert(pair<uint, TableEntry>(9, TableEntry(' ', ' ',-1,10)));
	machine.insert(pair<uint, TableEntry>(10,TableEntry(' ', ' ',-1,10)));
	machine.insert(pair<uint, TableEntry>(10,TableEntry('=', '=', 1,11)));
	//----------------------------b--------------------------------------
	machine.insert(pair<uint, TableEntry>(8, TableEntry('b', 'b', 1,12)));
	machine.insert(pair<uint, TableEntry>(12,TableEntry('a', 'a', 1,12)));
	machine.insert(pair<uint, TableEntry>(12,TableEntry('b', 'b', 1,12)));
	machine.insert(pair<uint, TableEntry>(12,TableEntry(' ', ' ',-1,13)));
	//----------------------------bb-------------------------------------
	machine.insert(pair<uint, TableEntry>(13,TableEntry('b', ' ',-1,14)));
	machine.insert(pair<uint, TableEntry>(14,TableEntry('b', ' ',-1,14)));
	machine.insert(pair<uint, TableEntry>(14,TableEntry('=', '=', 1,11)));
	//----------------------------ba-------------------------------------
	machine.insert(pair<uint, TableEntry>(13,TableEntry('a', ' ',-1,16)));
	//----------------------------bab------------------------------------
	machine.insert(pair<uint, TableEntry>(16,TableEntry('b', ' ',-1,14)));
	//----------------------------baa------------------------------------
	machine.insert(pair<uint, TableEntry>(16,TableEntry('a', ' ',-1,17)));
	machine.insert(pair<uint, TableEntry>(18,TableEntry('=', '=', 1, 8)));
	//----------------------------baab-----------------------------------
	machine.insert(pair<uint, TableEntry>(17,TableEntry('b', ' ',-1,18)));
	machine.insert(pair<uint, TableEntry>(18,TableEntry('b', ' ',-1,14)));
	//----------------------------baaLoop--------------------------------
	machine.insert(pair<uint, TableEntry>(17,TableEntry('a', ' ',-1,19)));
	machine.insert(pair<uint, TableEntry>(19,TableEntry('a', 'a',-1,19)));
	machine.insert(pair<uint, TableEntry>(19,TableEntry('b', 'a',-1,20)));
	machine.insert(pair<uint, TableEntry>(20,TableEntry('=', '=', 1, 8)));
	machine.insert(pair<uint, TableEntry>(20,TableEntry('a', 'a',-1,20)));
	machine.insert(pair<uint, TableEntry>(20,TableEntry('b', 'b',-1,20)));
	//-------------------------------------exit--------------------------
	machine.insert(pair<uint, TableEntry>(8, TableEntry(' ', '1', 0, 0)));
	machine.insert(pair<uint, TableEntry>(11,TableEntry(' ', '0', 0, 0)));

}