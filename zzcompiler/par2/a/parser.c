#include <stdlib.h>

#include "debug.c"
// #include "semantics.c"
#include "symtab.c"
#include "scanner.c"
#include "parser.h"

Token *currentToken;
Token *lookAhead;
int enable = 1; // tu them

// extern Type* intType;
// extern Type* floatType;
// extern Type* charType;
// extern Type* stringType;
// extern SymTab* symtab;

void scan(void) {
	Token* tmp = currentToken;
	currentToken = lookAhead;
	//-------------------------
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

void compileProgram(void) {
	if (enable){
		assert("Parsing a Program ....");
	}
	
	Object* program; //xx
  	
	eat(KW_PROGRAM);
	eat(TK_IDENT);
	program = createProgramObject(currentToken->string);
	
	enterBlock(program->progAttrs->scope); //xx 

	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_PERIOD);
	exitBlock(); //xx
	printf("DONE!");

	if (enable){
		assert("Program parsed!");
	}
}

void compileBlock(void) {
	if (enable){
		assert("Parsing a Block ....");
	}
	if (lookAhead->tokenType == KW_CONST) {
		eat(KW_CONST);
		compileConstDecl();
		compileConstDecls();
		compileBlock2();
	} 
	else compileBlock2();

	if (enable){
		assert("Block parsed!");
	}
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

void compileConstDecls(void) {
	if (lookAhead->tokenType == TK_IDENT){
		compileConstDecl();
		compileConstDecls();
	} else {
		// error(ERR_INVALIDCONSTDECL, lookAhead->lineNo, lookAhead->colNo);
	}
}

void compileConstDecl(void) {
	Object* constObj;//xx
	ConstantValue* constValue;//xx

	eat(TK_IDENT);

	constObj = createConstantObject(currentToken->string);//xx

	eat(SB_EQ);

	constValue = compileConstant();				// --- Get constant value ---
	constObj->constAttrs->value = constValue;	// --- Assign value to constant ---
	declareObject(constObj); //xx

	eat(SB_SEMICOLON);
}

void compileTypeDecls(void) {
	if (lookAhead->tokenType == TK_IDENT){
		compileTypeDecl();
		compileTypeDecls();
	} else {
		// error(ERR_INVALIDTYPEDECL, lookAhead->lineNo, lookAhead->colNo);
	}
}

void compileTypeDecl(void) {
	Object* typeObj;//xx
	Type* actualType;//xx

	eat(TK_IDENT);

	typeObj = createTypeObject(currentToken->string);//xx

	eat(SB_EQ);

	actualType = compileType();			// --- Get actual type ---
	typeObj->typeAttrs->actualType = actualType;
	declareObject(typeObj);

	eat(SB_SEMICOLON);
}

void compileVarDecls(void) {
	if (lookAhead->tokenType == TK_IDENT){
		compileVarDecl();
		compileVarDecls();
	} else {
		// error(ERR_INVALIDVARDECL, lookAhead->lineNo, lookAhead->colNo);
	}
}

void compileVarDecl(void) {
	Object* varObj;//xx
	Type* varType;//xx

	eat(TK_IDENT);

	varObj = createVariableObject(currentToken->string);//xx

	eat(SB_COLON);

	varType = compileType();			// --- Assign type to variable ---
	varObj->varAttrs->type = varType;
	declareObject(varObj);//xx

	eat(SB_SEMICOLON);
}

void compileSubDecls(void) {
	if (enable){
		assert("Parsing subtoutines ....");
	}

	switch (lookAhead->tokenType){
		case KW_FUNCTION:
			compileFuncDecl();
			compileSubDecls();
			break;
		case KW_PROCEDURE:
			compileProcDecl();
			compileSubDecls();
			break;
		default:
			// ko can error
			// error(ERR_INVALIDSUBDECL, lookAhead->lineNo, lookAhead->colNo);
			break;
	}

	if (enable){
		assert("Subtoutines parsed ....");
	}
}

void compileFuncDecl(void) {
	if (enable){
		assert("Parsing a function ....");
	}
  	
	Object* funcObj;//xx
	Type* returnType;//xx

	eat(KW_FUNCTION);
	eat(TK_IDENT);

	funcObj = createFunctionObject(currentToken->string); //xx
	declareObject(funcObj);					// --- Declare funcObj into current block ---
	enterBlock(funcObj->funcAttrs->scope);	// --- Move to funcBlock to traversed localObj ---

	compileParams();
	eat(SB_COLON);

	returnType = compileBasicType();		// --- Return type of func ---
	funcObj->funcAttrs->returnType = returnType;//xx

	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_SEMICOLON);

	exitBlock();//xx

	if (enable){
		assert("Function parsed ....");
	}
}

