// Kangmin Kim
// CS 4301
// Lab 02

#include <string>

using namespace std;

bool isValid(string s)
{
   // bool check = false;
   uint aCount = 0, bCount = 0; // I declared 2 variables to count if
                                // the inputs are 'a' or 'b'.
                                       
   for(uint i = 0 ; i < s.length(); ++i)
   {
      if(s[i] == 'a')
         ++aCount;
      else if(s[i] == 'b')
         ++bCount;
   }
   
   // {x|x ∈ {a, b} + and x has exactly two a’s and an odd number of b’s}
   if(aCount == 0 || bCount == 0)
      return false;
   else if((aCount % 2 == 0) && (bCount % 2 == 1))
   {
      return true;
   }
   else
      return false;
}