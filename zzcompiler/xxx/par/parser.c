// #include <stdlib.h>

// #include "debug.c"
// // #include "semantics.c"
// #include "symtab.c"
// #include "scanner.c"
// #include "parser.h"

// Token *currentToken;
// Token *lookAhead;
// int enable = 1; // tu them

// extern Type* intType;
// extern Type* floatType;
// extern Type* charType;
// extern Type* stringType;
// extern SymTab* symtab;

// void scan(void) {
// 	Token* tmp = currentToken;
// 	currentToken = lookAhead;
// 	//-------------------------
// 	lookAhead = getValidToken();
// 	free(tmp);
// }

// void eat(TokenType tokenType) {
// 	if (lookAhead->tokenType == tokenType) {
// 		printToken(lookAhead);
// 		scan();
// 	} else {
// 		missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
// 	}
// }

// void compileProgram(void) {
// 	if (enable){
// 		assert("Parsing a Program ....");
// 	}
	
// 	// Object* program = NULL; //xx
  	
// 	eat(KW_PROGRAM);
// 	eat(TK_IDENT);
// 	symtab->program = createProgramObject(currentToken->string);
	
// 	enterBlock(symtab->program->progAttrs->scope); //xx 
	

// 	eat(SB_SEMICOLON);
// 	compileBlock();
// 	eat(SB_PERIOD);
// 	exitBlock(); //xx

// 	if (enable){
// 		assert("Program parsed!");
// 	}

// }

// void compileBlock(void) {
// 	if (enable){
// 		assert("Parsing a Block ....");
// 	}
// 	if (lookAhead->tokenType == KW_CONST) {
// 		eat(KW_CONST);
// 		compileConstDecl();
// 		compileConstDecls();
// 		compileBlock2();
// 	} 
// 	else compileBlock2();

// 	if (enable){
// 		assert("Block parsed!");
// 	}
// }

// void compileBlock2(void) {
// 	if (lookAhead->tokenType == KW_TYPE) {
// 		eat(KW_TYPE);
// 		compileTypeDecl();
// 		compileTypeDecls();
// 		compileBlock3();
// 	} 
// 	else compileBlock3();
// }

// void compileBlock3(void) {
// 	if (lookAhead->tokenType == KW_VAR) {
// 		eat(KW_VAR);
// 		compileVarDecl();
// 		compileVarDecls();
// 		compileBlock4();
// 	} 
// 	else compileBlock4();
// }

// void compileBlock4(void) {
// 	compileSubDecls();
// 	compileBlock5();
// }

// void compileBlock5(void) {
// 	eat(KW_BEGIN);
// 	compileStatements();
// 	eat(KW_END);
// }

// void compileConstDecls(void) {
// 	if (lookAhead->tokenType == TK_IDENT){
// 		compileConstDecl();
// 		compileConstDecls();
// 	} else {
// 		// error(ERR_INVALIDCONSTDECL, lookAhead->lineNo, lookAhead->colNo);
// 	}
// }

// void compileConstDecl(void) {
// 	Object* constObj = NULL;//xx

// 	eat(TK_IDENT);

// 	constObj = createConstantObject(currentToken->string);//xx

// 	eat(SB_EQ);

// 	constObj->constAttrs->value = compileConstant();// --- Assign value to constant ---
// 	declareObject(constObj); //xx

// 	eat(SB_SEMICOLON);
// }

// void compileTypeDecls(void) {
// 	if (lookAhead->tokenType == TK_IDENT){
// 		compileTypeDecl();
// 		compileTypeDecls();
// 	} else {
// 		// error(ERR_INVALIDTYPEDECL, lookAhead->lineNo, lookAhead->colNo);
// 	}
// }

// void compileTypeDecl(void) {
// 	Object* typeObj = NULL;//xx

// 	eat(TK_IDENT);

// 	typeObj = createTypeObject(currentToken->string);//xx

// 	eat(SB_EQ);

// 	typeObj->typeAttrs->actualType = compileType();// --- Get actual type ---
	
// 	declareObject(typeObj);

// 	eat(SB_SEMICOLON);
// }

// void compileVarDecls(void) {
// 	if (lookAhead->tokenType == TK_IDENT){
// 		compileVarDecl();
// 		compileVarDecls();
// 	} else {
// 		// error(ERR_INVALIDVARDECL, lookAhead->lineNo, lookAhead->colNo);
// 	}
// }

// void compileVarDecl(void) {
// 	Object* varObj = NULL;//xx

// 	eat(TK_IDENT);

// 	varObj = createVariableObject(currentToken->string);//xx

// 	eat(SB_COLON);

// 	varObj->varAttrs->type = compileType();			// --- Assign type to variable ---

// 	declareObject(varObj);//xx

// 	eat(SB_SEMICOLON);
// }

// void compileSubDecls(void) {
// 	if (enable){
// 		assert("Parsing subtoutines ....");
// 	}

// 	switch (lookAhead->tokenType){
// 		case KW_FUNCTION:
// 			compileFuncDecl();
// 			compileSubDecls();
// 			break;
// 		case KW_PROCEDURE:
// 			compileProcDecl();
// 			compileSubDecls();
// 			break;
// 		default:
// 			// ko can error
// 			// error(ERR_INVALIDSUBDECL, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 	}

