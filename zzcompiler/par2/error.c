#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(ErrorCode err, int lineNo, int colNo) {

  if (lineNo < 10){
    printf("0%d-", lineNo);
  }else{
    printf("%d-", lineNo);
  }

  if (colNo < 10){
    printf("0%d : ", colNo);
  }else{
    printf("%d : ", colNo);
  } 

  switch (err) {
    case ERR_ENDOFCOMMENT:
      printf("%s\n", ERM_ENDOFCOMMENT);
      break;
    case ERR_IDENTTOOLONG:
      printf("%s\n", ERM_IDENTTOOLONG);
      break;
    case ERR_INVALIDCHARCONSTANT:
      printf("%s\n", ERM_INVALIDCHARCONSTANT);
      break;
    case ERR_INVALIDSYMBOL:
      printf("%s\n", ERM_INVALIDSYMBOL);
      break;
    case ERR_INVALIDCONSTANT:
      printf("%s\n", ERM_INVALIDCONSTANT);
      break;
    case ERR_INVALIDTYPE:
      printf("%s\n", ERM_INVALIDTYPE);
      break;
    case ERR_INVALIDBASICTYPE:
      printf("%s\n", ERM_INVALIDBASICTYPE);
      break;
    case ERR_INVALIDPARAM:
      printf("%s\n", ERM_INVALIDPARAM);
      break;
    case ERR_INVALIDSTATEMENT:
      printf("%s\n", ERM_INVALIDSTATEMENT);
      break;
    case ERR_INVALIDARGUMENTS:
      printf("%s\n", ERM_INVALIDARGUMENTS);
      break;
    case ERR_INVALIDCOMPARATOR:
      printf("%s\n", ERM_INVALIDCOMPARATOR);
      break;
    case ERR_INVALIDEXPRESSION:
      printf("%s\n", ERM_INVALIDEXPRESSION);
      break;
    case ERR_INVALIDTERM:
      printf("%s\n", ERM_INVALIDTERM);
      break;
    case ERR_INVALIDFACTOR:
      printf("%s\n", ERM_INVALIDFACTOR);
      break;
    case ERR_INVALIDCONSTDECL:
      printf("%s\n", ERM_INVALIDCONSTDECL);
      break;
    case ERR_INVALIDTYPEDECL:
      printf("%s\n", ERM_INVALIDTYPEDECL);
      break;
    case ERR_INVALIDVARDECL:
      printf("%s\n", ERM_INVALIDVARDECL);
      break;
    case ERR_INVALIDSUBDECL:
      printf("%s\n", ERM_INVALIDSUBDECL);
      break;


    case ERR_INVALIDCONDITION:
      printf("%s\n", ERM_INVALIDCONDITION);
      break;
    case ERR_INVALIDINDEX:
      printf("%s\n", ERM_INVALIDINDEX);
      break;
    case ERR_INVALIDSTRING:
      printf("%s\n", ERM_INVALIDSTRING);
      break;
    case ERR_INVALIDFLOAT:
      printf("%s\n", ERM_INVALIDFLOAT);
      break;




    case ERR_UNDECLARED_IDENT:
      printf("%s\n", ERM_UNDECLARED_IDENT);
      break;

    case ERR_UNDECLARED_CONSTANT:
      printf("%s\n", ERM_UNDECLARED_CONSTANT);
      break;

    case ERR_UNDECLARED_INT_CONSTANT:
      printf("%s\n", ERM_UNDECLARED_INT_CONSTANT);
      break;

    case ERR_UNDECLARED_DOUBLE_CONSTANT:
      printf("%s\n", ERM_UNDECLARED_DOUBLE_CONSTANT);
      break;

    case ERR_UNDECLARED_TYPE:
      printf("%s\n", ERM_UNDECLARED_TYPE);
      break;

    case ERR_UNDECLARED_VARIABLE:
      printf("%s\n", ERM_UNDECLARED_VARIABLE);
      break;

    case ERR_UNDECLARED_FUNCTION:
      printf("%s\n", ERM_UNDECLARED_FUNCTION);
      break;

    case ERR_UNDECLARED_PROCEDURE:
      printf("%s\n", ERM_UNDECLARED_PROCEDURE);
      break;

    case ERR_DUPLICATE_IDENT:
      printf("%s\n", ERM_DUPLICATE_IDENT);
      break;

    case ERR_TYPE_INCONSISTENCY:
      printf("%s\n", ERM_TYPE_INCONSISTENCY);
      break;

    case ERR_VARIABLE:
      printf("%s\n", ERM_VARIABLE);
      break;

    case ERR_MISS_RVALUE:
      printf("%s\n", ERM_MISS_RVALUE);
      break;

    case ERR_MISS_LVALUE:
      printf("%s\n", ERM_MISS_LVALUE);
      break;

    case ERR_INVALID_DOUBLE_VALUE:
      printf("%s\n", ERM_INVALID_DOUBLE_VALUE);
      break;

    case ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY:
      printf("%s\n", ERM_PARAMETERS_ARGUMENTS_INCONSISTENCY);
      break;

    case ERR_INVALID_VARIABLE:
      printf("%s\n", ERM_INVALID_VARIABLE);
      break;

    case ERR_INVALID_FUNCTION:
      printf("%s\n", ERM_INVALID_FUNCTION);
      break;

    case ERR_INVALID_PROCEDURE:
      printf("%s\n", ERM_INVALID_PROCEDURE);
      break;

    case ERR_INVALID_IDENT:
      printf("%s\n", ERM_INVALID_IDENT);
      break;

    case ERR_INVALID_LVALUE:
      printf("%s\n", ERM_INVALID_LVALUE);
      break;
    
  }
  exit(0);
}

void missingToken(TokenType tokenType, int lineNo, int colNo) {
  printf("%d-%d:Missing %s\n", lineNo, colNo, tokenToString(tokenType));
  exit(0);
}

void assert(char *msg) {
  printf("%s\n", msg);
}
