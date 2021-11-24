#include <stdlib.h>

// #include "reader.c"
#include "scanner.c"
#include "parser.h"
// #include "error.c"

Token *currentToken;
Token *lookAhead;

void scan(void) { //scan the next element
  Token* tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType) {
  if (lookAhead->tokenType == tokenType) {
    printToken(lookAhead);
    scan();
  } else missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

void compileProgram(void) {
  assert("Parsing a Program ....");
  eat(KW_PROGRAM);
  eat(TK_IDENT);
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_PERIOD);
  assert("Program parsed!");
}

void compileBlock(void) {
  assert("Parsing a Block ....");
  if (lookAhead->tokenType == KW_CONST) {
    eat(KW_CONST);
    compileConstDecl();
    compileConstDecls();
    compileBlock2();
  } 
  else compileBlock2();
  assert("Block parsed!");
}

void compileBlock2(void) {
  if (lookAhead->tokenType == KW_TYPE) {
    eat(KW_TYPE);
    compileTypeDecl();
    compileTypeDecls();
    compileBlock3();
  } 
  else compileBlock3();
}

void compileBlock3(void) {
  if (lookAhead->tokenType == KW_VAR) {
    eat(KW_VAR);
    compileVarDecl();
    compileVarDecls();
    compileBlock4();
  } 
  else compileBlock4();
}

void compileBlock4(void) {
  compileSubDecls();
  compileBlock5();
}