// 	if (enable){
// 		assert("Subtoutines parsed ....");
// 	}
// }

// void compileFuncDecl(void) {
// 	if (enable){
// 		assert("Parsing a function ....");
// 	}
  	
// 	Object* funcObj = NULL;//xx

// 	eat(KW_FUNCTION);
// 	eat(TK_IDENT);

// 	funcObj = createFunctionObject(currentToken->string); //xx
// 	declareObject(funcObj);					// --- Declare funcObj into current block ---
// 	enterBlock(funcObj->funcAttrs->scope);	// --- Move to funcBlock to traversed localObj ---

// 	compileParams();
// 	eat(SB_COLON);

// 	funcObj->funcAttrs->returnType = compileBasicType();// --- Return type of func ---

// 	eat(SB_SEMICOLON);
// 	compileBlock();
// 	eat(SB_SEMICOLON);

// 	exitBlock();//xx

// 	if (enable){
// 		assert("Function parsed ....");
// 	}
// }

// void compileProcDecl(void) {
// 	if (enable){
//   		assert("Parsing a procedure ....");
// 	}

// 	Object* procObj = NULL;

// 	eat(KW_PROCEDURE);
// 	eat(TK_IDENT);

// 	procObj = createProcedureObject(currentToken->string); //xx
// 	declareObject(procObj);	//xx						// --- Declare procedureObj into current block ---
// 	enterBlock(procObj->procAttrs->scope); //xx

// 	compileParams();
// 	eat(SB_SEMICOLON);
// 	compileBlock();
// 	eat(SB_SEMICOLON);
// 	exitBlock(); //xx

// 	if (enable){
//   		assert("Procedure parsed ....");
// 	}
// }

// void compileParams(void) {
// 	if (lookAhead->tokenType == SB_LPAR){
// 		eat(SB_LPAR);
// 		compileParam();
// 		compileParams2();
// 		eat(SB_RPAR);
// 	}
// }

// void compileParams2(void) {
// 	if (lookAhead->tokenType == SB_SEMICOLON){
// 		eat(SB_SEMICOLON);
// 		compileParam();
// 		compileParams2();
// 	} // ko can error
// }

// void compileParam(void) {
// 	Object* param = NULL;//xx

// 	switch (lookAhead->tokenType){
// 		case TK_IDENT:
// 			eat(TK_IDENT);

// 			param = createParameterObject(currentToken->string, PARAM_VALUE, symtab->currentScope->owner);//xx

// 			eat(SB_COLON);
			
// 			switch (lookAhead->tokenType){//tu lam -- khac
// 				case KW_FLOAT:
// 				case KW_INTEGER:
// 				case KW_CHAR:
// 				case KW_STRING:
// 					param->paramAttrs->type = compileBasicType();//xx
// 					declareObject(param);//xx
// 					break;
// 				default:
// 					error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
// 					break;
// 			}

// 			break;
// 		case KW_VAR:
// 			eat(KW_VAR);
// 			eat(TK_IDENT);

// 			param = createParameterObject(currentToken->string, PARAM_REFERENCE, symtab->currentScope->owner);//xx

// 			eat(SB_COLON);

// 			switch (lookAhead->tokenType){//tu lam -- khac
// 				case KW_FLOAT:
// 				case KW_INTEGER:
// 				case KW_CHAR:
// 				case KW_STRING:
// 					param->paramAttrs->type = compileBasicType();//xx
// 					declareObject(param);//xx
// 					break;
// 				default:
// 					error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
// 					break;
// 			}
			
// 			break;
// 		default:
// 			error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 	}
// }

// Type* compileType(void) {

// 	Type* type = NULL;
// 	Type* elementType = NULL;
// 	int arraySize;

// 	switch (lookAhead->tokenType){
// 		case KW_INTEGER: 
// 			eat(KW_INTEGER);
// 			type =	makeIntType();//xx
// 			break;
// 		case KW_CHAR:
// 			eat(KW_CHAR);
// 			type = makeCharType();//xx
// 			break;
// 		case TK_IDENT:
// 			eat(TK_IDENT);

// 			// Object* obj = lookupObject(currentToken->string); //xx
// 			// type = duplicateType(obj->typeAttrs->actualType); //xx
// 			break;

// 		case KW_STRING:
// 			eat(KW_STRING);
// 			type = makeStringType();//xx
// 			break;
// 		case KW_FLOAT:
// 			eat(KW_FLOAT);
// 			type = makeFloatType();//xx
// 			break;

// 		case KW_ARRAY:
// 			eat(KW_ARRAY);
// 			eat(SB_LSEL);
			
// 			switch (lookAhead->tokenType){ // tu them
// 				case TK_NUMBER:
// 					eat(TK_NUMBER);
// 					arraySize = currentToken->value; //xx
// 					break;
// 				case TK_FLOAT:
// 					eat(TK_FLOAT);
// 					arraySize = currentToken->value;//xx
// 					break;
// 				default:
// 					error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
// 					break;
// 			}//

// 			eat(SB_RSEL);
// 			eat(KW_OF);
// 			elementType = compileType(); //xx
// 			type = makeArrayType(arraySize, elementType);//xx
// 			break;
// 		default:
// 			error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 	}

