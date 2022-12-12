

#include "stage2.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>

// Kangmin Kim and Jeff Caldwell
// CS 4301
// Compiler - Stage2

using namespace std;

Compiler::Compiler(char** argv)
{
  // open sourceFile using argv[1]				
  sourceFile.open(argv[ 1 ]);
  // open listingFile using argv[2]
  listingFile.open(argv[ 2 ]);
  // open objectFile using argv[3]
  objectFile.open(argv[ 3 ]);
}

Compiler::~Compiler()
{
  // close all open files and Print the symbol table
  sourceFile.close();
  listingFile.close();
  objectFile.close();
}

void Compiler::createListingHeader()
{
  // line numbers and source statements should be aligned under the headings
  time_t now = time(NULL);
  listingFile << "STAGE2:  " << "Kangmin Kim, Jeff Caldwell   " << ctime(&now) << endl;
  listingFile << "LINE NO." << setw(30) << "SOURCE STATEMENT" << endl;			//<<<<<<<setw, work on it
  listingFile << endl;
}

void Compiler::parser()
{
  nextChar();
  // ch must be initialized to the first character of the source file

  // set the character to the first character in the file
  if (nextToken() != "program")
  {
    processError("keyword \"program\" expected");
  }
  // a call to nextToken() has two effects
  // (1) the variable, token, is assigned the value of the next token
  // (2) the next token is read from the source file in order to make
  // the assignment. The value returned by nextToken() is also
  // the next token.

  prog();
  //parser implements the grammar rules, calling first rule
}

void Compiler::createListingTrailer()
{
  // print "COMPILATION TERMINATED", "# ERRORS ENCOUNTERED"
  listingFile << endl << "COMPILATION TERMINATED" << right << setw(7) << errorCount << " ERRORS ENCOUNTERED" << endl;
}

//token should be "program"
void Compiler::prog()
{
  if (token != "program")
  {
    processError("keyword \"program\" expected");
  }

  progStmt();

  if (token == "const")
  {
    consts();
  }

  if (token == "var")
  {
    vars();
  }

  if (token != "begin")
  {
    processError("keyword \"begin\" expected");
  }

  beginEndStmt();
}
void Compiler::processError(string err)
{
  // for processing errors outputs at the bottom with the specified error
  //Output err to listingFile
  //Call exit() to terminate program
  listingFile << endl << "Error: Line " << lineNo << ": " << err << endl;
  errorCount += 1;
  listingFile << "\nCOMPILATION TERMINATED      " << errorCount << " ERROR ENCOUNTERED" << endl;
  exit(-1);
}

string Compiler::genInternalName(storeTypes storeType) const
{
  static int I = 0; // integer
  static int B = 0; // boolean
  static int U = 0; // unknown
  string internalName;

  if (storeType == PROG_NAME)
  {
    internalName = "P0";
  }
  else if (storeType == INTEGER)
  {
    internalName = "I" + to_string(I);
    I++;
  }

  else if (storeType == BOOLEAN)
  {
    internalName = "B" + to_string(B);
    B++;
  }
  else if (storeType == UNKNOWN)
  {
    internalName = "U" + to_string(U);
    U++;
  }

  return internalName;
}

//token should be "program"
void Compiler::progStmt()
{
  string x;

  if (token != "program")
  {
    processError("keyword \"program\" expected");
  }

  x = nextToken(); //may need to change to nextToken()

  // if token is not a non_key_id
  if (!isNonKeyId(token))
  {
    processError("program name expected");
  }

  if (nextToken() != ";")
  {
    processError("semicolon expected");
  }

  nextToken();
  code("program", x);
  insert(x, PROG_NAME, CONSTANT, x, NO, 0);

}

void Compiler::consts() // 3. CONSTS → 'const' CONST_STMTS
{                       //   → ε
  if (token != "const")
  {
    processError("keyword \"const\" expected");
  }
  if (!isNonKeyId(nextToken()))
  {
    processError("non-keyword identifier must follow \"const\"");
  }
  constStmts();
}

void Compiler::vars() // 4. VARS → 'var' VAR_STMTS
{                     //   → ε
  if (token != "var")
  {
    processError("keyword \"var\" expected");
  }

  if (!isNonKeyId(nextToken()))
  {
    processError("non-keyword identifier must follow \"var\"");
  }
  varStmts();
}

bool beginEndCheck = false;
int  beginEndCount = 0;

void Compiler::beginEndStmt()
{
  if (token != "begin")
  {
    processError("begin expected");
  }

  nextToken();
  execStmts();
  if (token != "end")
  {
    processError("error");
  }
  nextToken();


  if (token == ".")
  {
    code("end", ".");
  }
  else if (token == ";" && beginEndCheck == false && beginEndCount == 0)
  {
    processError("{Final end lacks period, has semicolon instead.}");
  }
  else if (token == ";")
  {
    return;
  }

  else
  {
    processError("'.' or ';' expected following \"end\"");
  }
}
// token should be a non_key_id
void Compiler::constStmts() // 6. CONST_STMTS → NON_KEY_IDx '='( NON_KEY_IDy |
// 'not' NON_KEY_IDy | LITy ) ';'
{              //   insert(x,whichType(y),CONSTANT,whichValue(y),YES,1)
  string x, y; //   ( CONST_STMTS | ε )

  if (!isNonKeyId(token))
  {
    processError("non-keyword identifier expected");
  }

  // check for illegal '_' at end of variable name
  if (token.back() == '_')
  {
    processError("illegal character '_'");
  }

  // check for '__' in middle of var/const
  if (token.find("__") != string::npos)
  {
    processError("illegal character '_'");
  }

  x = token;

  if (nextToken() != "=")
  {
    processError("\"=\" expected");
  }

  y = nextToken();

  if (y != "+" && y != "-" && y != "not" && !(isNonKeyId(y)) && !(isBoolean(y)) && !(isInteger(y)))
  {
    processError("token to right of \"=\" illegal");
  }

  if (y == "+" || y == "-")
  {
    string next = nextToken();

    if (!isInteger(next))
    {
      processError("integer expected after sign");
    }
    y = y + token;
  }

  if (y == "not")
  {
    nextToken();

    if (isBoolean(token) || isNonKeyId(token))
    {
      if (token == "true")
      {
        y = "false";
      }
      else if (token == "false")
      {
        y = "true";
      }
      else if (isNonKeyId(token))
      {
        if (symbolTable.at(token).getDataType() != BOOLEAN)
        {
          processError("boolean expected after \"not\"");
        }
        else
        {
          y = (symbolTable.at(token).getValue() == "0") ? "true" : "false";
        }
      }
    }
    else
    {
      processError("boolean expected after \"not\"");
    }
  }

  if (nextToken() != ";")
  {
    processError("semicolon expected");
  }

  storeTypes currentType = whichType(y);

  if (currentType != INTEGER && currentType != BOOLEAN)
  {
    processError("data type of token on the right - hand side must be INTEGER "
                 "or BOOLEAN");
  }

  insert(x, whichType(y), CONSTANT, whichValue(y), YES, 1);

  x = nextToken();

  if (x != "begin" && x != "var" && !(isNonKeyId(x)))
  {
    processError("non - keyword identifier, \"begin\", or \"var\" expected");
  }

  if (isNonKeyId(x))
  {
    constStmts();
  }
}


void Compiler::varStmts() // token should be NON_KEY_ID
{
  string x, y;
  if (!isNonKeyId(token))
  {
    processError("non-keyword identifier expected");
  }

  // check for illegal '_' at end of variable name
  if (token.back() == '_')
  {
    processError("illegal character '_'");
  }

  // check for '__' in middle of var/const
  if (token.find("__") != string::npos)
  {
    processError("illegal character '_'");
  }

  x = ids();

  if (token != ":")
  {
    processError("\":\" expected");
  }

  if (nextToken() != "integer" && token != "boolean")
  {
    processError("illegal type follows \":\"");
  }

  y = token;

  if (nextToken() != ";")
  {
    processError("semicolon expected");
  }

  if (y == "integer")
  {
    insert(x, INTEGER, VARIABLE, "1", YES, 1);
  }
  else
  {
    insert(x, BOOLEAN, VARIABLE, "1", YES, 1);
  }

  if (nextToken() != "begin" && !(isNonKeyId(token)))
  {
    processError("non-keyword identifier or \"begin\" expected");
  }

  if (isNonKeyId(token))
  {
    varStmts();
  }
}
string Compiler::ids() // 8. IDS → NON_KEY_ID ( ',' IDS | ε )
{
  string temp, tempString;

  if (!isNonKeyId(token))
  {
    processError("non-keyword identifier expected");
  }

  tempString = token;
  temp = token;

  if (nextToken() == ",")
  {
    if (!isNonKeyId(nextToken()))
    {
      processError("non-keyword identifier expected");
    }

    tempString = temp + "," + ids();
  }
  return tempString;
}

/** STAGE 1 PRODUCTIONS **/
void Compiler::execStmts() // -> EXEC_STMT | EXEC_STMTS
{                          // -> ε
  if (token[ 0 ] == '$')
  {

  }
  if (isNonKeyId(token) || token == "read" || token == "write" || token == "begin" || token == "if" || token == "while" || token == "repeat" || token == ";")
  {
    execStmt();
    execStmts();
  }

  else if (token == "end")
  {

  }

  else if (token == "until")
  {

  }

  else
  {
    processError("one of \";\", \"begin\", \"if\", \"read\", \"repeat\", \"while\", \"write\", \"end\", or \"until\" expected");		//error here
  }


}


