#include <stdio.h>
#include <stdlib.h>

#include "debug.c"
#include "symtab.c"
#include "scanner.c"
#include "parser.h"

Token *currentToken;
Token *lookAhead;
int mark=0;
int enable;
int enable2;
int enable3;

extern Type* intType;
extern Type* floatType;
extern Type* charType;
extern Type* stringType;
extern SymTab* symtab;

char name_tmp_var[30];
int check_arg = 1;
int check_arg2 = 0;

void scan(void) {
	Token* tmp = currentToken;
	currentToken = lookAhead;
	lookAhead = getValidToken();
	free(tmp);
}

void eat(TokenType tokenType) {
	if (lookAhead->tokenType == tokenType) {
	 	if (enable2){
			printToken(lookAhead);
		}
		scan();
	} else {
   		missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
   	}
}

void compileProgram(void) {						
	if (enable){
		assert("Parsing a Program ....");
	}

	Object* program;

	eat(KW_PROGRAM);
	eat(TK_IDENT);

	symtab->program = createProgramObject(currentToken->string);
	enterBlock(symtab->program->progAttrs->scope);		// --- Move to main block ---
	eat(SB_SEMICOLON);

	compileBlock();
	eat(SB_PERIOD);

	if (enable){
		assert("Program parsed!");
	}

	exitBlock();
}

void compileBlock(void) {						
	if (enable){
		assert("Parsing a Block ....");
	}
	
	Object* constObj;
	ConstantValue* constValue;

	if (lookAhead->tokenType == KW_CONST) {
		eat(KW_CONST);

		do {
			eat(TK_IDENT);

			checkFreshIdent(currentToken->string);
			constObj = createConstantObject(currentToken->string);

			eat(SB_EQ);
			constValue = compileConstant();				// --- Get constant value ---

			constObj->constAttrs->value = constValue;	// --- Assign value to constant ---
			declareObject(constObj);					// --- Declare constant to current block after traversed ---

			eat(SB_SEMICOLON);
		} while (lookAhead->tokenType == TK_IDENT);

		compileBlock2();
	} else {
  		compileBlock2();
  	}

	  if (enable){
		assert("Block parsed!");
	}
}

void compileBlock2(void) {							
	Object* typeObj;
	Type* actualType;

	if (lookAhead->tokenType == KW_TYPE) {
	eat(KW_TYPE);

	do {
		eat(TK_IDENT);

		checkFreshIdent(currentToken->string);
		typeObj = createTypeObject(currentToken->string);

		eat(SB_EQ);
		actualType = compileType();			// --- Get actual type ---

		typeObj->typeAttrs->actualType = actualType;
		declareObject(typeObj);				// --- Declare typeObj to current block after traversed ---

		eat(SB_SEMICOLON);
	} while (lookAhead->tokenType == TK_IDENT);

	compileBlock3();
	}
	else {
		compileBlock3();
	}
}