// 	return type;//xx
// }

// Type* compileBasicType(void) {
// 	Type* type = NULL;//xx

// 	switch (lookAhead->tokenType){

// 		case KW_INTEGER:
// 			eat(KW_INTEGER);
// 			type = makeIntType();
// 			break;
// 		case KW_CHAR:
// 			eat(KW_CHAR);
// 			type = makeCharType();
// 			break;

// 		case KW_STRING:
// 			eat(KW_STRING);
// 			type = makeStringType();
// 			break;
// 		case KW_FLOAT:
// 			eat(KW_FLOAT);
// 			type = makeFloatType();
// 			break;

// 		default:
// 			error(ERR_INVALIDBASICTYPE, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 	}

// 	return type;//xx
// }

// ConstantValue* compileUnsignedConstant(void) {
// 	ConstantValue* constValue = NULL;

// 	switch (lookAhead->tokenType){
// 		case TK_NUMBER:
// 			eat(TK_NUMBER);
// 			constValue = makeIntConstant(currentToken->value); //xx
// 			break;
// 		case TK_FLOAT:
// 			eat(TK_FLOAT);
// 			constValue = makeFloatConstant(currentToken->fValue);//xx
// 			break;
// 		case TK_IDENT:
// 			eat(TK_IDENT);
// 			// Object* obj = lookupObject(currentToken->string); //xx
// 			// constValue = duplicateConstantValue(obj->constAttrs->value); //xx
// 			break;
// 		case TK_CHAR:
// 			eat(TK_CHAR);
// 			constValue = makeCharConstant(currentToken->string[0]);
// 			break;
		
// 		case TK_STRING:
// 			eat(TK_STRING);
// 			constValue = makeStringConstant(currentToken->stringNode);
// 			break;

// 		default:
// 			// khong biet error nao ?
// 			// error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
// 			error(ERR_INVALIDCHARCONSTANT, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 	}

// 	return constValue; //xx
// }

// ConstantValue* compileConstant(void) {
// 	ConstantValue* constValue = NULL;

// 	switch (lookAhead->tokenType) {
// 		case SB_PLUS: 
// 			eat(SB_PLUS);
// 			constValue = compileConstant2();
// 			break;
// 		case SB_MINUS:
// 			eat(SB_MINUS);
// 			constValue = compileConstant2();
// 			constValue->intValue = - constValue->intValue;
// 			constValue->floatValue = - constValue->floatValue;
// 			break;
// 		case TK_CHAR:
// 			eat(TK_CHAR);
// 			constValue = makeCharConstant(currentToken->string[0]);
// 			break;

// 		case TK_STRING:
// 			eat(TK_STRING);
// 			constValue= makeStringConstant(currentToken->stringNode);
// 			break;

// 		default: 
// 			constValue = compileConstant2();
// 			break;
// 	}

// 	return constValue;
// }

// ConstantValue* compileConstant2(void) {
// 	ConstantValue* constValue = NULL;

// 	switch (lookAhead->tokenType) {
// 		case TK_IDENT:
// 			// Object * obj = lookupObject(currentToken->string); //xx

// 			eat(TK_IDENT);

// 			// if (obj->constAttrs->value->type == TP_INT){
// 			// 	constValue = duplicateConstantValue(obj->constAttrs->value);
// 			// }else{
// 			// 	if(obj->constAttrs->value->type == TP_FLOAT){
// 			// 		constValue = duplicateConstantValue(obj->constAttrs->value);
// 			// 	}else{
// 			// 		error(ERR_INVALIDCONSTDECL,currentToken->lineNo, currentToken->colNo);
// 			// 	}
// 			// }

// 			break;
// 		case TK_NUMBER:
// 			eat(TK_NUMBER);
// 			constValue = makeIntConstant(currentToken->value); //xx
// 			break;
// 		case TK_FLOAT:
// 			eat(TK_FLOAT);
// 			constValue = makeFloatConstant(currentToken->value); //xx
// 			break;
// 		default:
// 			error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 	}

// 	return constValue;//xx
// }

// void compileStatements(void) {
// 	compileStatement();
// 	compileStatements2();
// }

// void compileStatements2(void) {
// 	if (lookAhead->tokenType == SB_SEMICOLON){
// 		eat(SB_SEMICOLON);
// 		compileStatement();
// 		compileStatements2();
// 	}

// 	if (lookAhead->tokenType != SB_SEMICOLON 
// 			&& lookAhead->tokenType != KW_END){
// 		missingToken(SB_SEMICOLON, lookAhead->lineNo, lookAhead->colNo);
// 	}
// }

// void compileStatement(void) {
// 	switch (lookAhead->tokenType) {
// 		case TK_IDENT:
// 			compileAssignSt();
// 			break;
// 		case KW_CALL:
// 			compileCallSt();
// 			break;
// 		case KW_BEGIN:
// 			compileGroupSt();
// 			break;
// 		case KW_IF:
// 			compileIfSt();
// 			break;
// 		case KW_WHILE:
// 			compileWhileSt();
// 			break;
// 		case KW_FOR:
// 			compileForSt();
// 			break;

// 		// EmptySt
// 		case SB_SEMICOLON:  // ???
// 		case KW_END:
// 		case KW_UNTIL:
// 		case KW_ELSE:
// 			break;


