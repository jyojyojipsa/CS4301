// Kangmin Kim
// CS 4301
// Lab 04

#include <fsa.h>

using namespace std;

// I generated 8 states to count two a's and odd b's.
typedef enum { Accept, S, A, B, AA, BB, AB, AAB } States;

// This function shows my name and description.
FSA::FSA()
{
    name = "Kangmin Kim";
    labNumber = 4;
    description = string("{x | x is in {a, b}+, and x has exactly two a's and an odd number of b's}");
}

// This function initializes Finite States Automata
void FSA::initializeMachine()
{   
    /*
  *    --------------------------------------------next state
  *    ---------------------------------------input symbol  |
  *    ---------------------current state                |  |
  *machine.insert(pair<uint, TableEntry>(1, TableEntry('a', 2)));
  */
   //---------------------------- state S -----------------------------//
    machine.insert(pair<unsigned int, TableEntry>(S, TableEntry('a', A)));
    machine.insert(pair<unsigned int, TableEntry>(S, TableEntry('b', B)));
    
    //---------------------------- state A -----------------------------//
    
    machine.insert(pair<unsigned int, TableEntry>(A, TableEntry('a', AA)));
    machine.insert(pair<unsigned int, TableEntry>(A, TableEntry('b', AB)));
    
    //---------------------------- state B -----------------------------//
    
    machine.insert(pair<unsigned int, TableEntry>(B, TableEntry('a', AB)));
    machine.insert(pair<unsigned int, TableEntry>(B, TableEntry('b', BB)));
    
    //---------------------------- state AA ----------------------------//
    
    machine.insert(pair<unsigned int, TableEntry>(AA, TableEntry('b', AAB)));
    
    //---------------------------- state AB -----------------------------//
    
    machine.insert(pair<unsigned int, TableEntry>(AB, TableEntry('a', AAB)));
    machine.insert(pair<unsigned int, TableEntry>(AB, TableEntry('b', A)));
    
    //---------------------------- state BB -----------------------------//
    
    machine.insert(pair<unsigned int, TableEntry>(BB, TableEntry('a', A)));
    machine.insert(pair<unsigned int, TableEntry>(BB, TableEntry('b', B)));
    
    //---------------------------- state AAB -----------------------------//
    
    machine.insert(pair<unsigned int, TableEntry>(AAB, TableEntry('b', AA)));
    
    // ------------------------transitions on % --------------------------//
    
    machine.insert(pair<unsigned int, TableEntry>(AAB, TableEntry('%', Accept)));
}