void compileBlock3(void) {				
	Object* varObj;
	Type* varType;

	if (lookAhead->tokenType == KW_VAR) {
		eat(KW_VAR);

		do {
			eat(TK_IDENT);

			checkFreshIdent(currentToken->string);
			varObj = createVariableObject(currentToken->string);

			eat(SB_COLON);
			varType = compileType();			// --- Assign type to variable ---

			varObj->varAttrs->type = varType;
			declareObject(varObj);				// --- Declare variableObj to current block after traversed ---

			eat(SB_SEMICOLON);
		} while (lookAhead->tokenType == TK_IDENT);

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

void compileSubDecls(void) {
	if (enable){
		assert("Parsing subtoutines ....");
	}

	while ((lookAhead->tokenType == KW_FUNCTION) || (lookAhead->tokenType == KW_PROCEDURE)) {
		if (lookAhead->tokenType == KW_FUNCTION){
			compileFuncDecl();
		}
		else compileProcDecl();
	}

	if (enable){
		assert("Subtoutines parsed ....");
	}
}

void compileFuncDecl(void) {
	check_arg = 0;		
	if (enable){
		assert("Parsing a function ....");
	}
	
	Object* funcObj;
	Type* returnType;

	eat(KW_FUNCTION);
	eat(TK_IDENT);

	checkFreshIdent(currentToken->string);
	funcObj = createFunctionObject(currentToken->string);
	declareObject(funcObj);					// --- Declare funcObj into current block ---
	checkDeclaredFunction(currentToken->string);
	enterBlock(funcObj->funcAttrs->scope);	// --- Move to funcBlock to traversed localObj ---

	compileParams();			// --- Update funcObj 's attributes

	eat(SB_COLON);
	returnType = compileBasicType();		// --- Return type of func ---
	funcObj->funcAttrs->returnType = returnType;

	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_SEMICOLON);

	if (enable){
		assert("Function parsed ....");
	}

	check_arg = 1;
	exitBlock();
}

void compileProcDecl(void) {
	check_arg = 0;			
	if (enable){
  		assert("Parsing a procedure ....");
	}
	
	Object* procObj;

	eat(KW_PROCEDURE);
	eat(TK_IDENT);

	checkFreshIdent(currentToken->string);
	procObj = createProcedureObject(currentToken->string);
	declareObject(procObj);							// --- Declare procedureObj into current block ---

	enterBlock(procObj->procAttrs->scope);			// --- Move to procedureBlock to traversed localObj ---

	compileParams();

	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_SEMICOLON);

	if (enable){
  		assert("Procedure parsed ....");
	}

	check_arg = 1;
	exitBlock();
}

ConstantValue* compileUnsignedConstant(void) {
	ConstantValue* constValue;
	Object* obj;

	switch (lookAhead->tokenType) {
		case TK_NUMBER:
			eat(TK_NUMBER);
			constValue = makeIntConstant(currentToken->value);
			break;
		case TK_FLOAT:
			eat(TK_FLOAT);
			constValue = makeFloatConstant(currentToken->fValue);
			break;
		case TK_IDENT:
			eat(TK_IDENT);

			obj = checkDeclaredConstant(currentToken->string);
			constValue = duplicateConstantValue(obj->constAttrs->value);

			break;
		case TK_CHAR:
			eat(TK_CHAR);
			constValue = makeCharConstant(currentToken->string[0]);
			break;
		case TK_STRING:
			eat(TK_STRING);
			constValue = makeStringConstant(currentToken->stringNode);
		default:
			error(ERR_INVALID_CONSTANT, lookAhead->lineNo, lookAhead->colNo);
		break;
	}
	return constValue;
}

ConstantValue* compileConstant(void) {
	ConstantValue* constValue;

	switch (lookAhead->tokenType) {
		case SB_PLUS:
			eat(SB_PLUS);
			constValue = compileConstant2();
			break;
		case SB_MINUS:
			eat(SB_MINUS);
			constValue = compileConstant2();
			constValue->intValue = - constValue->intValue;
			constValue->floatValue = - constValue->floatValue;
			break;
		case TK_CHAR:
			eat(TK_CHAR);
			constValue = makeCharConstant(currentToken->string[0]);
			break;
		case TK_STRING:
			eat(TK_STRING);
			constValue= makeStringConstant(currentToken->stringNode);
			break;
		default:
			constValue = compileConstant2();
			break;
	}
	return constValue;
}

ConstantValue* compileConstant2(void) {
	ConstantValue* constValue;
	Object* obj;

	switch (lookAhead->tokenType) {
		case TK_NUMBER:
			eat(TK_NUMBER);
			constValue = makeIntConstant(currentToken->value);
			break;
		case TK_FLOAT:
			eat(TK_FLOAT);
			constValue = makeFloatConstant(currentToken->fValue);
			break;
		case TK_IDENT:
			eat(TK_IDENT);
			obj = checkDeclaredConstant(currentToken->string);
			if (obj->constAttrs->value->type == TP_INT){
				constValue = duplicateConstantValue(obj->constAttrs->value);
			}
			else{
				if(obj->constAttrs->value->type == TP_FLOAT){
					constValue = duplicateConstantValue(obj->constAttrs->value);
				}
				else{
					error(ERR_UNDECLARED_CONSTANT,currentToken->lineNo, currentToken->colNo);
				}
			}
			break;
		default:{
			error(ERR_INVALID_CONSTANT, lookAhead->lineNo, lookAhead->colNo);
			break;
		}
	}
	return constValue;
}

