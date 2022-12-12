// Kangmin Kim
// CS 4301
// Lab 05

#include <fsa.h>

using namespace std;

// I generated 8 states to count even a's and odd b's.
typedef enum {Accept, Start, PositiveOrNegative, Decimal, Hexadecimals, horH } States;

// This function shows my name and description.
FSA::FSA()
{
    name = "Kangmin Kim";
    labNumber = 5;
    description = string("{x | x is a valid hexadecimal integer constant in MASM}");
}
 
// This function initializes Finite States Automata

void FSA::initializeMachine()
{
  /*
   *    ----------------------------------------------next state
   *    -----------------------------------------input symbol  |
   *    -----------------------current state                |  |    
   *  machine.insert(pair<uint, TableEntry>(1, TableEntry('a', 2)));
   */
   
     // transitions on + and -
  machine.insert(pair<uint, TableEntry>(Start, TableEntry('+', PositiveOrNegative)));
  machine.insert(pair<uint, TableEntry>(Start, TableEntry('-', PositiveOrNegative)));
  
  // transitions on Digits
  for (char ch = '0'; ch <= '9'; ++ch)
  {
    machine.insert(pair<uint, TableEntry>(Start, TableEntry(ch, Decimal)));
    machine.insert(pair<uint, TableEntry>(Decimal, TableEntry(ch, Decimal)));
    machine.insert(pair<uint, TableEntry>(Hexadecimals, TableEntry(ch, Decimal)));
    machine.insert(pair<uint, TableEntry>(PositiveOrNegative, TableEntry(ch, Decimal)));
  }
  // transitions on Upper Hexadecimals
  for (char ch = 'A'; ch <= 'F'; ++ch)
  {
  machine.insert(pair<uint, TableEntry>(Decimal, TableEntry(ch, Hexadecimals)));
  machine.insert(pair<uint, TableEntry>(Hexadecimals, TableEntry(ch, Hexadecimals)));
  }
  // transitions on Lower Hexadecimals
  for (char ch = 'a'; ch <= 'f'; ++ch)
  {
  machine.insert(pair<uint, TableEntry>(Decimal, TableEntry(ch, Hexadecimals)));
  machine.insert(pair<uint, TableEntry>(Hexadecimals, TableEntry(ch, Hexadecimals)));
  }
  // transitions on Radix (h,H)
  machine.insert(pair<uint, TableEntry>(Decimal, TableEntry('H', horH)));
  machine.insert(pair<uint, TableEntry>(Decimal, TableEntry('h', horH)));
  machine.insert(pair<uint, TableEntry>(Hexadecimals, TableEntry('H', horH)));
  machine.insert(pair<uint, TableEntry>(Hexadecimals, TableEntry('h', horH)));
 
  // transitions on %
  machine.insert(pair<uint, TableEntry>(horH, TableEntry('%', Accept)));
}