// 		default: // -- khac
// 			error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 		}
// }

// void compileAssignSt(void) {
// 	if (enable){
// 		assert("Parsing an assign statement ....");
// 	}

// 	// Type **lvalueType = NULL;//xx
// 	Type *expType = NULL;//xx
// 	// lvalueType = (Type**)malloc(sizeof(Type));//xx
// 	// int counterForVariables = 1;//xx
// 	// lvalueType = (Type**)realloc(lvalueType, counterForVariables*sizeof(Type));//xx
// 	// lvalueType[0] = compileVariable();//xx

// 	compileVariable(); // thay bang 2 dong duoi -- y het
// 	// eat(TK_IDENT);
// 	// compileIndexes();

// 	switch (lookAhead->tokenType){
// 		case SB_ASSIGN_PLUS:
// 			eat(SB_ASSIGN_PLUS);
// 			break;
// 		case SB_ASSIGN_MINUS:
// 			eat(SB_ASSIGN_MINUS);
// 			break;
// 		case SB_ASSIGN_TIMES:
// 			eat(SB_ASSIGN_TIMES);
// 			break;
// 		case SB_ASSIGN_SLASH:
// 			eat(SB_ASSIGN_SLASH);
// 			break;
// 		case SB_ASSIGN_MOD:
// 			eat(SB_ASSIGN_MOD);
// 			break;
// 		default:
// 			eat(SB_ASSIGN);
// 			break;
// 	}
	
// 	expType = compileExpression();

// 	if (enable){
// 		assert("Assign statement parsed ....");
// 	}
// }

// void compileCallSt(void) {
// 	if (enable){
// 		assert("Parsing a call statement ....");
// 	}

// 	// Object* proc = NULL;//xx

// 	eat(KW_CALL);
// 	eat(TK_IDENT);
// 	compileArguments();

// 	if (enable){
// 		assert("Call statement parsed ....");
// 	}
// }

// void compileGroupSt(void) {
// 	if (enable){
// 		assert("Parsing a group statement ....");
// 	}
  	
// 	eat(KW_BEGIN);
// 	compileStatements();
// 	eat(KW_END);

// 	if (enable){
// 		assert("Group statement parsed ....");
// 	}
// }

// void compileIfSt(void) {
// 	if (enable){
// 		assert("Parsing an if statement ....");
// 	}

// 	eat(KW_IF);
// 	compileCondition();
// 	eat(KW_THEN);
// 	compileStatement();
// 	if (lookAhead->tokenType == KW_ELSE) {
// 		compileElseSt();
// 	}

// 	if (enable){
// 		assert("If statement parsed ....");
// 	}
// }

// void compileElseSt(void) {
// 	eat(KW_ELSE);
// 	compileStatement();
// }

// void compileWhileSt(void) {
// 	if (enable){
// 		assert("Parsing a while statement ....");
// 	}
  
// 	eat(KW_WHILE);
// 	compileCondition();
// 	eat(KW_DO);
// 	compileStatement();

// 	if (enable){
// 		assert("While statement parsed ....");
// 	}
// }

// void compileForSt(void) {
// 	if (enable){
// 		assert("Parsing a for statement ....");
// 	}

// 	Object* var = NULL;
// 	Type *type = NULL;

// 	eat(KW_FOR);
// 	eat(TK_IDENT);
// 	eat(SB_ASSIGN);

// 	type = compileExpression();//xx

// 	eat(KW_TO);

// 	type = compileExpression();//xx

// 	eat(KW_DO);
// 	compileStatement();

// 	if (enable){
// 		assert("For statement parsed ....");
// 	}
// }

// void compileArguments(void) { // !!!!!!!
// 	Type* type = NULL;

// 	if (lookAhead->tokenType == SB_LPAR){
// 		eat(SB_LPAR);
// 		type = compileExpression();
// 		compileArguments2();
// 		eat(SB_RPAR);
// 	} else{
// 		// error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
// 		// hinh nhu khong can
// 	}
// }

// void compileArguments2(void) {
// 	Type* type = NULL;//xx
// 	if (lookAhead->tokenType == SB_COMMA){
// 		eat(SB_COMMA);
// 		switch (lookAhead->tokenType){ // tu lam
// 				case TK_FLOAT:
// 				case TK_NUMBER:
// 				case TK_CHAR:
// 				case TK_IDENT:
// 				case SB_LPAR:
// 				case SB_PLUS:
// 				case SB_MINUS:
// 					type = compileExpression();
// 					compileArguments2();
// 					break;
// 				default:
// 					error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
// 					break;
// 		}
// 	}
// }

// void compileCondition(void) {
// 	Type* type1 = NULL;//xx
// 	type1 = compileExpression();//xx
// 	compileCondition2();
// }

// void compileCondition2(void) {
// 	Type* type2 = NULL;

// 	switch (lookAhead->tokenType){
// 		case SB_EQ:
// 		case SB_NEQ:
// 		case SB_LE:
// 		case SB_LT:
// 		case SB_GE:
// 		case SB_GT:
// 			eat(lookAhead->tokenType);
// 			type2 = compileExpression();
// 			break;
// 		default:
// 			error(ERR_INVALIDCONDITION, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 	}
// }