void compileProcDecl(void) {
	if (enable){
  		assert("Parsing a procedure ....");
	}

	Object* procObj;

	eat(KW_PROCEDURE);
	eat(TK_IDENT);

	procObj = createProcedureObject(currentToken->string); //xx
	declareObject(procObj);	//xx						// --- Declare procedureObj into current block ---
	enterBlock(procObj->procAttrs->scope); //xx

	compileParams();
	eat(SB_SEMICOLON);
	compileBlock();
	eat(SB_SEMICOLON);
	exitBlock(); //xx

	if (enable){
  		assert("Procedure parsed ....");
	}
}

void compileParams(void) {
	if (lookAhead->tokenType == SB_LPAR){
		eat(SB_LPAR);
		compileParam();
		compileParams2();
		eat(SB_RPAR);
	}
}

void compileParams2(void) {
	if (lookAhead->tokenType == SB_SEMICOLON){
		eat(SB_SEMICOLON);
		compileParam();
		compileParams2();
	} // ko can error
}

void compileParam(void) {
	Object* param;//xx
	Type* type;//xx

	switch (lookAhead->tokenType){
		case TK_IDENT:
			eat(TK_IDENT);

			param = createParameterObject(currentToken->string, PARAM_VALUE, symtab->currentScope->owner);//xx

			eat(SB_COLON);
			
			switch (lookAhead->tokenType){//tu lam -- khac
				case KW_FLOAT:
				case KW_INTEGER:
				case KW_CHAR:
				case KW_STRING:
					type = compileBasicType();//xx
					param->paramAttrs->type = type;//xx
					declareObject(param);//xx
					break;
				default:
					error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
					break;
			}

			break;
		case KW_VAR:
			eat(KW_VAR);
			eat(TK_IDENT);

			param = createParameterObject(currentToken->string, PARAM_REFERENCE, symtab->currentScope->owner);//xx

			eat(SB_COLON);

			switch (lookAhead->tokenType){//tu lam -- khac
				case KW_FLOAT:
				case KW_INTEGER:
				case KW_CHAR:
				case KW_STRING:
					type = compileBasicType();//xx
					param->paramAttrs->type = type;//xx
					declareObject(param);//xx
					break;
				default:
					error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
					break;
			}
			
			break;
		default:
			error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
			break;
	}
}

Type* compileType(void) {

	Type* type;
	Type* elementType;
	int arraySize;
	Object* obj;

	switch (lookAhead->tokenType){
		case KW_INTEGER: 
			eat(KW_INTEGER);
			type =	makeIntType();//xx
			break;
		case KW_CHAR:
			eat(KW_CHAR);
			type = makeCharType();//xx
			break;
		case TK_IDENT:
			eat(TK_IDENT);
			type = duplicateType(obj->typeAttrs->actualType);//xx
			break;

		case KW_STRING:
			eat(KW_STRING);
			type = makeStringType();//xx
			break;
		case KW_FLOAT:
			eat(KW_FLOAT);
			type = makeFloatType();//xx
			break;

		case KW_ARRAY:
			eat(KW_ARRAY);
			eat(SB_LSEL);
			
			switch (lookAhead->tokenType){ // tu them
				case TK_NUMBER:
					eat(TK_NUMBER);
					arraySize = currentToken->value; //xx
					break;
				case TK_FLOAT:
					eat(TK_FLOAT);
					arraySize = currentToken->value;//xx
					break;
				default:
					error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
					break;
			}//

			eat(SB_RSEL);
			eat(KW_OF);
			elementType = compileType(); //xx
			type = makeArrayType(arraySize, elementType);//xx
			break;
		default:
			error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
			break;
	}

	return type;//xx
}

Type* compileBasicType(void) {
	Type* type;//xx

	switch (lookAhead->tokenType){

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

		default:
			error(ERR_INVALIDBASICTYPE, lookAhead->lineNo, lookAhead->colNo);
			break;
	}

	return type;//xx
}