void compileBlock5(void) {
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

void compileConstDecl(void) {
  // TODO/
  eat(TK_IDENT);
  eat(SB_EQ);
  compileConstant();
  eat(SB_SEMICOLON);
}

void compileConstDecls(void) {
  // TODO/
  while (lookAhead->tokenType == TK_IDENT){
    compileConstDecl();
  }
}

void compileTypeDecls(void) {
  // TODO
  while (lookAhead->tokenType == TK_IDENT){
    compileTypeDecl();
  }
}

void compileTypeDecl(void) {
  // TODO
  eat(TK_IDENT);
  eat(SB_EQ);
  compileType();
  eat(SB_SEMICOLON);
}

void compileVarDecls(void) {
  // TODO/
  while (lookAhead->tokenType == TK_IDENT){
    compileVarDecl();
  }
}

void compileVarDecl(void) {
  // TODO/
  eat(TK_IDENT);
  eat(SB_COLON);
  compileType();
  eat(SB_SEMICOLON);
}

void compileSubDecls(void) {
  assert("Parsing subtoutines ....");
  // TODO
  	eat(KW_FUNCTION);
	  eat(TK_IDENT);
  	compileParams();
	  eat(SB_COLON);
  	compileBasicType();
	  eat(SB_SEMICOLON);
	  compileBlock();
  	eat(SB_SEMICOLON);
  assert("Subtoutines parsed ....");
}

void compileFuncDecl(void) {
  assert("Parsing a function ....");
  // TODO
  assert("Function parsed ....");
}

void compileProcDecl(void) {
  assert("Parsing a procedure ....");
  // TODO
  assert("Procedure parsed ....");
}

void compileUnsignedConstant(void) {
  // TODO
  switch(lookAhead->tokenType){
    case TK_NUMBER:
      eat(TK_NUMBER);
      break;
    case TK_IDENT:
      eat(TK_IDENT);
      break;
    case TK_CHAR:
      eat(TK_CHAR);
      break;
  }
}

void compileConstant(void) {
  // TODO
  compileConstant2();
  switch (lookAhead->tokenType)
  {
  case SB_PLUS:
    eat(SB_PLUS);
    compileConstant2();
    break;
  
  case SB_MINUS:
    eat(SB_MINUS);
    compileConstant2();
    break;

  default:
    compileConstant2();
    break;

  case TK_CHAR:
    eat(TK_CHAR);
    break;
  }
}

void compileConstant2(void) {
  // TODO
  switch(lookAhead->tokenType){
    case TK_IDENT:
      eat(TK_IDENT);
      break;
    
    case TK_NUMBER:
      eat(TK_NUMBER);
      break;
  }
}

void compileType(void) {
  // TODO
  switch(lookAhead -> tokenType){
    case KW_INTEGER:
      eat(KW_INTEGER);
      break;
    case KW_CHAR:
      eat(KW_CHAR);
      break;
    case TK_IDENT:
      eat(TK_IDENT);
      break;
    case KW_ARRAY:
      eat(KW_ARRAY);
      eat(SB_LSEL);
      eat(TK_NUMBER);
      eat(SB_RSEL);
      eat(KW_OF);
      compileType();
  }
}

void compileBasicType(void) {
  // TODO
  switch (lookAhead -> tokenType)
  {
    case KW_INTEGER:
      eat(KW_INTEGER);
      break;

    case KW_CHAR:
      eat(KW_CHAR);
      break; 
  }
}

void compileParams(void) {
  // TODO
  if (lookAhead->tokenType == SB_LPAR){
		eat(SB_LPAR);
		compileParam();
		compileParams2();
		eat(SB_RPAR);
	}

}

void compileParams2(void) {
  // TODO
  if (lookAhead->tokenType == SB_SEMICOLON){
		eat(SB_SEMICOLON);
		compileParam();
		compileParams2();
	}
}

void compileParam(void) {
  // TODO
  switch (lookAhead->tokenType){
		case TK_IDENT:
			eat(TK_IDENT);
			eat(SB_COLON);
			compileBasicType();
			break;
		case KW_VAR:
			eat(KW_VAR);
			eat(TK_IDENT);
			eat(SB_COLON);
			compileBasicType();
			break;
		default:
			error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
			break;
	}

}

void compileStatements(void) {
  // TODO?
  	compileStatement();
	compileStatements2();
}

void compileStatements2(void) {
  // TODO/?
	if (lookAhead->tokenType == SB_SEMICOLON){
		eat(SB_SEMICOLON);
		compileStatement();
		compileStatements2();
	}
	if (lookAhead->tokenType != SB_SEMICOLON 
			&& lookAhead->tokenType != KW_END){
		missingToken(SB_SEMICOLON, lookAhead->lineNo, lookAhead->colNo);
	}
}

void compileStatement(void) {
  switch (lookAhead->tokenType) {
  case TK_IDENT:
    compileAssignSt();
    break;
  case KW_CALL:
    compileCallSt();
    break;
  case KW_BEGIN:
    compileGroupSt();
    break;
  case KW_IF:
    compileIfSt();
    break;
  case KW_WHILE:
    compileWhileSt();
    break;
  case KW_FOR:
    compileForSt();
    break;
    // EmptySt needs to check FOLLOW tokens
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    break;
    // Error occurs
  default:
    error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileAssignSt(void) {
  assert("Parsing an assign statement ....");
  // TODO
  assert("Assign statement parsed ....");
}

void compileCallSt(void) {
  assert("Parsing a call statement ....");
  // TODO
  assert("Call statement parsed ....");
}

void compileGroupSt(void) {
  assert("Parsing a group statement ....");
  // TODO
  assert("Group statement parsed ....");
}

void compileIfSt(void) {
  assert("Parsing an if statement ....");
  eat(KW_IF);
  compileCondition();
  eat(KW_THEN);
  compileStatement();
  if (lookAhead->tokenType == KW_ELSE) 
    compileElseSt();
  assert("If statement parsed ....");
}

void compileElseSt(void) {
  eat(KW_ELSE);
  compileStatement();
}

void compileWhileSt(void) {
  assert("Parsing a while statement ....");
  // TODO
  assert("While statement pased ....");
}

void compileForSt(void) {
  assert("Parsing a for statement ....");
  // TODO
  assert("For statement parsed ....");
}

void compileArguments(void) {
  // TODO
}

void compileArguments2(void) {
  // TODO
}

void compileCondition(void) {
  // TODO
}

void compileCondition2(void) {
  // TODO
}

void compileExpression(void) {
  assert("Parsing an expression");
  // TODO
  assert("Expression parsed");
}

void compileExpression2(void) {
  // TODO
}

void compileExpression3(void) {
  // TODO
}

void compileTerm(void) {
  // TODO
}

void compileTerm2(void) {
  // TODO
}

void compileFactor(void) {
  // TODO
}

void compileIndexes(void) {
  // TODO
}

int compile(char *fileName) {
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  currentToken = NULL;
  lookAhead = getValidToken();

  compileProgram();

  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;

}

int main() {
  compile("..\\test\\example2.kpl");
  return 0;
}