// Type* compileExpression(void) {
// 	if (enable){
// 		assert("Parsing an expression");
// 	}

// 	Type* type = NULL;

// 	switch (lookAhead->tokenType){
// 		case SB_PLUS:
// 			eat(SB_PLUS);
// 			type = compileExpression2();//xx
// 			break;
// 		case SB_MINUS:
// 			eat(SB_MINUS);
// 			type = compileExpression2();//xx
// 			break;
// 		default:
// 			type = compileExpression2();//xx
// 			break;
// 	}

// 	if (enable){
// 		assert("Expression parsed");
// 	}

// 	return type;//xx
// }

// Type* compileExpression2(void) {
// 	Type* type = NULL;//xx
// 	type = compileTerm();//xx
// 	compileExpression3();
// 	return type;
// }

// void compileExpression3(void) {
// 	Type* type = NULL;//xx
// 	switch (lookAhead->tokenType){
// 		case SB_PLUS:
// 			eat(SB_PLUS);
// 			switch (lookAhead->tokenType){ // tu lam -- khac
// 				case TK_FLOAT:
// 				case TK_NUMBER:
// 				case TK_CHAR:
// 				case TK_IDENT:
// 				case SB_LPAR:
// 					type = compileTerm();//xx
// 					compileExpression3();
// 					break;
// 				default:
// 					error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
// 					break;
// 			}

// 			break;

// 		case SB_MINUS:
// 			eat(SB_MINUS);
// 			switch (lookAhead->tokenType){ // tu lam
// 				case TK_FLOAT:
// 				case TK_NUMBER:
// 				case TK_CHAR:
// 				case TK_IDENT:
// 				case SB_LPAR:
// 					type = compileTerm();
// 					compileExpression3();
// 					break;
// 				default:
// 					error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
// 					break;
// 			}

// 			break;
//   	}	 
// }

// Type* compileTerm(void) {
// 	Type* type = NULL;//xx

// 	type = compileFactor();//xx
// 	compileTerm2();

// 	return type;
// }

// void compileTerm2(void) {
// 	Type* type = NULL;

// 	switch (lookAhead->tokenType){
// 		case SB_TIMES:
// 			eat(SB_TIMES);
// 			type = compileFactor();
// 			compileTerm2();
// 			break;
// 		case SB_MOD:
// 			eat(SB_MOD);
// 			type = compileFactor();
// 			compileTerm2();
// 			break;
// 		case SB_SLASH:
// 			eat(SB_SLASH);
// 			type = compileFactor();
// 			compileTerm2();
// 			break;


// 		case SB_PLUS: //???
// 		case SB_MINUS:
// 		case KW_TO:
// 		case KW_DO:
// 		case KW_UNTIL:
// 		case SB_RPAR:
// 		case SB_COMMA:
// 		case SB_EQ:
// 		case SB_NEQ:
// 		case SB_LE:
// 		case SB_LT:
// 		case SB_GE:
// 		case SB_GT:
// 		case SB_RSEL:
// 		case SB_SEMICOLON:
// 		case KW_END:
// 		case KW_ELSE:
// 		case KW_THEN:
// 		case KW_WHILE:
// 			break;

// 		default:
// 			error(ERR_INVALIDTERM, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 	}
// }

// Type* compileFactor(void) {
// 	Type* type = NULL;//xx

// 	switch (lookAhead->tokenType){
// 		case TK_NUMBER:
// 			eat(lookAhead->tokenType);
// 			type = intType;
// 			break;
// 		case TK_CHAR:
// 			eat(lookAhead->tokenType);
// 			type = charType;
// 			break;
// 		case TK_STRING:
// 			eat(lookAhead->tokenType);
// 			type = stringType;
// 			break;
// 		case TK_FLOAT:
// 			eat(lookAhead->tokenType);
// 			type = floatType;
// 			break;
// 		case TK_IDENT:
// 			eat(TK_IDENT);
	
// 			// da co eat INDENT o trong
// 			if (lookAhead->tokenType == SB_LPAR){
// 				// compileFunctionApp(); thay bang dong o duoi
// 				compileArguments();
// 			} else {
// 				type = compileIndexes();
// 			}

// 			break;

// 		case SB_LPAR:
// 			eat(SB_LPAR);
// 			type = compileExpression();
// 			eat(SB_RPAR);
// 			break;
// 		default:
// 			error(ERR_INVALIDFACTOR, lookAhead->lineNo, lookAhead->colNo);
// 			break;
// 	}

// 	return type;
// }

// Type* compileVariable(void) {
// 	Object* var = NULL;//xx
// 	Type* varType = NULL;//xx

// 	eat(TK_IDENT);
// 	varType = compileIndexes();//xx

// 	return varType;
// }

// void compileFunctionApp(void) {
// 	eat(TK_IDENT);
// 	compileArguments();
// }

// Type* compileIndexes(void) {
// 	Type* type = NULL;//xx

// 	if (lookAhead->tokenType == SB_LSEL){
// 		eat(SB_LSEL);
// 		eat(TK_IDENT);
// 		// type = compileExpression();
// 		eat(SB_RSEL);
// 		compileIndexes();
// 	}

// 	return type;
// }