ConstantValue* compileUnsignedConstant(void) {
	ConstantValue* constValue;
	Object* obj;

	switch (lookAhead->tokenType){
		case TK_NUMBER:
			eat(TK_NUMBER);
			constValue = makeIntConstant(currentToken->value); //xx
			break;
		case TK_FLOAT:
			eat(TK_FLOAT);
			constValue = makeFloatConstant(currentToken->fValue);//xx
			break;
		case TK_IDENT:
			eat(TK_IDENT);
			constValue = duplicateConstantValue(obj->constAttrs->value); //xx
			break;
		case TK_CHAR:
			eat(TK_CHAR);
			constValue = makeCharConstant(currentToken->string[0]);
			break;
		
		case TK_STRING:
			eat(TK_STRING);
			constValue = makeStringConstant(currentToken->stringNode);
			break;

		default:
			// khong biet error nao ?
			// error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
			error(ERR_INVALIDCHARCONSTANT, lookAhead->lineNo, lookAhead->colNo);
			break;
	}

	return constValue; //xx
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
		case TK_IDENT:
			eat(TK_IDENT);

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
		case TK_NUMBER:
			eat(TK_NUMBER);
			constValue = makeIntConstant(currentToken->value); //xx
			break;
		case TK_FLOAT:
			eat(TK_FLOAT);
			constValue = makeFloatConstant(currentToken->value); //xx
			break;
		default:
			error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
			break;
	}

	return constValue;//xx
}

void compileStatements(void) {
	compileStatement();
	compileStatements2();
}

void compileStatements2(void) {
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

		// EmptySt
		case SB_SEMICOLON:  // ???
		case KW_END:
		case KW_UNTIL:
		case KW_ELSE:
			break;


		default: // -- khac
			error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
			break;
		}
}

void compileAssignSt(void) {
	if (enable){
		assert("Parsing an assign statement ....");
	}

	Type **lvalueType = NULL;//xx
	Type *expType = NULL;//xx
	lvalueType = (Type**)malloc(sizeof(Type));//xx
	int counterForVariables = 1;//xx
	lvalueType = (Type**)realloc(lvalueType, counterForVariables*sizeof(Type));//xx
	lvalueType[0] = compileVariable();//xx

	// compileVariable(); // thay bang 2 dong duoi -- y het
	// eat(TK_IDENT);
	// compileIndexes();

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

	if (enable){
		assert("Assign statement parsed ....");
	}
}