void Compiler::execStmt()
{
  if (isNonKeyId(token))
  {
    assignStmt();
  }
  else if (token == "begin")
  {
    beginEndCount++;
    beginEndCheck = true;
    beginEndStmt();
  }
  else if (token == "end")
  {
    beginEndCount--;
    if (beginEndCount == 0)
      beginEndCheck = false;
    return;
  }
  else if (token == "read")
  {
    readStmt();
  }
  else if (token == "write")
  {
    writeStmt();
  }
  if (token == "if")
  {
    ifStmt();
  }
  else if (token == "while")
  {
    whileStmt();
  }
  else if (token == "repeat")
  {
    repeatStmt();
  }
  else if (token == ";")
  {
    nullStmt();
  }
  else
  {
    processError("non-keyword id, \"read\", or \"write\" expected ");
  }
}

void Compiler::assignStmt()
{
  string op2, op1;
  if (!isNonKeyId(token))
  {
    processError("non - keyword identifier expected");
  }
  //Token must be defined
  if (symbolTable.count(token) == 0)
  {
    processError("reference to undefined variable");
  }

  pushOperand(token);

  nextToken();

  if (token != ":=")
  {
    processError("':=' expected; found " + token);
  }
  else
  {
    pushOperator(token);
    // pushOperator(":=");
  }
  nextToken();

  if (token != "not" && !isBoolean(token) && token != "(" && token != "+" && !isInteger(token)
     && token != "-" && !isNonKeyId(token) && token != ";")
  {
    processError("one of \"*\", \"and\", \"div\", \"mod\", \")\", \"+\", \"-\", \";\", \"<\", \"<=\", \"<>\", \"=\", \">\", \">=\", or \"or\" expected");
  }
  else
  {
    express();
  }
  op2 = popOperand();
  op1 = popOperand();
  code(popOperator(), op2, op1);
}

void Compiler::readStmt()
{
  string list;          // read list
  string listItem = ""; // list item
  uint i;               // list counter

  // double check for "read" token
  if (token != "read")
  {
    processError("keyword \"read\" expected");
  }

  // We have a read token. Advance to next token.
  nextToken();

  // Make sure it's a "("
  if (token != "(")
  {
    processError("\"(\" expected");
  }

  else
  {
    // We have a left paren. Advance token.
    nextToken();

    // collect non token ids, will advance token
    list = ids();

    // loop through the characters of the list
    for (i = 0; i < list.length(); i++)
    {
      if (list[ i ] == ',')
      {
        // if we have a ',', code current list item
        code("read", listItem);

        // reset list item for next characters
        listItem = "";
      }
      else
      {
        // if we don't have a ',', add characters to the list item
        listItem += list[ i ];
      }
    }

    // code current list item
    code("read", listItem);

    // look for a right paren
    // call to ids() advanced token, so no need to advance now
    if (token != ")")
    {
      processError("',' or ')' expected after non-keyword identifier");
    }

    // advance token
    nextToken();

    // check for semicolon
    if (token != ";")
    {
      processError("';' expected");
    }
  }
}

void Compiler::writeStmt()
{
  string list;          // read list
  string listItem = ""; // list item
  uint i;               // list counter

  // double check for "write" token
  if (token != "write")
  {
    processError("keyword \"write\" expected");
  }

  // We have a write token. Advance to next token.
  nextToken();

  // Make sure it's a "("
  if (token != "(")
  {
    processError("\"(\" expected");
  }

  // We have a left paren. Advance token.
  nextToken();

  // collect non token ids, will advance token
  list = ids();

  // loop through the characters of the list
  for (i = 0; i < list.length(); i++)
  {
    if (list[ i ] == ',')
    {
      // if we have a ',', code current list item
      code("write", listItem);

      // reset list item for next characters
      listItem = "";
    }
    else
    {
      // if we don't have a ',', add characters to the list item
      listItem += list[ i ];
    }
  }

  // code current list item
  code("write", listItem);

  // look for a right paren
  // call to ids() advanced token, so no need to advance now
  if (token != ")")
  {
    processError("',' or ')' expected after non-keyword identifier");
  }

  // advance token
  nextToken();

  // check for semicolon
  if (token != ";")
  {
    processError("';' expected");
  }

}

//done //stage 1 production 9
void Compiler::express()
{
  if (token != "(" && !isBoolean(token) && token != "not" && token != "+" && token != "-" && !isInteger(token) && !isNonKeyId(token))
  {
    processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", non - keyword identifier or integer expected");
  }

  term();

  if (token == "=" || token == "<" || token == ">" || token == ">=" || token == "<=" || token == "<>")
  {
    expresses();
  }
}
// stage 1, production 10
void Compiler::expresses()
{
  string x = "";
  string op1, op2;
  if (token != "=" && token != "<" && token != ">" && token != "<>" && token != "<=" && token != ">=")
  {
    processError("\"=\", \"<>\", \"<=\", \">=\", \"<\", or \">\" expected");
  }
  pushOperator(token);
  nextToken();

  if (!isBoolean(token) && !isInteger(token) && !isNonKeyId(token) && token != "+" && token != "not"
    && token != "-" && token != "(")
  {
    processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", integer, or non - keyword identifier expected");
  }
  else
  {
    term();
  }
  op1 = popOperand();
  op2 = popOperand();

  code(popOperator(), op1, op2);

  if (token == "<>" || token == "<" || token == ">" || token == "=" || token == "<=" || token == ">=")
  {
    expresses();
  }
}

// stage 1, production 11
void Compiler::term()
{
  if (token != "not" && !isBoolean(token) && token != "(" && token != "+"
    && token != "-" && !isInteger(token) && !isNonKeyId(token))
  {
    processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", integer, or non - keyword identifier expected");
  }
  factor();

  if (token == "-" || token == "or" || token == "+")
  {
    terms();
  }
}

// stage 1, production 12
void Compiler::terms()
{
  string x = "";
  string op1, op2;

  if (token != "or" && token != "+" && token != "-")
  {
    processError("\"+\", \"-\", or \"or\" expected");
  }
  pushOperator(token);
  nextToken();

  if (token != "-" && !isInteger(token) && !isNonKeyId(token)
    && token != "not" && !isBoolean(token) && token != "(" && token != "+")
  {
    processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", integer, or non - keyword identifier expected");
  }
  else
  {
    factor();
  }
  op1 = popOperand();
  op2 = popOperand();
  code(popOperator(), op1, op2);

  if (token == "-" || token == "+" || token == "or")
  {
    terms();
  }
}

//stage 1 production 13
void Compiler::factor()
{
  if (token != "not" && token != "true" && token != "false" && token != "(" && token != "+" && token != "-" && !isInteger(token) && !isNonKeyId(token))
  {
    processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", INTEGER, or NON_KEY_ID expected");
  }

  part();

  if (token == "*" || token == "div" || token == "mod" || token == "and")
  {
    factors();
  }

  if (token == "<>" || token == "=" || token == "<=" || token == ">=" || token == "<" || token == ">" || token == ")" || token == "," || token == ";" || token == "-" || token == "+" || token == "or" || token == "begin" || token == "then" || token == "do")
  {

  }
  else
  {
    processError("one of \"*\", \"and\", \"div\", \"mod\", \")\", \"+\", \"-\", \";\", \"<\", \"<=\", \"<>\", \"=\", \">\", \">=\", or \"or\" expected");
  }

}

// stage 1, production 14
void Compiler::factors()
{
  string x = "";
  string op1, op2;
  if (token != "*" && token != "mod" && token != "div" && token != "and")
  {
    processError("\"*\", \"div\", \"mod\", or \"and\" expected");
  }
  pushOperator(token);
  nextToken();

  if (token != "not" && !isBoolean(token) && !isInteger(token) && !isNonKeyId(token) && token != "+" && token != "-" && token != "(")
  {
    processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", integer, or non - keyword identifier expected");
  }
  else
  {
    part();
  }
  op1 = popOperand();
  op2 = popOperand();
  code(popOperator(), op1, op2);
  if (token == "*" || token == "mod" || token == "and" || token == "div")
  {
    factors();
  }
}
// stage 1, production 15
void Compiler::part()
{
  string x = "";
  if (token == "not")
  {
    nextToken();
    if (token == "(")
    {
      nextToken();
      if (token != "-" && !isInteger(token) && !isNonKeyId(token) && token != "not"
        && !isBoolean(token) && token != "(" && token != "+")
      {
        processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", integer, or non - keyword identifier expected");
      }
      express();
      if (token != ")")
      {
        processError(") expected; found " + token);
      }
      nextToken();
      code("not", popOperand());
    }

    else if (isBoolean(token))
    {
      if (token == "true")
      {
        pushOperand("false");
        nextToken();
      }
      else
      {
        pushOperand("true");
        nextToken();
      }
    }

    else if (isNonKeyId(token))
    {
      code("not", token);
      nextToken();
    }
  }

  else if (token == "+")
  {
    nextToken();
    if (token == "(")
    {
      nextToken();
      if (token != "-" && !isInteger(token) && !isNonKeyId(token)
        && !isBoolean(token) && token != "not" && token != "(" && token != "+")
      {
        processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", integer, or non - keyword identifier expected");
      }
      express();
      if (token != ")")
      {
        processError("expected ')'; found " + token);
      }
      nextToken();
    }
    else if (isInteger(token) || isNonKeyId(token))
    {
      pushOperand(token);
      nextToken();
    }

    else
    {
      processError("expected '(', integer, or non-keyword id; found " + token);
    }
  }

  else if (token == "-")
  {
    nextToken();
    if (token == "(")
    {
      nextToken();
      if (token != "-" && !isInteger(token) && !isNonKeyId(token) && token != "not"
        && !isBoolean(token) && token != "(" && token != "+")
      {
        processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", integer, or non - keyword identifier expected");
      }
      express();
      if (token != ")")
      {
        processError("expected ')'; found " + token);
      }
      nextToken();
      code("neg", popOperand());
    }
    else if (isInteger(token))
    {
      pushOperand("-" + token);
      nextToken();
    }
    else if (isNonKeyId(token))
    {
      code("neg", token);
      nextToken();
    }
  }

  else if (token == "(")
  {
    nextToken();
    if (!isInteger(token) && !isBoolean(token) && !isNonKeyId(token) && token != "(" && token != "+"
      && token != "-" && token != "not")
    {
      processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", integer, or non - keyword identifier expected");
    }
    express();
    if (token != ")")
    {
      processError(") expected; found " + token);
    }
    nextToken();
  }

  else if (isNonKeyId(token) || isInteger(token) || isBoolean(token))
  {
    pushOperand(token);
    nextToken();
  }

  else
  {
    processError("\"not\", \"true\", \"false\", \"(\", \"+\", \"-\", integer, boolean, or non - keyword identifier expected");
  }
}