// int compile(char *fileName) {
// 	if (openInputStream(fileName) == IO_ERROR)
// 		return IO_ERROR;

// 	currentToken = NULL;
// 	lookAhead = getValidToken();

// 	initSymTab();

// 	compileProgram();

// 	printf("\n-----------------------------\n\n");
// 	printObject(symtab->program,0);// --- Print program to check result ---
	
// 	cleanSymTab();//xx

// 	free(currentToken);
// 	free(lookAhead);
// 	closeInputStream();
// 	return IO_SUCCESS;
// }


// int main() {
// 	compile("tests\\example4.kpl");
// 	return 0;
// }


#include <stdio.h>
#include <stdlib.h>

// #include "reader.h"
// #include "scanner.h"
// #include "parser.h"
// #include "semantics.h"
// #include "error.h"
// #include "debug.h"

#include "debug.c"
#include "semantics.c"
#include "symtab.c"
#include "scanner.c"
#include "parser.h"


Token *currentToken;
Token *lookAhead;
int mark=0;
int enable = 1; // tu them

extern Type* intType;
extern Type* floatType;
extern Type* charType;
extern Type* stringType;
extern SymTab* symtab;

void scan(void) {
	Token* tmp = currentToken;
	currentToken = lookAhead;
	lookAhead = getValidToken();
	free(tmp);
}

void eat(TokenType tokenType) {
	if (lookAhead->tokenType == tokenType) {
	 	printToken(lookAhead);
		scan();
	} else {
   		missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
   	}
}

void compileProgram(void) {						// --- Initialize programObj ---
	Object* program;

	eat(KW_PROGRAM);
	eat(TK_IDENT);

	symtab->program = createProgramObject(currentToken->string);
	enterBlock(symtab->program->progAttrs->scope);		// --- Move to main block ---

	eat(SB_SEMICOLON);

	compileBlock();
	eat(SB_PERIOD);

	exitBlock();
}