Type* compileType(void) {
	Type* type;
	Type* elementType;
	int arraySize;
	Object* obj;

	switch (lookAhead->tokenType) {
		case KW_INTEGER:
			eat(KW_INTEGER);
			type = makeIntType();
			break;
		case KW_CHAR:
			eat(KW_CHAR);
			type = makeCharType();
			break;
		case KW_STRING:
			eat(KW_STRING);
			type = makeStringType();
			break;
		case KW_FLOAT:
			eat(KW_FLOAT);
			type = makeFloatType();
			break;
		case KW_ARRAY:
			eat(KW_ARRAY);
			eat(SB_LSEL);
			eat(TK_NUMBER);
			arraySize = currentToken->value;
			eat(SB_RSEL);
			eat(KW_OF);
			elementType = compileType();
			type = makeArrayType(arraySize, elementType);
			break;
		case TK_IDENT:
			eat(TK_IDENT);
			obj = checkDeclaredType(currentToken->string);
			type = duplicateType(obj->typeAttrs->actualType);
			break;
		default:{
			error(ERR_INVALID_TYPE, lookAhead->lineNo, lookAhead->colNo);
			break;
		}
	}
	return type;
}

Type* compileBasicType(void) {
	Type* type;

	switch (lookAhead->tokenType) {
		case KW_INTEGER:
			eat(KW_INTEGER);
			type = makeIntType();
			break;
		case KW_CHAR:
			eat(KW_CHAR);
			type = makeCharType();
			break;
		case KW_STRING:
			eat(KW_STRING);
			type = makeStringType();
			break;
		case KW_FLOAT:
			eat(KW_FLOAT);
			type = makeFloatType();
			break;
		default:{
			error(ERR_INVALID_BASICTYPE, lookAhead->lineNo, lookAhead->colNo);
			break;
		}
	}
	return type;
}

void compileParams(void) {
	if (lookAhead->tokenType == SB_LPAR) {
		eat(SB_LPAR);
		compileParam();
		while (lookAhead->tokenType == SB_SEMICOLON) {
			eat(SB_SEMICOLON);
			compileParam();
		}
		eat(SB_RPAR);
	}
}

void compileParam(void) {
	Object* param;
	Type* type;

	switch (lookAhead->tokenType) {
		case TK_IDENT:
			eat(TK_IDENT);
			checkFreshIdent(currentToken->string);
			param = createParameterObject(currentToken->string, PARAM_VALUE, symtab->currentScope->owner);
			eat(SB_COLON);
			type = compileBasicType();
			param->paramAttrs->type = type;
			declareObject(param);
			break;
		case KW_VAR:
			eat(KW_VAR);
			eat(TK_IDENT);
			checkFreshIdent(currentToken->string);
			param = createParameterObject(currentToken->string, PARAM_REFERENCE, symtab->currentScope->owner);
			eat(SB_COLON);
			type = compileBasicType();
			param->paramAttrs->type = type;
			declareObject(param);
			break;
		default:{
			error(ERR_INVALID_PARAMETER, lookAhead->lineNo, lookAhead->colNo);
			break;
		}
	}
}

void compileStatements(void) {
	compileStatement();
	while (lookAhead->tokenType == SB_SEMICOLON) {
		eat(SB_SEMICOLON);
		compileStatement();
	}
}

void compileDoWhileSt(void){
	eat(KW_DO);
	compileStatement();
	eat(KW_WHILE);
	compileCondition();	
}

