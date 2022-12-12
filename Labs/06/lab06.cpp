// Kangmin Kim
// CS 4301
// Lab 06

#include <pda.h>
#include <stack>

using namespace std;

PDA::PDA()
{
    name = "Kangmin Kim";
    labNumber = 6;
    description = string("{a^ib^jc^k | i + k = j and i,j,k >= 0}");
}

//{a^nb^n| n ≤ m ≤ 3n}
//void PDA::initializeMachine()
//{
//	machine.insert(pair<uint, TableEntry>(1, TableEntry('@', '%', " *", 0)));
//	machine.insert(pair<uint, TableEntry>(1, TableEntry('*', 'a', "+a", 2)));
//	machine.insert(pair<uint, TableEntry>(2, TableEntry('*', 'a', "+a", 4)));
//	machine.insert(pair<uint, TableEntry>(2, TableEntry('*', 'a', "+a", 4)));
//}




//a^nb^mc^(n+m) n>=0 && b >=0
//void PDA::initializeMachine()
//{
//	machine.insert(pair<uint, TableEntry>(1, TableEntry('@', '%', " *", 0)));
//	machine.insert(pair<uint, TableEntry>(1, TableEntry('@', 'a', "+a", 2)));
//	machine.insert(pair<uint, TableEntry>(1, TableEntry('@', 'b', "+b", 3)));
//	machine.insert(pair<uint, TableEntry>(2, TableEntry('a', 'a', "+a", 2)));
//	machine.insert(pair<uint, TableEntry>(2, TableEntry('a', 'b', "+b", 3)));
//	machine.insert(pair<uint, TableEntry>(2, TableEntry('a', 'c', "-a", 4)));
//	machine.insert(pair<uint, TableEntry>(3, TableEntry('b', 'b', "+b", 3)));
//	machine.insert(pair<uint, TableEntry>(3, TableEntry('b', 'c', "-b", 4)));
//	machine.insert(pair<uint, TableEntry>(3, TableEntry('b', 'c', "-b", 4)));
//	machine.insert(pair<uint, TableEntry>(4, TableEntry('a', 'c', "-a", 4)));
//	machine.insert(pair<uint, TableEntry>(4, TableEntry('b', 'c', "-b", 4)));
//	machine.insert(pair<uint, TableEntry>(4, TableEntry('@', '%', " *", 0)));
//}




//a^ib^2i
//void PDA::initializeMachine()
//{
//	machine.insert(pair<uint, TableEntry>(1, TableEntry('@', '%', " *", 0)));
//	machine.insert(pair<uint, TableEntry>(1, TableEntry('@', 'a', "+a", 2)));
//	machine.insert(pair<uint, TableEntry>(2, TableEntry('a', 'a', "+a", 2)));
//	machine.insert(pair<uint, TableEntry>(2, TableEntry('a', 'b', " *", 3)));
//	machine.insert(pair<uint, TableEntry>(3, TableEntry('a', 'b', "-a", 4)));
//	machine.insert(pair<uint, TableEntry>(4, TableEntry('a', 'b', " *", 3)));
//	machine.insert(pair<uint, TableEntry>(4, TableEntry('@', '%', " *", 0)));
//}




 void PDA::initializeMachine()
 {
	 int i;
	 
   // Example from notes
   /*
    *---------------------------------------------------------next state
    *--------------------------------------------------------push pop  |
    *----------------------------------------------input symbol     |  |
    *-----------------------------------------stack symbol    |     |  |
    *------------------------current state               |    |     |  |  */
   machine.insert(pair<uint, TableEntry>(1, TableEntry('@', '%', " *", 0)));
   machine.insert(pair<uint, TableEntry>(1, TableEntry('*', 'a', "+a", 2)));
   machine.insert(pair<uint, TableEntry>(1, TableEntry('*', 'b', "+b", 3)));
   machine.insert(pair<uint, TableEntry>(2, TableEntry('*', 'a', "+a", 2)));
   machine.insert(pair<uint, TableEntry>(2, TableEntry('a', 'b', "-a", 3)));
   machine.insert(pair<uint, TableEntry>(3, TableEntry('a', 'b', "-a", 3)));
   machine.insert(pair<uint, TableEntry>(3, TableEntry('@', '%', " *", 0)));
   machine.insert(pair<uint, TableEntry>(3, TableEntry('*', 'b', "+b", 3)));
   machine.insert(pair<uint, TableEntry>(3, TableEntry('b', 'c', "-b", 4)));
   machine.insert(pair<uint, TableEntry>(4, TableEntry('b', 'c', "-b", 4)));
   machine.insert(pair<uint, TableEntry>(4, TableEntry('@', '%', " *", 0)));
 }
 