void compileBlock(void) {						// --- Declare constantObj ---
	Object* constObj;
	ConstantValue* constValue;

	if (lookAhead->tokenType == KW_CONST) {
		eat(KW_CONST);

		do {
			eat(TK_IDENT);

			// checkFreshIdent(currentToken->string);
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
}

void compileBlock2(void) {							// --- Declare typeObj ---
	Object* typeObj;
	Type* actualType;

	if (lookAhead->tokenType == KW_TYPE) {
	eat(KW_TYPE);

	do {
		eat(TK_IDENT);

		// checkFreshIdent(currentToken->string);
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

void compileBlock3(void) {				// --- Declare variableObj ---
	Object* varObj;
	Type* varType;

	if (lookAhead->tokenType == KW_VAR) {
	eat(KW_VAR);

	do {
		eat(TK_IDENT);

		// checkFreshIdent(currentToken->string);
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
	while ((lookAhead->tokenType == KW_FUNCTION) || (lookAhead->tokenType == KW_PROCEDURE)) {
		if (lookAhead->tokenType == KW_FUNCTION){
			compileFuncDecl();
		}
		else compileProcDecl();
	}
}

void compileFuncDecl(void) {			// --- Declare funcObj ---
	Object* funcObj;
	Type* returnType;

	eat(KW_FUNCTION);
	eat(TK_IDENT);

	// checkFreshIdent(currentToken->string);
	funcObj = createFunctionObject(currentToken->string);
	declareObject(funcObj);					// --- Declare funcObj into current block ---

	enterBlock(funcObj->funcAttrs->scope);	// --- Move to funcBlock to traversed localObj ---

	compileParams();			// --- Update funcObj 's attributes

	eat(SB_COLON);
	returnType = compileBasicType();		// --- Return type of func ---
	funcObj->funcAttrs->returnType = returnType;

	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_SEMICOLON);

	exitBlock();
}

void compileProcDecl(void) {			// --- Declare procedureObj ---
	Object* procObj;

	eat(KW_PROCEDURE);
	eat(TK_IDENT);

	// checkFreshIdent(currentToken->string);
	procObj = createProcedureObject(currentToken->string);
	declareObject(procObj);							// --- Declare procedureObj into current block ---

	enterBlock(procObj->procAttrs->scope);			// --- Move to procedureBlock to traversed localObj ---

	compileParams();

	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_SEMICOLON);

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
			constValue =makeStringConstant(currentToken->stringNode);
		default:
			error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
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
		// case TK_NUMBER:
		// 	eat(TK_NUMBER);
		// 	if(currentToken->flagNumber != 0){
		// 		constValue = makeIntConstant(currentToken->value);
		// 	}else{
		// 		constValue = makeDoubleConstant(currentToken->fValue);
		// 	}
		// 	break;
		case TK_NUMBER:
			eat(TK_NUMBER);
			constValue = makeIntConstant(currentToken->value);
			break;
		case TK_FLOAT:
			eat(TK_FLOAT);
			constValue = makeFloatConstant(currentToken->value);
			break;
		case TK_IDENT:
			eat(TK_IDENT);
			obj = checkDeclaredConstant(currentToken->string);
			if (obj->constAttrs->value->type == TP_INT){
				constValue = duplicateConstantValue(obj->constAttrs->value);
			}else{
				if(obj->constAttrs->value->type == TP_FLOAT){
					constValue = duplicateConstantValue(obj->constAttrs->value);
				}else{
					error(ERR_INVALIDCONSTDECL,currentToken->lineNo, currentToken->colNo);
				}
			}
			break;
		default:{
			error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
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
			type =	makeIntType();
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
			error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
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
			type =makeStringType();
			break;
		case KW_FLOAT:
			eat(KW_FLOAT);
			type = makeFloatType();
			break;
		default:{
			error(ERR_INVALIDBASICTYPE, lookAhead->lineNo, lookAhead->colNo);
			break;
		}
	}
	return type;
}

void compileParams(void) {				// --- Declare paramObj ---
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
			error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
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
		// Error occurs
		default:{
			// ln= lookAhead->lineNo;
			// cn=lookAhead->colNo;
			// if(lookAhead->tokenType==TK_NUMBER)
			// {
			// 	eat(TK_NUMBER);
			// 	if(lookAhead->tokenType== SB_ASSIGN)
			// 	{
			// 	error(ERR_VARIABLE,ln,cn);
			// 	}
			// }
			error(ERR_INVALIDSTATEMENT, ln, cn);
			break;
		}
	}
}

Type* compileLValue(void) {
	Object* var;
	Type* varType;

	eat(TK_IDENT);

  	var = checkDeclaredLValueIdent(currentToken->string);

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

	// //thay switch tren
	// varType = compileIndexes();

	return varType;
}

void compileAssignSt(void) {
	Type **lvalueType = NULL;
	Type *expType = NULL;

	lvalueType = (Type**)malloc(sizeof(Type));

	int counterForVariables = 1;

	lvalueType = (Type**)realloc(lvalueType, counterForVariables*sizeof(Type));
	lvalueType[0] = compileLValue();
	while(lookAhead->tokenType == SB_COMMA){
		eat(SB_COMMA);
		// if(lookAhead->tokenType != TK_IDENT){
		// 	error(ERR_VARIABLE,lookAhead->lineNo,lookAhead->colNo);
		// }
		counterForVariables ++;
		lvalueType = (Type**)realloc(lvalueType, counterForVariables*sizeof(Type));
		lvalueType[counterForVariables - 1] = compileLValue();
	}

	int counterForExpression = 1;
	eat(SB_ASSIGN);
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

	// if(counterForVariables > counterForExpression){
	// 	error(ERR_MISS_RVALUE, lookAhead->lineNo, lookAhead->colNo);
	// }
	// if(counterForVariables < counterForExpression){
	// 	error(ERR_MISS_LVALUE, lookAhead->lineNo, lookAhead->colNo);
	// }
}

void compileCallSt(void) {
	Object* proc;

	eat(KW_CALL);
	eat(TK_IDENT);

	proc = checkDeclaredProcedure(currentToken->string);

	compileArguments(proc->procAttrs->paramList);

	// compileArguments(); //thay 2 cai tren
}

void compileGroupSt(void) {
	eat(KW_BEGIN);
	compileStatements();
	eat(KW_END);
}

void compileIfSt(void) {
	eat(KW_IF);
	compileCondition();
	eat(KW_THEN);
	compileStatement();
	if (lookAhead->tokenType == KW_ELSE){
		compileElseSt();
	}
}

Type* compileIfAssignSt(){
	Type *express1;
	Type *express2;
	eat(KW_IF);
	compileCondition();
	eat(KW_THEN);
	express1 = compileExpression();
	eat(KW_ELSE);
	express2 = compileExpression();
	checkTypeEquality(express1, express2);
	return express1;
}

void compileElseSt(void) {
	eat(KW_ELSE);
	compileStatement();
}

void compileWhileSt(void) {
	eat(KW_WHILE);
	compileCondition();
	eat(KW_DO);
	compileStatement();
}

void compileForSt(void) {
	Object* var;
	Type *type;

	eat(KW_FOR);
	eat(TK_IDENT);

	var = checkDeclaredVariable(currentToken->string);

	eat(SB_ASSIGN);
	type = compileExpression();
	checkTypeEquality(var->varAttrs->type, type);

	eat(KW_TO);
	type = compileExpression();
	checkTypeEquality(var->varAttrs->type, type);

	eat(KW_DO);
	compileStatement();
}

void compileArgument(Object* param) {
	Type* type;

	if (param->paramAttrs->kind == PARAM_VALUE) {
		type = compileExpression();
		// checkTypeEquality(type, param->paramAttrs->type);
	}
	else {
		type = compileLValue();
		// checkTypeEquality(type, param->paramAttrs->type);
	}
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
			// Check FOLLOW set
		case SB_TIMES:
		case SB_SLASH:
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
			break;
		default:{
			error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
		}
	}
}


// //////Thay 2 arguments
// void compileArguments(void) { // !!!!!!!
// 	Type* type = NULL;

// 	if (lookAhead->tokenType == SB_LPAR){
// 		eat(SB_LPAR);
// 		type = compileExpression();
// 		compileArguments2();
// 		eat(SB_RPAR);
// 	} else{
// 		// error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
// 		// hinh nhu khong can
// 	}
// }

// void compileArguments2(void) {
// 	Type* type = NULL;//xx
// 	if (lookAhead->tokenType == SB_COMMA){
// 		eat(SB_COMMA);
// 		switch (lookAhead->tokenType){ // tu lam
// 				case TK_FLOAT:
// 				case TK_NUMBER:
// 				case TK_CHAR:
// 				case TK_IDENT:
// 				case SB_LPAR:
// 				case SB_PLUS:
// 				case SB_MINUS:
// 					type = compileExpression();
// 					compileArguments2();
// 					break;
// 				default:
// 					error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
// 					break;
// 		}
// 	}
// }

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
			error(ERR_INVALIDCOMPARATOR, lookAhead->lineNo, lookAhead->colNo);
		}
	}

	type2 = compileExpression();
	checkTypeEquality(type1,type2);
}