void compileStatement(void) {
	int ln ;
	int cn ;
	switch (lookAhead->tokenType) {
		case TK_IDENT:
			compileAssignSt();
			break;
		case KW_DO:
			compileDoWhileSt();
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
		case KW_UNTIL:
		case KW_ELSE:
			break;

		default:{
			ln = lookAhead->lineNo;
			cn = lookAhead->colNo;
			if(lookAhead->tokenType==TK_NUMBER)
			{
				eat(TK_NUMBER);
				if(lookAhead->tokenType== SB_ASSIGN)
				{
				error(ERR_VARIABLE,ln,cn);
				}
			}
			error(ERR_INVALID_STATEMENT, ln, cn);
			break;
		}
	}
}

Type* compileLValue(int assign) {
	Object* var;
	Type* varType;

	char *tmp;
	strcpy(tmp, lookAhead->string);//
	eat(TK_IDENT);

	if(0){
		Object* obj;
		obj = checkDeclaredLValueIdent(tmp);
		if (obj->test != 1){
			error(ERR_UNDECLARED_VARIABLE,currentToken->lineNo, currentToken->colNo);
		}
	}

  	var = checkDeclaredLValueIdent(currentToken->string);
	if (assign){
		strcpy(name_tmp_var, currentToken->string);
	}

  	switch (var->kind) {
	  	case OBJ_VARIABLE:
			if (var->varAttrs->type->typeClass == TP_ARRAY) {
			  	varType = compileIndexes(var->varAttrs->type);
			}
			else{
			  	varType = var->varAttrs->type;
			}
			break;
		case OBJ_PARAMETER:
			varType = var->paramAttrs->type;
			break;
		case OBJ_FUNCTION:
			varType = var->funcAttrs->returnType;
			break;
		default: {
			error(ERR_INVALID_LVALUE,currentToken->lineNo, currentToken->colNo);
		}
  	}

	return varType;
}

void compileAssignSt(void) {
	if (enable){
		assert("Parsing an assign statement ....");
	}

	Type **lvalueType = NULL;
	Type *expType = NULL;

	lvalueType = (Type**)malloc(sizeof(Type));

	int counterForVariables = 1;

	lvalueType = (Type**)realloc(lvalueType, counterForVariables*sizeof(Type));
	lvalueType[0] = compileLValue(1);
	while(lookAhead->tokenType == SB_COMMA){
		eat(SB_COMMA);
		if(lookAhead->tokenType != TK_IDENT){
			error(ERR_VARIABLE,lookAhead->lineNo,lookAhead->colNo);
		}
		counterForVariables ++;
		lvalueType = (Type**)realloc(lvalueType, counterForVariables*sizeof(Type));
		lvalueType[counterForVariables - 1] = compileLValue(1);
	}

	int counterForExpression = 1;
	
	switch (lookAhead->tokenType){
		case SB_ASSIGN_PLUS:
			eat(SB_ASSIGN_PLUS);
			break;
		case SB_ASSIGN_MINUS:
			eat(SB_ASSIGN_MINUS);
			break;
		case SB_ASSIGN_TIMES:
			eat(SB_ASSIGN_TIMES);
			break;
		case SB_ASSIGN_SLASH:
			eat(SB_ASSIGN_SLASH);
			break;
		case SB_ASSIGN_MOD:
			eat(SB_ASSIGN_MOD);
			break;

		default:
			eat(SB_ASSIGN);
			break;
	}

	expType = compileExpression();
	checkTypeEquality(lvalueType[counterForExpression - 1], expType);
	while(lookAhead->tokenType == SB_COMMA){
		eat(SB_COMMA);
		counterForExpression++;
		expType = compileExpression();
		if(lvalueType[counterForExpression - 1] != NULL){
			checkTypeEquality(lvalueType[counterForExpression - 1], expType);
		}
	}

	if(counterForVariables > counterForExpression){
		error(ERR_MISS_RVALUE, lookAhead->lineNo, lookAhead->colNo);
	}
	if(counterForVariables < counterForExpression){
		error(ERR_MISS_LVALUE, lookAhead->lineNo, lookAhead->colNo);
	}


	// Object* seek = lookupObject(name_tmp_var);//tu them
	// seek->varAttrs->localOffset = 69;//assgined!!!!!
	Object* seek = lookupObject(name_tmp_var);//tu them
	seek->test = 1;

	if (enable){
		assert("Assign statement parsed ....");
	}
}