/** STAGE 2 PRODUCTIONS **/

// stage 2, production 3
void Compiler::ifStmt()
{
  if (token != "if")
  {
    processError("if expected; found " + token);
  }
  nextToken();
  express();

  if (token != "then")
  {
    processError("then expected; found " + token);
  }

  string temp = popOperand();
  code("then", temp);
  nextToken();

  if (isNonKeyId(token) || token == "read" || token == "write" || token == "if" || token == "while" || token == "repeat" || token == ";" || token == "begin")
  {
    execStmt();
  }

  elsePt();
}


// stage 2, production 4
void Compiler::elsePt()
{
  if (token == "else")
  {
    string temp = popOperand();
    code("else", temp);
    nextToken();

    execStmt();
    code("post_if", popOperand());
  }
  else if (isNonKeyId(token) || token == "end" || token == "write" || token == "read" || token == "repeat" || token == "if" || token == "while" || token == "begin" || token == "until" || token == ";")
  {
    code("post_if", popOperand());
  }
  else
  {
    processError("illegal character");
  }
}

// stage 2, production 5
void Compiler::whileStmt()
{
  if (token != "while")
  {
    processError("while expected");
  }

  code("while");
  nextToken();
  express();

  if (token != "do")
  {
    processError("do expected");
  }

  code("do", popOperand());

  nextToken();

  execStmt();

  string op2 = popOperand();

  string op1 = popOperand();

  code("post_while", op2, op1);

}

void Compiler::repeatStmt()
{
  if (token != "repeat")
  {
    processError("received " + token + " expected repeat");
  }

  code("repeat");
  nextToken();

  if (!isNonKeyId(token) && token != "read" && token != "write" && token != "end" && token != "write" && token != "read" && token != "repeat" && token != "if" && token != "while" && token != "begin" && token != "until" && token != ";")
  {
    processError("error1");
  }

  execStmts();

  if (token != "until")
  {
    processError("error2" + token);
  }

  nextToken();
  express();
  string op2 = popOperand();
  string op1 = popOperand();

  code("until", op2, op1);

  if (token != ";")
  {
    processError("received " + token + " expected ;");
  }
}

// stage 2, production 7
void Compiler::nullStmt()
{
  if (token != ";")
  {
    processError("received " + token + " expected ;");
  }

  nextToken();
}

/** END PRODUCTIONS **/

/** STACK FUNCTIONS **/

void Compiler::pushOperator(string op)
{
  operatorStk.push(op);
}

string Compiler::popOperator() // pop name from operatorStk
{
  string op;

  if (!operatorStk.empty())
  {
    op = operatorStk.top();
    operatorStk.pop();
  }
  else
  {
    processError("operator stack underflow");
  }
  return op;
}

void Compiler::pushOperand(string op) // push name onto operatorStk
{
  if (symbolTable.count(op) == 0)
  {
    if (isInteger(op) || isBoolean(op))
    {
      insert(op, whichType(op), CONSTANT, whichValue(op), YES, 1);
    }
  }
  operandStk.push(op);
}

string Compiler::popOperand() // pop name from operandStk
{
  string op;
  if (!operandStk.empty())
  {
    op = operandStk.top();
    operandStk.pop();
  }
  else
  {
    processError("operand stack underflow");
  }

  return op;
}

/** TYPE CHECKING FUNCTIONS **/
bool Compiler::isKeyword(string s) const
{

  // instead of using a crazy, long string of conditional operators (||),
  // just make an array and loop through that
  string keywords[ 23 ] = {"program", "const", "var", "integer", "boolean", "begin", "end", "true",
    "false", "not", "mod", "div", "and", "or", "read", "write", "if", "do", "repeat", "then", "until", "else", "while"};

  int len = *(&keywords + 1) - keywords; // length of keywords

  for (int i = 0; i < len; i++)
  {
    if (keywords[ i ] == s)
    {
      return true;
    }
  }

  return false;
}



bool Compiler::isSpecialSymbol(char c) const
{
  char symbols[ 12 ] = {':', ',', ';', '=', '+', '-', '.', '*', '(', ')', '>', '<'};

  int len = *(&symbols + 1) - symbols;

  for (int i = 0; i < len; i++)
  {
    if (symbols[ i ] == c)
    {
      return true;
    }
  }

  return false;
}



bool Compiler::isNonKeyId(string s) const
{
  if (!isInteger(s) && !isKeyword(s) && !isSpecialSymbol(s[ 0 ]))
  {
    return true;
  }

  return false;
}

bool Compiler::isInteger(string s) const
{
  // Check for '+' or '-' without digits
  if (s.length() == 1)
  {
    if (s == "+" || s == "-")
    {
      return false;
    }
  }

  for (uint i = 0; i < s.length(); i++)
  {
    // if the first character is not a '+' or a '-'
    // of if any character is not a digit, it is not an integer
    if (!(isdigit(s[ i ]) || s[ 0 ] == '+' || s[ 0 ] == '-'))
    {
      return false;
    }
  }

  // if we made it this far we have an integer
  return true;
}