Type* compileExpression(void) {
	Type* type;

	switch (lookAhead->tokenType) {
		case SB_PLUS:
			eat(SB_PLUS);
			type = compileExpression2();
			if(type == intType){
				checkIntType(type);
			}
			else if(type == floatType){
				checkFloatType(type);
			}
			break;
		case SB_MINUS:
			eat(SB_MINUS);
			type = compileExpression2();
			if(type == intType){
				checkIntType(type);
			}
			else if(type == floatType){
				checkFloatType(type);
			}
			break;
		case KW_IF:
			type = compileIfAssignSt();
			break;
		default:
			type = compileExpression2();
	}
	return type;
}

Type* compileExpression2(void) {
	Type* type;

	type = compileTerm();
	compileExpression3();

	return type;
}

void compileExpression3(void) {
	Type* type;

	switch (lookAhead->tokenType) {
		case SB_PLUS:
			eat(SB_PLUS);
			type = compileTerm();
			if(type == intType){
				checkIntType(type);
			}else if(type == floatType){
				checkFloatType(type);
			}
			compileExpression3();
			break;
		case SB_MINUS:
			eat(SB_MINUS);
			type = compileTerm();
			if(type == intType){
				checkIntType(type);
			}
			else if(type == floatType){
				checkFloatType(type);
			}
			compileExpression3();
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
		case KW_THEN:
		case KW_WHILE:
			break;
		default:{
			error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
		}
	}
}

Type* compileTerm(void) {
	Type* type;

	type = compileFactor();
	compileTerm2();

	return type;
}

void compileTerm2(void) {
	Type* type;

	switch (lookAhead->tokenType) {
		case SB_TIMES:
			eat(SB_TIMES);
			type = compileFactor();
			if(type == intType){
				checkIntType(type);
			}
			else if(type == floatType){
				checkFloatType(type);
			}
			compileTerm2();
			break;
		case SB_SLASH:
			eat(SB_SLASH);
			type = compileFactor();
			if(type == intType){
				checkIntType(type);
			}
			else if(type == floatType){
				checkFloatType(type);
			}
			compileTerm2();
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
			break;
		default:{
			error(ERR_INVALIDTERM, lookAhead->lineNo, lookAhead->colNo);
		}
	}
}

Type* compileFactor(void) {
	Type* type;
	Object* obj;

	switch (lookAhead->tokenType) {
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
		case TK_IDENT:
			eat(TK_IDENT);
			obj = checkDeclaredIdent(currentToken->string);
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
	  					case TP_STRING:
  							type = stringType;
							break;
	  					default:
							break;
						}
	 				break;
				case OBJ_VARIABLE:
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
					error(ERR_INVALIDFACTOR,currentToken->lineNo, currentToken->colNo);
					break;
				}


			// // thay switch trennnn
			// if (lookAhead->tokenType == SB_LPAR){
			// 	// compileFunctionApp(); thay bang dong o duoi
			// 	compileArguments();
			// } else {
			// 	type = compileIndexes();
			// }


			break;

		case KW_IF:
			type = compileIfAssignSt();
			break;
		default:{
			error(ERR_INVALIDFACTOR, lookAhead->lineNo, lookAhead->colNo);
		}
	}
  	return type;
}

Type* compileIndexes(Type* arrayType) {
	Type* type;

	while (lookAhead->tokenType == SB_LSEL) {
		eat(SB_LSEL);
		type = compileExpression();
		// checkIntType(type);
		// checkArrayType(arrayType);
		arrayType = arrayType->elementType;
		eat(SB_RSEL);
	}
	// checkBasicType(arrayType);
	return arrayType;
}

//// OLD COMPILE INDEX

// Type* compileIndexes() {
// 	Type* type;

// 	while (lookAhead->tokenType == SB_LSEL) {
// 		eat(SB_LSEL);
// 		type = compileExpression();
// 		eat(SB_RSEL);
// 	}
// 	return type;
// }

int compile(char *fileName) {
	if (openInputStream(fileName) == IO_ERROR){
		return IO_ERROR;
	}

	currentToken = NULL;
	lookAhead = getValidToken();

	initSymTab();						// --- Initialize symtab ---

	compileProgram();

	printf("\n--------------------------------\n\n");
	printObject(symtab->program,0);		// --- Print program to check result ---

	cleanSymTab();						// --- Free symtab ---

	free(currentToken);
	free(lookAhead);
	closeInputStream();
	return IO_SUCCESS;
}


int main() {
	compile("tests\\example6.kpl");
	return 0;
}