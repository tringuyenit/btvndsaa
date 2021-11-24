#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#define NUM_OF_ERRORS 36
struct ErrorMessage {
	ErrorCode errorCode;
	char *message;
};

struct ErrorMessage errors[36]= {
	{ERR_END_OF_COMMENT, "End of comment expected."},
	{ERR_IDENT_TOO_LONG, "Identifier too long."},
	{ERR_INVALID_CONSTANT_CHAR, "Invalid char constant."},
	{ERR_INVALID_STRING,"Invalid string constant."},
	{ERR_INVALID_SYMBOL, "Invalid symbol."},
	{ERR_INVALID_IDENT, "An identifier expected."},
	{ERR_INVALID_CONSTANT, "A constant expected."},
	{ERR_INVALID_TYPE, "A type expected."},
	{ERR_INVALID_BASICTYPE, "A basic type expected."},
	{ERR_INVALID_VARIABLE, "A variable expected."},
	{ERR_INVALID_FUNCTION, "A function identifier expected."},
	{ERR_INVALID_PROCEDURE, "A procedure identifier expected."},
	{ERR_INVALID_PARAMETER, "A parameter expected."},
	{ERR_INVALID_STATEMENT, "Invalid statement."},
	{ERR_INVALID_COMPARATOR, "A comparator expected."},
	{ERR_INVALID_EXPRESSION, "Invalid expression."},
	{ERR_INVALID_TERM, "Invalid term."},
	{ERR_INVALID_FACTOR, "Invalid factor."},
	{ERR_INVALID_LVALUE, "Invalid lvalue in assignment."},
	{ERR_INVALID_ARGUMENTS, "Wrong arguments."},
	{ERR_UNDECLARED_IDENT, "Undeclared identifier."},
	{ERR_UNDECLARED_CONSTANT, "Undeclared constant."},
	{ERR_UNDECLARED_INT_CONSTANT, "Undeclared integer constant."},
	{ERR_UNDECLARED_FLOAT_CONSTANT, "Undeclared float constant."},
	{ERR_UNDECLARED_TYPE, "Undeclared type."},
	{ERR_UNDECLARED_VARIABLE, "Undeclared variable."},
	{ERR_UNDECLARED_FUNCTION, "Undeclared function."},
	{ERR_UNDECLARED_PROCEDURE, "Undeclared procedure."},
	{ERR_DUPLICATE_IDENT, "Duplicate identifier."},
	{ERR_TYPE_INCONSISTENCY, "Type inconsistency"},
	{ERR_VARIABLE, "Left site can't have value"},
	{ERR_MISS_RVALUE, "Missing right value"},
	{ERR_MISS_LVALUE, "Missing left value"},
	{ERR_INVALID_FLOAT_VALUE, "Invalid float value"},
	{ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, "The number of arguments and the number of parameters are inconsistent."},

	{ERR_INVALIDFLOAT, "Invalid float value!"}
};

void error(ErrorCode err, int lineNo, int colNo) {
	int i;
	for (i = 0 ; i < NUM_OF_ERRORS; i ++) {
		if (errors[i].errorCode == err) {
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

			printf("%s\n", errors[i].message);
			exit(0);
		}
	}
}

void missingToken(TokenType tokenType, int lineNo, int colNo) {
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
	printf("Missing %s\n", tokenToString(tokenType));
	exit(0);
}

void assert(char *msg) {
	printf("%s\n", msg);
}