bool Compiler::isBoolean(string s) const
{
  if (s == "true" || s == "false")
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Compiler::isLiteral(string s) const // 10. LIT → INTEGER | BOOLEAN | 'not'
// BOOLEAN | '+' INTEGER | '-' INTEGER
{
  if (isInteger(s) || isBoolean(s) || s.front() == '+' || s.front() == '-' || s == "not")
  {
    return true;
  }

  return false;
}

void Compiler::insert(string externalName, // create symbol table entry for each identifier in list
                      storeTypes inType,   // of external names
                      modes inMode,        // Multiple inserted names are illegal
                      string inValue, allocation inAlloc, int inUnits)
{
  string name;
  uint listName = 0;

  while (listName < externalName.length())
  {
    name = "";
    while (name == "")
    {
      while (listName < externalName.length() && externalName[ listName ] != ',')
      {
        name += externalName[ listName ];
        listName += 1;
      }

      listName += 1;

      name = name.substr(0, 15);

      if (symbolTable.count(name) > 0)
      {
        processError("symbol x is multiply defined");
      }

      else if (isKeyword(name) && name != "true" && name != "false")
      {
        processError("illegal use of keyword");
      }

      else
      {
        if (name == "true" || name == "TRUE")
        {
          symbolTable.insert({"true", SymbolTableEntry("TRUE", inType, inMode, inValue, inAlloc, inUnits)});
        }
        else if (name == "false" || name == "FALSE")
        {
          symbolTable.insert({"false", SymbolTableEntry("FALSE", inType, inMode, inValue, inAlloc, inUnits)});
        }
        else if (isupper(name[ 0 ]))
        {
          symbolTable.insert({name, SymbolTableEntry(name, inType, inMode, inValue, inAlloc, inUnits)});
        }
        else
        {
          symbolTable.insert({name, SymbolTableEntry(genInternalName(inType), inType, inMode, inValue, inAlloc, inUnits)});
        }
      }
    }

    if (symbolTable.size() > 256)
    {
      processError("symbol table cannot exceed 256");
    }
  }
}

storeTypes Compiler::whichType(string name) // tells which data type a name has
{                                           // 9. TYPE → 'integer'
  storeTypes type;                          //		  → 'boolean'

  if (isLiteral(name))
  {
    if (isInteger(name))
    {
      type = INTEGER;
    }
    else if (isBoolean(name))
    {
      type = BOOLEAN;
    }
  }
  else // name is an identifier and hopefully a constant
  {
    if (symbolTable.find(name) != symbolTable.end())
    {
      type = symbolTable.find(name)->second.getDataType();
    }
    else
    {
      processError("variable " + name + " is undefined");
    }
  }
  return type;
}

string Compiler::whichValue(string name)
{
  string value;
  if (isLiteral(name))
  {
    if (name == "false")
    {
      value = "0";
    }
    else if (name == "true")
    {
      value = "-1";
    }
    else
      value = name;
  }
  else // name is an identifier and hopefully a constant
  {
    if (symbolTable.find(name) != symbolTable.end())
    {
      value = symbolTable.at(name).getValue();
    }
    else
    {
      processError("constant " + name + " is undefined");
    }
  }
  return value;
}

/** EMIT FUNCTIONS **/

void Compiler::code(string op, string operand1, string operand2)
{
  if (op == "program")
  {
    emitPrologue(operand1);
  }
  else if (op == "end")
  {
    emitEpilogue();
  }
  else if (op == "read")
  {
    emitReadCode(operand1, operand2);
  }
  else if (op == "write")
  {
    emitWriteCode(operand1, operand2);
  }
  else if (op == "+")
  { // binary plus
    emitAdditionCode(operand1, operand2);
  }
  else if (op == "-")
  { // binary minus
    emitSubtractionCode(operand1, operand2);
  }
  else if (op == "neg")
  { // unary minus
    emitNegationCode(operand1, operand2);
  }
  else if (op == "not")
  {
    emitNotCode(operand1, operand2);
  }
  else if (op == "*")
  {
    emitMultiplicationCode(operand1, operand2);
  }
  else if (op == "div")
  {
    emitDivisionCode(operand1, operand2);
  }
  else if (op == "mod")
  {
    emitModuloCode(operand1, operand2);
  }
  else if (op == "and")
  {
    emitAndCode(operand1, operand2);
  }
  else if (op == "or")
  {
    emitOrCode(operand1, operand2);
  }
  else if (op == "<")
  {
    emitLessThanCode(operand1, operand2);
  }
  else if (op == ">")
  {
    emitGreaterThanCode(operand1, operand2);
  }
  else if (op == "<=")
  {
    emitLessThanOrEqualToCode(operand1, operand2);
  }
  else if (op == ">=")
  {
    emitGreaterThanOrEqualToCode(operand1, operand2);
  }
  else if (op == "<>")
  {
    emitInequalityCode(operand1, operand2);
  }
  else if (op == "=")
  {
    emitEqualityCode(operand1, operand2);
  }
  else if (op == ":=")
  {
    emitAssignCode(operand1, operand2);
  }
  else if (op == "then")
  {
    emitThenCode(operand1, "");
  }
  else if (op == "else")
  {
    emitElseCode(operand1, "");
  }
  else if (op == "post_if")
  {
    emitPostIfCode(operand1, "");
  }
  else if (op == "while")
  {
    emitWhileCode("", "");
  }
  else if (op == "do")
  {
    emitDoCode(operand1, "");
  }
  else if (op == "post_while")
  {
    emitPostWhileCode(operand1, operand2);
  }
  else if (op == "repeat")
  {
    emitRepeatCode("", "");
  }
  else if (op == "until")
  {
    emitUntilCode(operand1, operand2);
  }
  else
  {
    processError("undefined constant");
  }
}

void Compiler::emit(string label, string instruction, string operands, string comment)
{
  //   Turn on left justification in objectFile
  //   Output label in a field of width 8
  //   Output instruction in a field of width 8
  //   Output the operands in a field of width 24
  //   Output the comment
  objectFile << left << setw(8) << label << setw(8) << instruction << setw(24) << operands << comment << endl;
}

void Compiler::emitPrologue(string progName, string operand2)
{
  // Output identifying comments at beginning of objectFile
  //   Output the %INCLUDE directives
  //   emit("SECTION", ".text")
  //   emit("global", "_start", "", "; program" + progName)
  //   emit("_start:")

  time_t now = time(0);
  objectFile << "; Kangmin Kim, Jeff Caldwell       " << setw(8) << right << ctime(&now);
  objectFile << "%INCLUDE \"Along32.inc\"\n"
    << "%INCLUDE \"Macros_Along.inc\"\n\n";

  emit("SECTION", ".text");
  emit("global", "_start", "", "; program " + progName + "\n");
  emit("_start:");
}

void Compiler::emitEpilogue(string operand1, string operand2)
{
  emit("", "Exit", "{0}\n");
  emitStorage();
}

void Compiler::emitStorage()
{
  map<string, SymbolTableEntry>::iterator i;
  // emit("SECTION", ".data")
  //   for those entries in the symbolTable that have
  //     an allocation of YES and a storage mode of CONSTANT
  //   {call emit to output a line to objectFile}
  //     emit("SECTION", ".bss")
  //     for those entries in the symbolTable that have
  //       an allocation of YES and a storage mode of VARIABLE
  //     {call emit to output a line to objectFile}

  emit("SECTION", ".data");

  for (i = symbolTable.begin(); i != symbolTable.end(); i++)
  {
    if (i->second.getAlloc() == YES && i->second.getMode() == CONSTANT)
    {
      emit(i->second.getInternalName(), "dd", i->second.getValue(), "; " + i->first);
    }
  }

  objectFile << endl;
  emit("SECTION", ".bss");

  for (i = symbolTable.begin(); i != symbolTable.end(); i++)
  {
    if (i->second.getAlloc() == YES && i->second.getMode() == VARIABLE)
    {
      emit(i->second.getInternalName(), "resd", i->second.getValue(), "; " + i->first);
    }
  }
}

void Compiler::emitReadCode(string operand, string operand2)
{
  string name;
  for (uint i = 0; i < operand.size(); ++i)
  {

    if (operand[ i ] != ',' && i < operand.size())
    {
      name += operand[ i ];
      continue;
    }

    if (name != "")
    {
      if (symbolTable.count(name) == 0)
      {
        processError("reference to undefined symbol " + name);
      }
      if (symbolTable.at(name).getDataType() != INTEGER)
      {
        processError("can't read variables of this type");
      }
      if (symbolTable.at(name).getMode() != VARIABLE)
      {
        processError("attempting to read to a read-only location");
      }
      emit("", "call", "ReadInt", "; read int; value placed in eax");
      emit("", "mov", "[" + symbolTable.at(name).getInternalName() + "],eax", "; store eax at " + name);
      contentsOfAReg = symbolTable.at(name).getInternalName();
    }
    name = "";
  }

  if (name != "")
  {
    if (symbolTable.count(name) == 0)
    {
      processError("reference to undefined symbol " + name);
    }
    if (symbolTable.at(name).getDataType() != INTEGER)
    {
      processError("can't read variables of this type");
    }
    if (symbolTable.at(name).getMode() != VARIABLE)
    {
      processError("attempting to read to a read-only location");
    }
    emit("", "call", "ReadInt", "; read int; value placed in eax");
    emit("", "mov", "[" + symbolTable.at(name).getInternalName() + "],eax", "; store eax at " + name);
    contentsOfAReg = symbolTable.at(name).getInternalName();
  }
}

void Compiler::emitWriteCode(string operand, string operand2)
{
  string name;

  for (uint i = 0; i < operand.size(); ++i)
  {

    if (operand[ i ] != ',' && i < operand.size()) // get operand string and assign it to name
    {
      name += operand[ i ];
      continue;
    }
    if (name.length() > 15)
    {
      name = name.substr(0, 15);
    }

    if (name != "") // if name is not empty
    {
      if (symbolTable.count(name) == 0) // if name is not defined in symbolTable
      {
        processError("reference to undefined symbol " + name); // processError
      }
      if (symbolTable.at(name).getInternalName() != contentsOfAReg) // if name != AReg;
      {
        emit("", "mov", "eax,[" + symbolTable.at(name).getInternalName() + "]", "; load " + name + " in eax"); // emit "mov eax, [name]; load name in eax"
        contentsOfAReg = symbolTable.at(name).getInternalName(); // AReg = name
      }
      emit("", "call", "WriteInt", "; write int in eax to standard out"); // emit "call WriteInt; write int in eax to standard out"

      emit("", "call", "Crlf", "; write \\r\\n to standard out"); // emit "call Crlf; write \r\n to standard out"
    }
    name = ""; // deassign name
  }

  if (symbolTable.count(name) == 0) // if name is not defined in symbolTable
  {
    processError("reference to undefined symbol " + name);
  }
  if (symbolTable.at(name).getInternalName() != contentsOfAReg) // if name != AReg
  {
    emit("", "mov", "eax,[" + symbolTable.at(name).getInternalName() + "]", "; load " + name + " in eax"); // emit "mov eax,[name]; load name in eax"
    contentsOfAReg = symbolTable.at(name).getInternalName(); // AReg = name
  }
  emit("", "call", "WriteInt", "; write int in eax to standard out"); // emit "call WriteInt; write int in eax to standard out"

  emit("", "call", "Crlf", "; write \\r\\n to standard out"); // emit "call Crlf; write \r\n to standard out"
}

void Compiler::emitAssignCode(string operand1, string operand2) // operand2 = operand1
{
  if (symbolTable.count(operand1) == 0) // if operand1 is not defined in symbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }

  else if (symbolTable.count(operand2) == 0) // if operand2 is not defined in symbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }

  if (symbolTable.at(operand1).getDataType() != symbolTable.at(operand2).getDataType()) // if both operands datatype is not same
  {
    processError("incompatible types for operator ':='");
  }

  if (symbolTable.at(operand2).getMode() != VARIABLE) // if operand's mode is not variable
  {
    processError("symbol on left-hand side of assignment must have a storage mode of VARIABLE");
  }

  if (operand1 == operand2) // if both operands are same
  {
    return; // do nothing
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName()) // if AReg != operand1
  {
    emit("", "mov", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", "; AReg = " + operand1); // emit "mov eax,[operand1]; AReg = operand1"
  }

  emit("", "mov", "[" + symbolTable.at(operand2).getInternalName() + "],eax", "; " + operand2 + " = AReg"); // emit "mov [operand2],eax; operand2 = AReg"

  contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2

  if (isTemporary(operand1)) // if operand1 == "Tx"
  {
    freeTemp(); // currentTempNo--;
  }
}

void Compiler::emitAdditionCode(string operand1, string operand2) // operand2 + operand1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in symbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in symbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }
  if (whichType(operand1) != INTEGER || whichType(operand2) != INTEGER) // if operand1 or operand2 are not INTEGERs
  {
    processError("binary '+' requires integer operands");
  }
  if (contentsOfAReg[ 0 ] == 'T' && contentsOfAReg != symbolTable.at(operand1).getInternalName() &&
      contentsOfAReg != symbolTable.at(operand2).getInternalName()) // if AReg == 'Tx' and AReg != operand1 and AReg != operand2
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // setAllocation of AReg
    contentsOfAReg = ""; // deassign AReg
  }

  if (!contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T' &&  // if AReg is empty and AReg != 'Tx' and AReg != operand1 and AReg != operand2
      contentsOfAReg != symbolTable.at(operand1).getInternalName() &&
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    contentsOfAReg = "";  // deassign AReg 
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 && AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2); // emit "mov eax,[operand2]; AReg = operand2"
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg is operand2
  {
    emit("", "add", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", // emit "add eax,[operand1]; AReg = operand2 + operand1"
         "; AReg = " + operand2 + " + " + operand1);
  }
  else
  {
    emit("", "add", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", // emit "add eax,[operand2]; AReg = operand1 + operand2"
         "; AReg = " + operand1 + " + " + operand2);
  }

  if (isTemporary(operand1)) // if operand1 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // if operand2 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx" 
  symbolTable.at(contentsOfAReg).setDataType(INTEGER); // set type of AReg to INTEGER
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitSubtractionCode(string operand1, string operand2) // operand2 - operand1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in symbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in symbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }
  if (whichType(operand1) != INTEGER || whichType(operand2) != INTEGER) // if both types are not INTEGERs
  {
    processError("binary '-' requires integer operands");
  }

  if (contentsOfAReg[ 0 ] == 'T' && contentsOfAReg != symbolTable.at(operand2).getInternalName())
  { // if AReg == 'Tx' and AReg != operand2
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax ;deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // allocate AReg at symbolTable
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg[ 0 ] != 'T' && !contentsOfAReg.empty() && // if AReg is not "Tx" and AReg is not empty and AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand2).getInternalName()) // if AReg != operand2
  {
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    //emit "mov, eax[operand2]; AReg = operand2"
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2;
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == operand2
  {
    // emit "sub eax,[operand1]; AReg = operand2 - operand1"
    emit("", "sub", "eax,[" + symbolTable.at(operand1).getInternalName() + "]",
         "; AReg = " + operand2 + " - " + operand1);
  }
  if (isTemporary(operand1)) // if operand1 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // if operand2 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(INTEGER); // set AReg to INTEGER
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitMultiplicationCode(string operand1, string operand2) // op2 * op1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }

  if (whichType(operand1) != INTEGER || whichType(operand2) != INTEGER) // if both operand are not INTEGERs
  {
    processError("binary '*' requires integer operands");
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2 and AReg == "Tx"
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && contentsOfAReg[ 0 ] == 'T')
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg], eax; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // generate "Tx" at symbolTable
    contentsOfAReg = ""; // deassign ARegg
  }

  if (!contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T' && // if AReg is not empty and AReg != "Tx" and AReg != operand1 and AReg != operand2
      contentsOfAReg != symbolTable.at(operand1).getInternalName() &&
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    //emit "mov eax,[operand2]; AReg operand2"
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == operand2
  {
    emit("", "imul", "dword [" + symbolTable.at(operand1).getInternalName() + "]", // emit imul dword [operand1]; AReg = operand2 * operand1
         "; AReg = " + operand2 + " * " + operand1);
  }
  else
  {
    emit("", "imul", "dword [" + symbolTable.at(operand2).getInternalName() + "]", // emit imul dword [operand2]; AReg = operand1 * operand2
         "; AReg = " + operand1 + " * " + operand2);
  }

  if (isTemporary(operand1)) // if operand1 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // if operand2 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(INTEGER); // set AReg to INTEGER
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitDivisionCode(string operand1, string operand2) // op2 / op1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }
  if (whichType(operand1) != INTEGER || whichType(operand2) != INTEGER) // if both operands are not INTEGERs
  {
    processError("binary 'div' requires integer operands");
  }
  if (contentsOfAReg != "" && contentsOfAReg[ 0 ] == 'T' && contentsOfAReg != symbolTable.at(operand2).getInternalName())
  { // if AReg is not empty and AReg is "Tx" and AReg != operand2 
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [Areg],eax; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // generate AReg at symbolTable
    contentsOfAReg = ""; // deassign AReg
  }

  if (!contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T' && // if AReg is not empty and AReg != "Tx" and AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    contentsOfAReg = ""; // deassign AReg 
  }
  if (contentsOfAReg != symbolTable.at(operand2).getInternalName()) // if AReg is not operand2
  {
    // emit "mov eax,[operand2]; AReg = operand2"
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2
  }
  emit("", "cdq", "", "; sign extend dividend from eax to edx:eax"); // emit "cdq; sign extended from eax to edx:eax"
  emit("", "idiv", "dword [" + symbolTable.at(operand1).getInternalName() + "]",
       "; AReg = " + operand2 + " div " + operand1); // emit "idiv dword [operand1]; AReg = operand2 div operand1"

  if (isTemporary(operand1)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(INTEGER); // set AReg to INTEGER
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitModuloCode(string operand1, string operand2)
{ // op2 %  op1 
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }
  if (whichType(operand1) != INTEGER || whichType(operand2) != INTEGER) // if both operand are not INTEGERs
  {
    processError("binary 'mod' requires integer operands");
  }

  if (contentsOfAReg[ 0 ] == 'T' && contentsOfAReg != symbolTable.at(operand2).getInternalName())
  { // if AReg == "Tx" and AReg != operand2
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax ; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // generate AReg at symbolTable
    contentsOfAReg = ""; // deassign AReg
  }

  if (!contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T' && // if AReg is empty and AReg != "Tx" and AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand2).getInternalName()) // if AReg != operand2
  {
    // emit "mov eax,[operand2]; AReg = operand2"
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2
  }

  emit("", "cdq", "", "; sign extend dividend from eax to edx:eax"); // emit "cdq; sign extended dividened from eax to edx:eax"
  emit("", "idiv", "dword [" + symbolTable.at(operand1).getInternalName() + "]", // emit "idiv dword [operand1]; AReg = op2 div op1"
       "; AReg = " + operand2 + " div " + operand1);
  emit("", "xchg", "eax,edx", "; exchange quotient and remainder"); // emit "xchg eax,edx; exchange quotient and remainder"

  if (isTemporary(operand1)) // if operand1 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2))// if operand2 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(INTEGER); // set AReg to INTEGER
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitNegationCode(string operand1, string operand2)
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in symbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }

  if (whichType(operand1) != INTEGER) // if type of operand1 is not INTEGER
  {
    processError("unary '-' requires an integer operand");
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && contentsOfAReg[ 0 ] == 'T')
  { // if AReg != operand1 and AReg == "Tx"
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax ; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // set Allocation AReg
    contentsOfAReg = ""; // deassign AReg
  }

  if (!contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T' && // if AReg is empty and AReg == "Tx" and AReg != operand1
      contentsOfAReg != symbolTable.at(operand1).getInternalName())
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName()) // if AReg != operand1
  {
    // emit "mov eax,[operand1]; AReg = operand1"
    emit("", "mov", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", "; AReg = " + operand1);
    contentsOfAReg = symbolTable.at(operand1).getInternalName(); // AReg = operand1
  }

  emit("", "neg", "eax", "; AReg = -AReg"); // emit "neg eax; AReg = AReg"
  if (isTemporary(operand1)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(INTEGER); // set AReg to INTEGER
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitNotCode(string operand1, string operand2)
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in symbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  if (whichType(operand1) != BOOLEAN) // if type of operand1 is not BOOLEAN
  {
    processError("unary 'not' requires a boolean operand");
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && contentsOfAReg[ 0 ] == 'T')
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax ; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // generate "Tx" in symbolTable
    contentsOfAReg = ""; // deassign AReg
  }

  if (!contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T' && // if Areg is not empty and AReg != "Tx" ad AReg != operand1
      contentsOfAReg != symbolTable.at(operand1).getInternalName())
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName()) // if AReg != operand1
  {
    // emit "mov eax,[operand1]; Areg operand1"
    emit("", "mov", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", "; AReg = " + operand1);
    contentsOfAReg = symbolTable.at(operand1).getInternalName();
  }

  emit("", "not", "eax", "; AReg = !AReg"); // emit "not eax; AReg = !AReg"

  if (isTemporary(operand1)) // if operand1 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // Areg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(BOOLEAN); // set type of AReg to BOOLEAN
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitAndCode(string operand1, string operand2) // op2 && op1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }

  if (whichType(operand1) != BOOLEAN || whichType(operand2) != BOOLEAN) // if one of both opernads is not BOOLEAN
  {
    processError("binary 'and' requires boolean operands");
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2 and AReg == "Tx"
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && contentsOfAReg[ 0 ] == 'T')
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // generate Areg at symbolTable
    contentsOfAReg = ""; // deassign AReg
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2 and AReg is not empty 
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && !contentsOfAReg.empty() &&
      contentsOfAReg[ 0 ] != 'T') // and AReg is not "Tx"
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  { // emit "mov eax,[operand2] ; AReg = operand2"
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2 
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg = operand2
  {
    emit("", "and", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", // emit "and eax,[operand1]; AReg = operand2 and operand1"
         "; AReg = " + operand2 + " and " + operand1);
  }
  else
  {
    emit("", "and", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", // emit "and eax,[operand2]; AReg = operand1 and operand2"
         "; AReg = " + operand1 + " and " + operand2);
  }
  if (isTemporary(operand1)) // if operand1 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // if operand2 == "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(BOOLEAN); // set AReg to BOOLEAN
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitOrCode(string operand1, string operand2) // op2 || op1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }

  if (whichType(operand1) != BOOLEAN || whichType(operand2) != BOOLEAN)  // if one of both opernads is not BOOLEAN
  {
    processError("binary 'or' requires boolean operands");
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2 and AReg == "Tx"
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && contentsOfAReg[ 0 ] == 'T')
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // generate AReg at symbolTable
    contentsOfAReg = ""; // deassign AReg
  }

  if (!contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T' && // if AReg != operand1 and AReg != operand2 and AReg is not empty and AReg = "Tx"
      contentsOfAReg != symbolTable.at(operand1).getInternalName() &&
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2); // emit "mov eax,[operand2]; AReg = operand2"
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == operand2
  {
    emit("", "or", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", // emit "or eax,[operand1]; AReg = operand2 or operand1"
         "; AReg = " + operand2 + " or " + operand1);
  }
  else
  {
    emit("", "or", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", // emit "or eax,[operand2]; AReg = operand1 or operand2"
         "; AReg = " + operand1 + " or " + operand2);
  }

  if (isTemporary(operand1)) // if operand1 == "Tx"
  {
    freeTemp(); //currentTempNo--
  }
  if (isTemporary(operand2)) // if operand2 == "Tx"
  {
    freeTemp(); //currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(BOOLEAN); // set AReg to BOOLEAN
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitEqualityCode(string operand1, string operand2) // op2 == op1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }
  if (whichType(operand1) != whichType(operand2))  // if one of both opernads is not BOOLEAN
  {
    processError("incompatible types for operator '='");
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2 and AReg = "Tx"
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && contentsOfAReg[ 0 ] == 'T')
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // generate AReg at symbolTable
    contentsOfAReg = ""; // deaassign AReg
  }

  if (!contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T' && // if AReg is empty and AReg != "Tx" and AReg != op1 and AReg != op2
      contentsOfAReg != symbolTable.at(operand1).getInternalName() &&
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    // emit "mov eax,[operand2]; AReg = operand2"
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == operand2
  {
    emit("", "cmp", "eax,[" + symbolTable.at(operand1).getInternalName() + "]",
         "; compare " + operand2 + " and " + operand1); // emit "cmp eax,[op1]; compare op2 and op1"
  }
  else
  {
    emit("", "cmp", "eax,[" + symbolTable.at(operand2).getInternalName() + "]",
         "; compare " + operand1 + " and " + operand2); // emit "cmp eax,[op2]; compare op1 and op2"
  }
  string firstLab = getLabel(), secLab = getLabel();
  // firstLab = L0
  // SecLab   = L1

  emit("", "je", "." + firstLab, "; if " + operand2 + " = " + operand1 + " then jump to set eax to TRUE");
  emit("", "mov", "eax,[FALSE]", "; else set eax to FALSE");

  if (symbolTable.count("false") == 0) // if false is not defined
  {
    insert("false", BOOLEAN, CONSTANT, "0", YES, 1); // insert false at .data SECTION
    symbolTable.at("false").setInternalName("FALSE"); // then change false to FALSE
  }
  emit("", "jmp", "." + secLab, "; unconditionally jump"); // emit "jmp. L1 unconditionally jump"
  emit("." + firstLab + ":"); // emit " .L0: "
  emit("", "mov", "eax,[TRUE]", "; set eax to TRUE"); // emit "mov eax,[TRUE]; set eax to TRUE"

  if (symbolTable.count("true") == 0) // if true is not defined
  {
    insert("true", BOOLEAN, CONSTANT, "-1", YES, 1);  // insert true at .data SECTION
    symbolTable.at("true").setInternalName("TRUE"); // then change true to TRUE
  }
  emit("." + secLab + ":"); // emit ". L1: "

  if (isTemporary(operand1)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(BOOLEAN); // set datatype of AReg to BOOLEAN
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitInequalityCode(string operand1, string operand2) // op2 != op1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }
  if (whichType(operand1) != whichType(operand2)) // if both types are not matched
  {
    processError("incompatible types for operator '<>'");
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != op1 and AReg != op2 and Areg = "Tx"
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && contentsOfAReg[ 0 ] == 'T')
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax ; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // generate AReg at symbolTable
    contentsOfAReg = ""; // deassign AReg 
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != op1 and AReg != op2 and AReg is not empty
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && !contentsOfAReg.empty() &&
      contentsOfAReg[ 0 ] != 'T') // and AReg != "Tx"
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != op1 and AReg != op2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  { // emit "mov eax,[operand2]; AReg = operand2"
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == op2
  {
    emit("", "cmp", "eax,[" + symbolTable.at(operand1).getInternalName() + "]",
         "; compare " + operand2 + " and " + operand1); // emit "cmp eax,[operand1]; compare op1 and op2"
  }
  else
  {
    emit("", "cmp", "eax,[" + symbolTable.at(operand2).getInternalName() + "]",
         "; compare " + operand1 + " and " + operand2); // emit "cmp eax,[operand2]; compare op2 and op1"
  }

  string firstLab = getLabel(), secLab = getLabel();
  // firstLab = L0
  // SecLab   = L1
  emit("", "jne", "." + firstLab, "; if " + operand2 + " <> " + operand1 + " then jump to set eax to TRUE");
  emit("", "mov", "eax,[FALSE]", "; else set eax to FALSE"); // emit "mov eax,[FALSE]; else set eax to FALSE"

  if (symbolTable.count("false") == 0) // if false is not defined
  {
    insert("false", BOOLEAN, CONSTANT, "0", YES, 1); // insert false at .data SECTION
    symbolTable.at("false").setInternalName("FALSE"); // then change false to FALSE
  }
  emit("", "jmp", "." + secLab, "; unconditionally jump"); // emit "jmp. L1 unconditionally jump"
  emit("." + firstLab + ":"); // emit " .L0: "
  emit("", "mov", "eax,[TRUE]", "; set eax to TRUE"); // emit "mov eax,[TRUE]; set eax to TRUE"

  if (symbolTable.count("true") == 0) // if true is not defined
  {
    insert("true", BOOLEAN, CONSTANT, "-1", YES, 1); // insert true at .data SECTION
    symbolTable.at("true").setInternalName("TRUE"); // then change true to TRUE
  }
  emit("." + secLab + ":"); // emit ".L1: "

  if (isTemporary(operand1)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(BOOLEAN); // set datatype of AReg to BOOLEAN
  pushOperand(contentsOfAReg); // push AReg to Operand
}

// operand2 less than operand1
void Compiler::emitLessThanCode(string operand1, string operand2)
{
  if (symbolTable.at(operand1).getDataType() != symbolTable.at(operand2).getDataType())
    processError("binary '<' requires integer operands");

  if (isTemporary(contentsOfAReg) && contentsOfAReg != symbolTable.at(operand1).getInternalName() && contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg");

    symbolTable.at(contentsOfAReg).setAlloc(YES);

    contentsOfAReg = "";
  }

  if (!isTemporary(contentsOfAReg) && contentsOfAReg != symbolTable.at(operand1).getInternalName())
  {
    if (contentsOfAReg != symbolTable.at(operand2).getInternalName())
    {
      contentsOfAReg = "";
    }
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName())
  {
    if (contentsOfAReg != symbolTable.at(operand2).getInternalName())
    {
      emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);

      contentsOfAReg = symbolTable.at(operand2).getInternalName();
    }
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName())
  {
    emit("", "cmp", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", "; compare " + operand2 + " and " + operand1);
  }
  else if (contentsOfAReg == symbolTable.at(operand1).getInternalName())
  {
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);

    emit("", "cmp", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", "; compare " + operand2 + " and " + operand1);
  }

  string firstlabel = getLabel();

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName())
  {
    emit("", "jl", "." + firstlabel, "; if " + operand2 + " < " + operand1 + " then jump to set eax to TRUE");
  }
  else if (contentsOfAReg == symbolTable.at(operand1).getInternalName())
  {
    emit("", "jl", "." + firstlabel, "; if " + operand2 + " < " + operand1 + " then jump to set eax to TRUE");
  }

  emit("", "mov", "eax,[FALSE]", "; else set eax to FALSE");

  if (symbolTable.count("false") == 0)
  {
    insert("FALSE", BOOLEAN, CONSTANT, "0", YES, 1);
  }

  string secondLabel = getLabel();

  emit("", "jmp", "." + secondLabel, "; unconditionally jump");

  emit("." + firstlabel + ":");

  emit("", "mov", "eax,[TRUE]", "; set eax to TRUE");

  if (symbolTable.count("true") == 0)
  {
    insert("TRUE", BOOLEAN, CONSTANT, "-1", YES, 1);
  }

  emit("." + secondLabel + ":");

  if (isTemporary(operand1))
  {
    freeTemp();
  }
  if (isTemporary(operand2))
  {
    freeTemp();
  }

  contentsOfAReg = getTemp();

  symbolTable.at(contentsOfAReg).setDataType(BOOLEAN);

  pushOperand(contentsOfAReg);
}

void Compiler::emitLessThanOrEqualToCode(string operand1, string operand2) // op2 <= op1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }
  if (whichType(operand1) != whichType(operand2)) // if both types are not matched
  {
    processError("incompatible types for operator '<='");
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != op1 and AReg != op2 and AReg == "Tx"
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && contentsOfAReg[ 0 ] == 'T')
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [Areg],eax ; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // insert AReg to symbolTable
    contentsOfAReg = ""; // deassign AReg
  }

  if (!contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T' && // if AReg is empty and AReg != "Tx" and AReg != op1 and AReg != op2
      contentsOfAReg != symbolTable.at(operand1).getInternalName() &&
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != op1 and AReg != op2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    // emit "mov eax,[operand2]; AReg = operand2"
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == operand2
  {
    // emit "cmp eax,[operand1]; compare op2 and op1"
    emit("", "cmp", "eax,[" + symbolTable.at(operand1).getInternalName() + "]",
         "; compare " + operand2 + " and " + operand1);
  }
  else
  {
    // emit "cmp eax,[operand2]; compare op1 and op2"
    emit("", "cmp", "eax,[" + symbolTable.at(operand2).getInternalName() + "]",
         "; compare " + operand1 + " and " + operand2);
  }
  string firstLab = getLabel(), secLab = getLabel();
  // firstLab = L0
  // SecLab   = L1
  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == operand2
  {
    // emit "jle. L0; if op2 <= op1 then jump to set eax to TRUE"
    emit("", "jle", "." + firstLab, "; if " + operand2 + " <= " + operand1 + " then jump to set eax to TRUE");
  }
  else
  {
    // emit "jle. L0; if op1 <= op2 then jump to set eax to TRUE"
    emit("", "jle", "." + firstLab, "; if " + operand1 + " <= " + operand2 + " then jump to set eax to TRUE");
  }
  // emit "mov eax,[FALSE]; else set eax to FALSE"
  emit("", "mov", "eax,[FALSE]", "; else set eax to FALSE");

  if (symbolTable.count("false") == 0) // if false is not defined at data section
  {
    insert("false", BOOLEAN, CONSTANT, "0", YES, 1);  // insert false at .data SECTION
    symbolTable.at("false").setInternalName("FALSE"); // then change false to FALSE
  }
  emit("", "jmp", "." + secLab, "; unconditionally jump"); // emit "jmp. L1; unconditionally jump"
  emit("." + firstLab + ":"); // emit ".L0: "
  emit("", "mov", "eax,[TRUE]", "; set eax to TRUE"); // emit "mov eax,[TRUE]; set eax to TRUE"

  if (symbolTable.count("true") == 0) // if true is not defined at data section
  {
    insert("true", BOOLEAN, CONSTANT, "-1", YES, 1); // insert true at .data SECTION
    symbolTable.at("true").setInternalName("TRUE"); // then change true to TRUE
  }
  emit("." + secLab + ":"); // emit ".L1: "

  if (isTemporary(operand1)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // // if operand2 = "Tx"
  {
    freeTemp(); // currentTempNo-- 
  }

  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(BOOLEAN); // set datatype of AReg to BOOLEAN
  pushOperand(contentsOfAReg); // push AReg to Operand
}
void Compiler::emitGreaterThanCode(string operand1, string operand2) // op2 > op1
{

  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }
  if (whichType(operand1) != whichType(operand2)) // if both types don't match
  {
    processError("incompatible types for operator '>'");
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() // if AReg != operand1 and AReg != operand2
    && contentsOfAReg != symbolTable.at(operand2).getInternalName()
      && contentsOfAReg[ 0 ] == 'T') // and AReg = "Tx"
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg"); // emit "mov [AReg],eax ; deassign AReg"
    symbolTable.at(contentsOfAReg).setAlloc(YES); // set allocation AReg at symbolTable
    contentsOfAReg = ""; // deassign AReg
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() // if AReg != operand1 and AReg != operand2
    && contentsOfAReg != symbolTable.at(operand2).getInternalName()
      && !contentsOfAReg.empty() && contentsOfAReg[ 0 ] != 'T')
  {
    contentsOfAReg = ""; // deassign AReg
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() // if AReg != operand1 and AReg != operand2
    && contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    // emit "mov eax,[operand2]; AReg = operand2"
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    contentsOfAReg = symbolTable.at(operand2).getInternalName(); // AReg = operand2
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName())
  {
    // emit "cmp eax,[operand1]; compare op2 and op1"
    emit("", "cmp", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", "; compare " + operand2 + " and " + operand1);
  }
  else
  {
    // emit "cmp eax,[operand2]; comapre op1 and op2"
    emit("", "cmp", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; compare " + operand1 + " and " + operand2);
  }
  string firstLab = getLabel(), secLab = getLabel();
  // firstLab = L0
  // SecLab   = L1
  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == operand2
  {
    //emit "jg.L0; if op2 > op1 then jump to set eax to TRUE"
    emit("", "jg", "." + firstLab, "; if " + operand2 + " > " + operand1 + " then jump to set eax to TRUE");
  }
  else
  {
    //emit "jg.L0; if op1 > op2 then jump to set eax to TRUE"
    emit("", "jg", "." + firstLab, "; if " + operand1 + " > " + operand2 + " then jump to set eax to TRUE");
  }
  // emit "mov eax,[FALSE]; else set eax to FALSE"
  emit("", "mov", "eax,[FALSE]", "; else set eax to FALSE");

  if (symbolTable.count("false") == 0) // if false is not defined at data section
  {
    insert("false", BOOLEAN, CONSTANT, "0", YES, 1);  // insert false at .data SECTION
    symbolTable.at("false").setInternalName("FALSE"); // then change false to FALSE
  }
  emit("", "jmp", "." + secLab, "; unconditionally jump"); // emit "jmp. L1; unconditionally jump"
  emit("." + firstLab + ":"); // emit ".L0: "
  emit("", "mov", "eax,[TRUE]", "; set eax to TRUE"); // emit "mov eax,[TRUE]; set eax to TRUE"

  if (symbolTable.count("true") == 0) // if true is not defined at data section
  {
    insert("true", BOOLEAN, CONSTANT, "-1", YES, 1); // insert true at .data SECTION
    symbolTable.at("true").setInternalName("TRUE"); // then change true to TRUE
  }
  emit("." + secLab + ":"); // emit ".L1: "

  if (isTemporary(operand1)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // // if operand2 = "Tx"
  {
    freeTemp(); // currentTempNo-- 
  }

  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(BOOLEAN); // set datatype of AReg to BOOLEAN
  pushOperand(contentsOfAReg); // push AReg to Operand
}

void Compiler::emitGreaterThanOrEqualToCode(string operand1, string operand2) // op2 >= op1
{
  if (symbolTable.find(operand1) == symbolTable.end()) // if operand1 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand1);
  }
  else if (symbolTable.find(operand2) == symbolTable.end()) // if operand2 is not defined in SymbolTable
  {
    processError("reference to undefined symbol " + operand2);
  }
  if (whichType(operand1) != whichType(operand2)) // if both types are not matched
  {
    processError("incompatible types for operator '>='");
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && contentsOfAReg[ 0 ] == 'T') // and AReg = "Tx"
  {
    emit("", "mov", "[" + contentsOfAReg + "],eax", "; deassign AReg");
    symbolTable.at(contentsOfAReg).setAlloc(YES);
    contentsOfAReg = ""; // deassign AReg 
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2 and AReg is not empty
      contentsOfAReg != symbolTable.at(operand2).getInternalName() && !contentsOfAReg.empty() &&
      contentsOfAReg[ 0 ] != 'T')
  {
    contentsOfAReg = ""; // deassign AReg 
  }
  if (contentsOfAReg != symbolTable.at(operand1).getInternalName() && // if AReg != operand1 and AReg != operand2
      contentsOfAReg != symbolTable.at(operand2).getInternalName())
  {
    //emit "mov eax,[operand2]; AReg = operand2"
    emit("", "mov", "eax,[" + symbolTable.at(operand2).getInternalName() + "]", "; AReg = " + operand2);
    contentsOfAReg = symbolTable.at(operand2).getInternalName();
  }

  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == operand2
  {
    // emit "cmp eax,[operand1]; compare operand2 and oeprand1 "
    emit("", "cmp", "eax,[" + symbolTable.at(operand1).getInternalName() + "]",
         "; compare " + operand2 + " and " + operand1);
  }
  else
  {
    // emit "cmp eax,[operand2]; compare operand1 and oeprand2 "
    emit("", "cmp", "eax,[" + symbolTable.at(operand2).getInternalName() + "]",
         "; compare " + operand1 + " and " + operand2);
  }
  string firstLab = getLabel(), secLab = getLabel();
  // firstLab = L0
  // SecLab   = L1
  if (contentsOfAReg == symbolTable.at(operand2).getInternalName()) // if AReg == op2
  {
    // emit "jge .L0; if op2 >= op1 then jump to set eax to TRUE"
    emit("", "jge", "." + firstLab, "; if " + operand2 + " >= " + operand1 + " then jump to set eax to TRUE");
  }
  else
  {
    // emit "jge .L0; if op1 >= op2 then jump to set eax to TRUE"
    emit("", "jge", "." + firstLab, "; if " + operand1 + " >= " + operand2 + " then jump to set eax to TRUE");
  }
  // emit "mov eax,[FALSE]; else set eax to FALSE"
  emit("", "mov", "eax,[FALSE]", "; else set eax to FALSE");

  if (symbolTable.count("false") == 0) // if false is not defined at data section
  {
    insert("false", BOOLEAN, CONSTANT, "0", YES, 1);  // insert false at .data SECTION
    symbolTable.at("false").setInternalName("FALSE"); // then change false to FALSE
  }
  emit("", "jmp", "." + secLab, "; unconditionally jump"); // emit "jmp. L1; unconditionally jump"
  emit("." + firstLab + ":"); // emit ".L0: "
  emit("", "mov", "eax,[TRUE]", "; set eax to TRUE"); // emit "mov eax,[TRUE]; set eax to TRUE"

  if (symbolTable.count("true") == 0) // if true is not defined at data section
  {
    insert("true", BOOLEAN, CONSTANT, "-1", YES, 1); // insert true at .data SECTION
    symbolTable.at("true").setInternalName("TRUE"); // then change true to TRUE
  }
  emit("." + secLab + ":"); // emit ".L1: "

  if (isTemporary(operand1)) // if operand1 = "Tx"
  {
    freeTemp(); // currentTempNo--
  }
  if (isTemporary(operand2)) // // if operand2 = "Tx"
  {
    freeTemp(); // currentTempNo-- 
  }

  contentsOfAReg = getTemp(); // AReg = "Tx"
  symbolTable.at(contentsOfAReg).setDataType(BOOLEAN); // set datatype of AReg to BOOLEAN
  pushOperand(contentsOfAReg); // push AReg to Operand
}

////emit code that follows 'then' and statement predicate
void Compiler::emitThenCode(string operand1, string operand2)
{
  string tempLabel;

  if (symbolTable.at(operand1).getDataType() != BOOLEAN)
  {
    processError("if predicate must be of type boolean");
  }

  tempLabel = getLabel();

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName())
  {
    emit("", "mov", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", "; AReg = " + operand1);
  }

  emit("", "cmp", "eax,0", "; compare eax to 0");

  emit("", "je", "." + tempLabel, "; if " + operand1 + " is false then jump to end of if");

  pushOperand(tempLabel);

  if (isTemporary(operand1))
  {
    freeTemp();
  }

  contentsOfAReg = ""; // deassign AReg
}

void Compiler::emitElseCode(string operand1, string operand2)
{
  string tempLabel;

  tempLabel = getLabel();

  emit("", "jmp", "." + tempLabel, "; jump to end if");

  emit("." + operand1 + ":", "", "", "; else");

  pushOperand(tempLabel);

  contentsOfAReg = "";

}

void Compiler::emitPostIfCode(string operand1, string)
{
  emit("." + operand1 + ":", "", "", "; end if");

  contentsOfAReg = "";
}

void Compiler::emitWhileCode(string operand1, string operand2)
{
  string tempLabel;

  tempLabel = getLabel();

  emit("." + tempLabel + ":", "", "", "; while");

  pushOperand(tempLabel);

  contentsOfAReg = "";

}

void Compiler::emitDoCode(string operand1, string operand2)
{
  string tempLabel;

  if (symbolTable.at(operand1).getDataType() != BOOLEAN)
  {
    processError("while predicate must be of type boolean");
  }

  tempLabel = getLabel();

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName())
  {
    emit("", "mov", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", "; AReg = " + operand1);
  }

  emit("", "cmp", "eax,0", "; compare eax to 0");

  emit("", "je", "." + tempLabel, "; if " + operand1 + " is false then jump to end while");

  pushOperand(tempLabel);

  if (isTemporary(operand1))
  {
    freeTemp();
  }

  contentsOfAReg = "";
}

void Compiler::emitPostWhileCode(string operand1, string operand2)
{
  emit("", "jmp", "." + operand2, "; end while");

  emit("." + operand1 + ":", "", "", "");

  contentsOfAReg = "";

}

void Compiler::emitRepeatCode(string operand1, string operand2)
{
  string tempLabel;

  tempLabel = getLabel();

  emit("." + tempLabel + ":", "", "", "; repeat");

  pushOperand(tempLabel);

  contentsOfAReg = "";
}

void Compiler::emitUntilCode(string operand1, string operand2)
{
  if (symbolTable.at(operand1).getDataType() != BOOLEAN)
  {
    processError("predicate of until must be of type boolean");
  }

  if (contentsOfAReg != symbolTable.at(operand1).getInternalName())
  {
    emit("", "mov", "eax,[" + symbolTable.at(operand1).getInternalName() + "]", "; AReg = " + symbolTable.at(operand1).getInternalName());
    contentsOfAReg = symbolTable.at(operand1).getInternalName(); // reassign
  }

  emit("", "cmp", "eax,0", "; compare eax to 0");

  emit("", "je", "." + operand2, "; until " + operand1 + " is true");

  if (isTemporary(operand1))
  {
    freeTemp();
  }

  contentsOfAReg = "";
}


/** LEXER FUNCTIONS **/
/*nextToken() catches LEXICAL ERRORS*/
string Compiler::nextToken() // returns the next token or end of file marker
{
  token = ""; // deassign token

  while (token == "")
  {
    if (ch == '{')
    {
      while (nextChar() && ch != END_OF_FILE && ch != '}')
      {
      }	// do nothing

      if (ch == END_OF_FILE)
      {
        processError("unexpected end of file");
      }
      else
      {
        nextChar();
      }
    }

    else if (ch == '}')
    {
      processError("'}' cannot begin token");
    }
    else if (isspace(ch))
    {
      nextChar();
    }
    else if (isSpecialSymbol(ch))
    {
      token = ch;
      nextChar();

      if (token == ":" && ch == '=')
      {
        token += ch;
        nextChar();
      }
      else if (token == "<" && (ch == '>' || ch == '='))
      {
        token += ch;
        nextChar();
      }
      else if (token == ">" && ch == '=')
      {
        token += ch;
        nextChar();
      }
    }

    else if (islower(ch))
    {
      token += ch;

      while ((nextChar() == '_' || (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z')) && ch != END_OF_FILE)
        token += ch;

      if (ch == END_OF_FILE)
      {
        processError("unexpected end of file");
      }
    }

    else if (isdigit(ch))
    {
      token = ch;

      while (isdigit(nextChar()) && ch != END_OF_FILE
        && !isSpecialSymbol(ch))
      {
        token += ch;
      }
      if (ch == END_OF_FILE)
      {
        processError("unexpected end of file");
      }
    }

    else if (ch == END_OF_FILE)
    {
      token = ch;
    }
    else
    {
      processError("illegal symbol");
    }
  }
  token = token.substr(0, 15);

  return token;
}

char Compiler::nextChar() // returns the next character or end of file marker
{
  // get the next character
  sourceFile.get(ch);

  // set prevChar at the beginning so we know when to start
  // a new line number. Needs to be static because this fn is
  // called from outside repeatedly.
  static char prevChar = '\n';

  if (!sourceFile) // works like if(sourcefile.eof())
  {                // see Dr Motl's lecture from 11/01
    ch = END_OF_FILE;
    return ch;
  }

  else
  {
    if (prevChar == '\n')
    {
      // we have a new line, increment the
      // line number and add it to the left
      // with a separator
      listingFile << setw(5) << ++lineNo << '|';
    }
    // add the current character
    listingFile << ch;
  }

  // now set the previous character (static!) to the
  // current character. When we reach a new line again,
  // it will be reset to '\n'
  prevChar = ch;

  // done
  return ch;
}



void Compiler::freeTemp()
{
  currentTempNo--;
  if (currentTempNo < -1)
  {
    processError("compiler error: currentTempNo should be greater than or equal to –1");
  }
}
string Compiler::getTemp()
{
  currentTempNo++;
  string temp;

  temp = "T" + to_string(currentTempNo);

  if (currentTempNo > maxTempNo)
  {
    insert(temp, UNKNOWN, VARIABLE, "1", NO, 1);
    symbolTable.at(temp).setInternalName(temp);
    maxTempNo++;
  }

  return temp;
}

string Compiler::getLabel()
{
  string internalName; // Label
  static int L = 0;

  internalName = "L" + to_string(L);

  L++;

  return internalName;
}

bool Compiler::isTemporary(string s) const
{
  if (s[ 0 ] == 'T')
    return true;
  else
    return false;
}