void compileCallSt(void) {
	if (enable){
		assert("Parsing a call statement ....");
	}

	Object* proc;

	eat(KW_CALL);
	eat(TK_IDENT);
	proc = checkDeclaredProcedure(currentToken->string);

	compileArguments(proc->procAttrs->paramList);

	if (enable){
		assert("Call statement parsed ....");
	}
}

void compileGroupSt(void) {
	if (enable){
		assert("Parsing a group statement ....");
	}

	eat(KW_BEGIN);
	compileStatements();
	eat(KW_END);

	if (enable){
		assert("Group statement parsed ....");
	}
}

void compileIfSt(void) {
	if (enable){
		assert("Parsing an if statement ....");
	}

	eat(KW_IF);
	compileCondition();
	eat(KW_THEN);
	compileStatement();
	if (lookAhead->tokenType == KW_ELSE){
		compileElseSt();
	}

	if (enable){
		assert("If statement parsed ....");
	}
}

void compileElseSt(void) {
	eat(KW_ELSE);
	compileStatement();
}

void compileWhileSt(void) {
	if (enable){
		assert("Parsing a while statement ....");
	}

	eat(KW_WHILE);
	compileCondition();
	eat(KW_DO);
	compileStatement();

	if (enable){
		assert("While statement parsed ....");
	}
}

void compileForSt(void) {
	if (enable){
		assert("Parsing a for statement ....");
	}

	Object* var;
	Type *type;

	eat(KW_FOR);
	eat(TK_IDENT);

	var = checkDeclaredVariable(currentToken->string);
	strcpy(name_tmp_var, currentToken->string);//tu them1

	eat(SB_ASSIGN);
	type = compileExpression();

	checkTypeEquality(var->varAttrs->type, type);

	// Object* seek = lookupObject(name_tmp_var);//tu them2
	// int done = seek->varAttrs->localOffset;//
	// seek->varAttrs->localOffset = 69;//assgined!!!!!

	Object* seek = lookupObject(name_tmp_var);//tu them2
	int done = seek->varAttrs->localOffset;//
	seek->test = 1;//

	eat(KW_TO);
	type = compileExpression();
	
	checkTypeEquality(var->varAttrs->type, type);

	eat(KW_DO);
	compileStatement();

	if (enable){
		assert("For statement parsed ....");
	}

	// seek->varAttrs->localOffset = done;//done assgined!!!!!
	seek->test = done;//done assgined!!!!!
}

// Type* compileIfAssignSt(){
// 	Type *express1;
// 	Type *express2;
// 	eat(KW_IF);
// 	compileCondition();
// 	eat(KW_THEN);
// 	express1 = compileExpression();
// 	eat(KW_ELSE);
// 	express2 = compileExpression();
// 	checkTypeEquality(express1, express2);
// 	return express1;
// }

void compileArgument(Object* param) {
	Type* type;

	if (param->paramAttrs->kind == PARAM_VALUE) {
		type = compileExpression();
		checkTypeEquality(param->paramAttrs->type, type);
	}
	else {
		if(check_arg){
			check_arg2 = 1;
		}
		type = compileLValue(0);
		checkTypeEquality(param->paramAttrs->type, type);
	}

	check_arg2 = 0;
}

