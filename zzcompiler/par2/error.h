#ifndef __ERROR_H__
#define __ERROR_H__
#include "token.h"

typedef enum {
  ERR_ENDOFCOMMENT,
  ERR_IDENTTOOLONG,
  ERR_INVALIDCHARCONSTANT,
  ERR_INVALIDSYMBOL,
  ERR_INVALIDCONSTANT,
  ERR_INVALIDTYPE,
  ERR_INVALIDBASICTYPE,
  ERR_INVALIDPARAM,
  ERR_INVALIDSTATEMENT,
  ERR_INVALIDARGUMENTS,
  ERR_INVALIDCOMPARATOR,
  ERR_INVALIDEXPRESSION,
  ERR_INVALIDTERM,
  ERR_INVALIDFACTOR,
  ERR_INVALIDCONSTDECL,
  ERR_INVALIDTYPEDECL,
  ERR_INVALIDVARDECL,
  ERR_INVALIDSUBDECL,

  ERR_INVALIDCONDITION,
  ERR_INVALIDINDEX,
  ERR_INVALIDSTRING,
  ERR_INVALIDFLOAT,


  ERR_UNDECLARED_IDENT,
  ERR_UNDECLARED_CONSTANT,
  ERR_UNDECLARED_INT_CONSTANT,
  ERR_UNDECLARED_DOUBLE_CONSTANT,
  ERR_UNDECLARED_TYPE,
  ERR_UNDECLARED_VARIABLE,
  ERR_UNDECLARED_FUNCTION,
  ERR_UNDECLARED_PROCEDURE,
  ERR_DUPLICATE_IDENT,
  ERR_TYPE_INCONSISTENCY,
  ERR_VARIABLE,
  ERR_MISS_RVALUE,
  ERR_MISS_LVALUE,
  ERR_INVALID_DOUBLE_VALUE,
  ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY,


  ERR_INVALID_VARIABLE,
  ERR_INVALID_FUNCTION,
  ERR_INVALID_PROCEDURE,
  ERR_INVALID_IDENT,
  ERR_INVALID_LVALUE,


} ErrorCode;


// {ERR_END_OF_COMMENT, "End of comment expected."},
// 	{ERR_IDENT_TOO_LONG, "Identifier too long."},
// 	{ERR_INVALID_CONSTANT_CHAR, "Invalid char constant."},
// 	{ERR_INVALID_STRING,"Invalid string constant."},
// 	{ERR_INVALID_SYMBOL, "Invalid symbol."},
// 	{ERR_INVALID_IDENT, "An identifier expected."},
// 	{ERR_INVALID_CONSTANT, "A constant expected."},
// 	{ERR_INVALID_TYPE, "A type expected."},
// 	{ERR_INVALID_BASICTYPE, "A basic type expected."},
// 	{ERR_INVALID_VARIABLE, "A variable expected."},
// 	{ERR_INVALID_FUNCTION, "A function identifier expected."},
// 	{ERR_INVALID_PROCEDURE, "A procedure identifier expected."},
// 	{ERR_INVALID_PARAMETER, "A parameter expected."},
// 	{ERR_INVALID_STATEMENT, "Invalid statement."},
// 	{ERR_INVALID_COMPARATOR, "A comparator expected."},
// 	{ERR_INVALID_EXPRESSION, "Invalid expression."},
// 	{ERR_INVALID_TERM, "Invalid term."},
// 	{ERR_INVALID_FACTOR, "Invalid factor."},
// 	{ERR_INVALID_LVALUE, "Invalid lvalue in assignment."},
// 	{ERR_INVALID_ARGUMENTS, "Wrong arguments."},

#define ERM_INVALID_VARIABLE "A variable expected."
#define ERM_INVALID_FUNCTION "A function identifier expected."
#define ERM_INVALID_PROCEDURE "A procedure identifier expected."
#define ERM_INVALID_IDENT "An identifier expected."
#define ERM_INVALID_LVALUE "Invalid lvalue in assignment."

#define ERM_UNDECLARED_IDENT "Undeclared identifier."
#define ERM_UNDECLARED_CONSTANT "Undeclared constant."
#define ERM_UNDECLARED_INT_CONSTANT "Undeclared integer constant."
#define ERM_UNDECLARED_DOUBLE_CONSTANT "Undeclared double constant."
#define ERM_UNDECLARED_TYPE "Undeclared type."
#define ERM_UNDECLARED_VARIABLE "Undeclared variable."
#define ERM_UNDECLARED_FUNCTION "Undeclared function."
#define ERM_UNDECLARED_PROCEDURE "Undeclared procedure."
#define ERM_DUPLICATE_IDENT "Duplicate identifier."
#define ERM_TYPE_INCONSISTENCY "Type inconsistency"
#define ERM_VARIABLE "Left site can't have value"
#define ERM_MISS_RVALUE "Missing right value"
#define ERM_MISS_LVALUE "Missing left value"
#define ERM_INVALID_DOUBLE_VALUE "Invalid double value"
#define ERM_PARAMETERS_ARGUMENTS_INCONSISTENCY "The number of arguments and the number of parameters are inconsistent."

#define ERM_ENDOFCOMMENT "End of comment expected!"
#define ERM_IDENTTOOLONG "Identification too long!"
#define ERM_INVALIDCHARCONSTANT "Invalid const char!"
#define ERM_INVALIDSYMBOL "Invalid symbol!"
#define ERM_INVALIDCONSTANT "Invalid constant!"
#define ERM_INVALIDTYPE "Invalid type!"
#define ERM_INVALIDBASICTYPE "Invalid basic type!"
#define ERM_INVALIDPARAM "Invalid parameter!"
#define ERM_INVALIDSTATEMENT "Invalid statement!"
#define ERM_INVALIDARGUMENTS "Invalid arguments!"
#define ERM_INVALIDCOMPARATOR "Invalid comparator!"
#define ERM_INVALIDEXPRESSION "Invalid expression!"
#define ERM_INVALIDTERM "Invalid term!"
#define ERM_INVALIDFACTOR "Invalid factor!"
#define ERM_INVALIDCONSTDECL "Invalid constant declaration!"
#define ERM_INVALIDTYPEDECL "Invalid type declaration!"
#define ERM_INVALIDVARDECL "Invalid variable declaration!"
#define ERM_INVALIDSUBDECL "Invalid subroutine declaration!"

#define ERM_INVALIDCONDITION "Invalid condition!"
#define ERM_INVALIDINDEX "Invalid index!"
#define ERM_INVALIDSTRING "Invalid const string!\n[ string too long (100000) ]"
#define ERM_INVALIDFLOAT "Invalid float value!"

void error(ErrorCode err, int lineNo, int colNo);
void missingToken(TokenType tokenType, int lineNo, int colNo);
void assert(char *msg);

#endif
