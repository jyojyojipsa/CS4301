// Kangmin Kim
// CS 4301
// Lab 03

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


// At first, I tried using counting integers bool checkers, but
// to make a Finite Automata State, I did second try.

// I declared 8 states. 
typedef enum { S , A , B , AA, BB, AB, AAB, Error } States;

// An FSA for recognizing a language consisting of the even 'a's and odd 'b's

// ↓↓↓↓ is my second try ↓↓↓↓

bool isValid(string s)
{
   States state = S; // Declare S from States enumerator 
   string::iterator itr, end = s.end(); // declare itr to make a for loop
   for (itr = s.begin(); state != Error && itr < end; ++itr)
   switch (state)
   {
      //---------state S------------//
      case S : 
      if(*itr == 'a') 
         state = A;
      else if(*itr == 'b')
         state = B;
      else
         state = Error;
      break;
      //---------state A-----------//
      case A : 
      if(*itr == 'a')
         state = AA;
      else if(*itr == 'b')
         state = AB;
      else
         state = Error;
      break;
      //----------state B----------//
      case B : 
      if(*itr == 'a')
         state = AB;
      else if(*itr == 'b')
         state = BB;
      else
         state = Error;
      break;
      //----------state AA---------//
      case AA : 
      if(*itr == 'a')
         state = Error;
      else if(*itr == 'b')
         state = AAB;
      else
         state = Error;
      break;
      //---------state AB----------//
      case AB : 
      if(*itr == 'a')
         state = AAB;
      else if(*itr == 'b')
         state = A;
      else
         state = Error;
      break;
      //---------state BB---------//
      case BB : 
      if(*itr == 'a')
         state = A;
      else if(*itr == 'b')
         state = B;
      else
         state = Error;
      break;
      //--------state AAB---------//
      case AAB : 
      if(*itr == 'a')
         state = Error;
      else if(*itr == 'b')
         state = AA;
      else
         state = Error;
      break;
      //--------state Error-------//
      case Error: ;
     
   }
   return (itr == end) && (state == AAB);
}


// ↓↓↓ This is my first try ↓↓↓

// bool isValid(string s)
// {


    // States state = S; // Declare S from States enumerator 
    // string::iterator itr, end = s.end(); // declare itr to make a for loop
    // bool Acheck = false, Bcheck = false;
    // unsigned int Acount = 0, Bcount = 0;
    // for (itr = s.begin(); state != C && itr < end; ++itr)
        // switch (state)
        // {
        // case S: if (*itr == 'a')
               // {
            // state = A;
            // Acheck = true;
            // Acount++;
               // }
              // else if (*itr == 'b')
              // {
            // state = B;
            // Bcheck = true;
            // Bcount++;
              // }
              // else
            // state = C;
            // break;
        // case A: 
            // if (*itr == 'a')
            // {
                // state = A;
                // Acount++;
            // }
            // else if (*itr == 'b')
            // {
                // state = B;
                // Bcheck = true;
                // Bcount++;
            // }
            // else
                // state = C;
             // break;
        // case B: 
            // if (*itr == 'a')
            // {
                // state = A;
                // Acheck = true;
                 // Acount++;
            // }
            // else if (*itr == 'b')
            // {
                // state = B;
                // Bcount++;
            // }
            // else
                // state = C;
             // break;
        // case C:;
        // }
        
        
    // return ((itr == end) && (Acount % 2 == 0) && (Bcount % 2 == 1) && Acheck && Bcheck);
// }

// ↓↓↓ This is my third try ↓↓↓

//bool isValid(string s)
//{
//    int state = 1; 
//
//    string::iterator itr, end = s.end();
//
//    for (itr = s.begin(); (state != 8) && (itr < end); ++itr)
//         switch (state)
//        {
//            case 1: 
//            if(*itr == 'a')
//                state = 2;
//                else if(*itr == 'b')  // 
//                state = 3;
//                else
//                   state = 8;
//                break;
//            case 2:
//            if(*itr == 'a') 
//                state = 4;
//            else if(*itr == 'b')
//                state = 6;
//                else
//                   state = 8;
//                break;
//            case 3: 
//            if(*itr == 'a')
//                state = 6;
//                else if(*itr == 'b')
//                state = 5;
//                else
//                   state = 8;
//                break;
//            case 4: 
//            if(*itr == 'a')
//                state = 2;
//                else if(*itr == 'b')
//                state = 7;
//             else
//                state = 8;
//             break;
//            case 5 : 
//            if(*itr == 'a')
//            state = 2;
//            else if(*itr == 'b')
//               state = 3;
//            else
//               state = 8;
//            break;
//            case 6 :
//            if(*itr == 'a')  
//               state = 7;
//               else if(*itr == 'b')
//               state = 2;
//               else
//                  state = 8;
//               break;
//            case 7 :
//            if(*itr == 'a') 
//            state = 6;
//            else if(*itr == 'b')
//               state = 4;
//            else
//               state = 8;
//            break;
//            case 8 :
//        }
//        
//        return ((itr == end) && (state == 7));
//}