void compileArguments(ObjectNode* paramList) {
	ObjectNode* node = paramList;

	switch (lookAhead->tokenType) {
		case SB_LPAR:
			eat(SB_LPAR);
			if (node == NULL){
				error(ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
			}
			compileArgument(node->object);
			node = node->next;

			while (lookAhead->tokenType == SB_COMMA) {
				eat(SB_COMMA);
				
				if (node == NULL){
					error(ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
				}
				
				compileArgument(node->object);
				node = node->next;
			}
			if (node != NULL){
				error(ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
			}
			eat(SB_RPAR);
			break;
			
		default:{
			error(ERR_INVALID_ARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
		}
	}
}

void compileCondition(void) {
	Type* type1;
	Type* type2;

	type1 = compileExpression();
	checkBasicType(type1);

	switch (lookAhead->tokenType) {
		case SB_EQ:
			eat(SB_EQ);
			break;
		case SB_NEQ:
			eat(SB_NEQ);
			break;
		case SB_LE:
			eat(SB_LE);
			break;
		case SB_LT:
			eat(SB_LT);
			break;
		case SB_GE:
			eat(SB_GE);
			break;
		case SB_GT:
			eat(SB_GT);
			break;
		default:{
			error(ERR_INVALID_COMPARATOR, lookAhead->lineNo, lookAhead->colNo);
		}
	}

	type2 = compileExpression();
	checkTypeEquality(type1,type2);
}

Type* compileExpression(void) {
	if (enable){
		assert("Parsing an expression");
	}

	Type* type;

	switch (lookAhead->tokenType) {
		case SB_PLUS:
			eat(SB_PLUS);
			type = compileExpression2();
			checkIntType(type);
			break;
		case SB_MINUS:
			eat(SB_MINUS);
			type = compileExpression2();
			checkIntType(type);
			break;
		case SB_MOD:
			eat(SB_MOD);
			type = compileExpression2();
			checkIntType2(type);
			break;
		// case KW_IF:
		// 	type = compileIfAssignSt();
		// 	break;
		default:
			type = compileExpression2();
			checkIntType(type);
			break;
	}

	if (enable){
		assert("Expression parsed");
	}

	return type;
}

Type* compileExpression2(void) {
	Type* type;

	type = compileTerm();
	type = compileExpression3(type);

	return type;
}

Type* compileExpression3(Type* testType) {
	Type* type;

	switch (lookAhead->tokenType) {
		case SB_PLUS:
		case SB_MINUS:
		case SB_MOD:
			checkIntType(testType);
			eat(lookAhead->tokenType);

			type = compileTerm();
			checkIntType(type);
			checkTypeEquality(testType, type);

			type = compileExpression3(testType);
			break;

		// check the FOLLOW set
		case KW_TO:
		case KW_DO:
		case KW_UNTIL:
		case SB_RPAR:
		case SB_COMMA:
		case SB_EQ:
		case SB_NEQ:
		case SB_LE:
		case SB_LT:
		case SB_GE:
		case SB_GT:
		case SB_RSEL:
		case SB_SEMICOLON:
		case KW_END:
		case KW_ELSE:
		case KW_WHILE:
		case KW_THEN:
			type = testType;
			break;
		default:{
			error(ERR_INVALID_EXPRESSION, lookAhead->lineNo, lookAhead->colNo);
		}
	}

	return type;
}

Type* compileTerm(void) {
	Type* type;

	type = compileFactor();
	type = compileTerm2(type);

	return type;
}

Type* compileTerm2(Type* testType) {
	Type* type;

	switch (lookAhead->tokenType) {
		case SB_TIMES:
		case SB_SLASH:
			checkIntType(testType);
			eat(lookAhead->tokenType);

			type = compileFactor();
			checkIntType(type);
			checkTypeEquality(testType, type);

			type = compileTerm2(testType);
			break;
		
		case SB_MOD:
			checkIntType(testType);
			eat(lookAhead->tokenType);

			type = compileFactor();
			checkIntType2(type);
			checkTypeEquality(testType, type);

			type = compileTerm2(testType);
			break;

		// check the FOLLOW set
		case SB_PLUS:
		case SB_MINUS:
		case KW_TO:
		case KW_DO:
		case KW_UNTIL:
		case SB_RPAR:
		case SB_COMMA:
		case SB_EQ:
		case SB_NEQ:
		case SB_LE:
		case SB_LT:
		case SB_GE:
		case SB_GT:
		case SB_RSEL:
		case SB_SEMICOLON:
		case KW_END:
		case KW_ELSE:
		case KW_THEN:
		case KW_WHILE:
			type = testType;
			break;
		default:{
			error(ERR_INVALID_TERM, lookAhead->lineNo, lookAhead->colNo);
		}
	}

	return type;
}

Type* compileFactor(void) {
	Type* type;
	Object* obj;

	switch (lookAhead->tokenType) {
		case SB_LPAR:
			eat(SB_LPAR);
			type = compileExpression();
			eat(SB_RPAR);
			break;
		case TK_NUMBER:
			eat(TK_NUMBER);
			type = intType;
			break;
		case TK_FLOAT:
			eat(TK_FLOAT);
			type = floatType;
			break;
		case TK_CHAR:
			eat(TK_CHAR);
			type = charType;
			break;
  		case TK_STRING:
			eat(TK_STRING);
			type = stringType;
			break;
		case TK_IDENT:;
			char name_tmp[30];
			strcpy(name_tmp, lookAhead->string);
		
			eat(TK_IDENT);

			if (lookAhead->tokenType == SB_LPAR) {
				obj = checkDeclaredFunction(name_tmp);
			} else {
				obj = checkDeclaredIdent(currentToken->string);
			}

			switch (obj->kind) {
				case OBJ_CONSTANT:
	 		 		switch (obj->constAttrs->value->type) {
	  					case TP_INT:
							type = intType;
							break;
						case TP_FLOAT:
							type = floatType;
							break;
	  					case TP_CHAR:
							type = charType;
							break;
	  					case TP_STRING:
  							type = stringType;
							break;
	  					default:
							break;
						}
	 				break;
				case OBJ_VARIABLE:
	
					if (obj->test != 1){
						error(ERR_UNDECLARED_VARIABLE,currentToken->lineNo, currentToken->colNo);
						break;
					}

					if (obj->varAttrs->type->typeClass == TP_ARRAY){
						type = compileIndexes(obj->varAttrs->type);
					}
					else {
						type = obj->varAttrs->type;
					}
					break;
				case OBJ_PARAMETER:
					type = obj->paramAttrs->type;
					break;
				case OBJ_FUNCTION:
					compileArguments(obj->funcAttrs->paramList);
					type = obj->funcAttrs->returnType;
					break;
				default:
					error(ERR_INVALID_FACTOR,currentToken->lineNo, currentToken->colNo);
					break;
				}
			break;
		// case KW_IF:
		// 	type = compileIfAssignSt();
		// 	break;
		default:{
			error(ERR_INVALID_FACTOR, lookAhead->lineNo, lookAhead->colNo);
		}
	}
  	return type;
}

Type* compileIndexes(Type* arrayType) {
	Type* type;

	while (lookAhead->tokenType == SB_LSEL) {
		eat(SB_LSEL);
		type = compileExpression();
		checkIntType(type);
		checkArrayType(arrayType);
		arrayType = arrayType->elementType;
		eat(SB_RSEL);
	}
	checkBasicType(arrayType);
	return arrayType;
}

int compile(char *fileName) {
	if (openInputStream(fileName) == IO_ERROR){
		printf("co van de ???\n");
		return IO_ERROR;
	}

	currentToken = NULL;
	lookAhead = getValidToken();

	initSymTab();						// --- Initialize symtab ---

	compileProgram();
	
	if (enable3){ // --- Print program to check result ---
		printf("\n--------------------------------\n\n");
		printObject(symtab->program,0,0);
		printf("--------------------------------");
	}
	
	cleanSymTab();						// --- Free symtab ---

	free(currentToken);
	free(lookAhead);
	closeInputStream();
	
	return IO_SUCCESS;
}


int enable  = 0;
int enable2 = 1;
int enable3 = 1;

int main() {
	compile("tests\\test.kpl");
	// compile("tests\\example4.kpl");
	return 0;
}