void compileCallSt(void) {
	if (enable){
		assert("Parsing a call statement ....");
	}

	Object* proc;//xx

	eat(KW_CALL);
	eat(TK_IDENT);
	compileArguments();

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
	if (lookAhead->tokenType == KW_ELSE) {
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
	eat(SB_ASSIGN);

	type = compileExpression();//xx

	eat(KW_TO);

	type = compileExpression(); //xx

	eat(KW_DO);
	compileStatement();

	if (enable){
		assert("For statement parsed ....");
	}
}

void compileArguments(void) { // !!!!!!!
	Type* type;

	if (lookAhead->tokenType == SB_LPAR){
		eat(SB_LPAR);
		type = compileExpression();
		compileArguments2();
		eat(SB_RPAR);
	} else{
		// error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
		// hinh nhu khong can
	}
}

void compileArguments2(void) {
	Type* type;//xx
	if (lookAhead->tokenType == SB_COMMA){
		eat(SB_COMMA);
		switch (lookAhead->tokenType){ // tu lam
				case TK_FLOAT:
				case TK_NUMBER:
				case TK_CHAR:
				case TK_IDENT:
				case SB_LPAR:
				case SB_PLUS:
				case SB_MINUS:
					type = compileExpression();
					compileArguments2();
					break;
				default:
					error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
					break;
		}
	}
}

void compileCondition(void) {
	Type* type1;//xx
	type1 = compileExpression();//xx
	compileCondition2();
}

void compileCondition2(void) {
	Type* type2;

	switch (lookAhead->tokenType){
		case SB_EQ:
		case SB_NEQ:
		case SB_LE:
		case SB_LT:
		case SB_GE:
		case SB_GT:
			eat(lookAhead->tokenType);
			type2 = compileExpression();
			break;
		default:
			error(ERR_INVALIDCONDITION, lookAhead->lineNo, lookAhead->colNo);
			break;
	}
}

Type* compileExpression(void) {
	if (enable){
		assert("Parsing an expression");
	}

	Type* type;

	switch (lookAhead->tokenType){
		case SB_PLUS:
			eat(SB_PLUS);
			type = compileExpression2();//xx
			break;
		case SB_MINUS:
			eat(SB_MINUS);
			type = compileExpression2();//xx
			break;
		default:
			type = compileExpression2();//xx
			break;
	}

	return type;//xx

	if (enable){
		assert("Expression parsed");
	}
}

Type* compileExpression2(void) {
	Type* type;//xx
	type = compileTerm();//xx
	compileExpression3();
	return type;
}

void compileExpression3(void) {
	Type* type;//xx
	switch (lookAhead->tokenType){
		case SB_PLUS:
			eat(SB_PLUS);
			switch (lookAhead->tokenType){ // tu lam -- khac
				case TK_FLOAT:
				case TK_NUMBER:
				case TK_CHAR:
				case TK_IDENT:
				case SB_LPAR:
					type = compileTerm();//xx
					compileExpression3();
					break;
				default:
					error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
					break;
			}

			break;

		case SB_MINUS:
			eat(SB_MINUS);
			switch (lookAhead->tokenType){ // tu lam
				case TK_FLOAT:
				case TK_NUMBER:
				case TK_CHAR:
				case TK_IDENT:
				case SB_LPAR:
					type = compileTerm();
					compileExpression3();
					break;
				default:
					error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
					break;
			}

			break;
  	}	 
}

Type* compileTerm(void) {
	Type* type;//xx

	type = compileFactor();//xx
	compileTerm2();

	return type;
}

void compileTerm2(void) {
	Type* type;

	switch (lookAhead->tokenType){
		case SB_TIMES:
			eat(SB_TIMES);
			type = compileFactor();
			compileTerm2();
			break;
		case SB_MOD:
			eat(SB_MOD);
			type = compileFactor();
			compileTerm2();
			break;
		case SB_SLASH:
			eat(SB_SLASH);
			type = compileFactor();
			compileTerm2();
			break;


		case SB_PLUS: //???
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

		default:
			error(ERR_INVALIDTERM, lookAhead->lineNo, lookAhead->colNo);
			break;
	}
}

Type* compileFactor(void) {
	Type* type;//xx
	Object* obj;//xx

	switch (lookAhead->tokenType){
		case TK_NUMBER:
			eat(lookAhead->tokenType);
			type = intType;
			break;
		case TK_CHAR:
			eat(lookAhead->tokenType);
			type = charType;
			break;
		case TK_STRING:
			eat(lookAhead->tokenType);
			type = stringType;
			break;
		case TK_FLOAT:
			eat(lookAhead->tokenType);
			type = floatType;
			break;
		case TK_IDENT:
			eat(TK_IDENT);
	
			// da co eat INDENT o trong
			if (lookAhead->tokenType == SB_LPAR){
				// compileFunctionApp(); thay bang dong o duoi
				compileArguments();
			} else {
				type = compileIndexes();
			}

			break;

		case SB_LPAR:
			eat(SB_LPAR);
			type = compileExpression();
			eat(SB_RPAR);
			break;
		default:
			error(ERR_INVALIDFACTOR, lookAhead->lineNo, lookAhead->colNo);
			break;
	}
}

Type* compileVariable(void) {
	Object* var;//xx
	Type* varType;//xx

	eat(TK_IDENT);
	varType = compileIndexes();//xx

	return varType;
}

void compileFunctionApp(void) {
	eat(TK_IDENT);
	compileArguments();
}

Type* compileIndexes(void) {
	Type* type;//xx
	if (lookAhead->tokenType == SB_LSEL){
		eat(SB_LSEL);
		type = compileExpression();
		eat(SB_RSEL);
		compileIndexes();
	}

	return type;
}

int compile(char *fileName) {
	if (openInputStream(fileName) == IO_ERROR)
		return IO_ERROR;

	currentToken = NULL;
	lookAhead = getValidToken();

	compileProgram();

	printObject(symtab->program,0);		// --- Print program to check result ---

	cleanSymTab();//xx

	free(currentToken);
	free(lookAhead);
	closeInputStream();
	return IO_SUCCESS;
}


int main() {
	compile("test\\example1.kpl");
	return 0;
}
