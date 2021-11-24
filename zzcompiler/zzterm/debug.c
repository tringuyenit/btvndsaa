#include <stdio.h>
#include "debug.h"

void pad(int n) {
	int i;
	for (i = 0; i < n ; i++){
		printf(" ");
	}
}

void printType(Type* type) {
	switch (type->typeClass) {
		case TP_INT:{
			printf("Int");
			break;
		}
		case TP_CHAR:{
			printf("Char");
			break;
		}
		case TP_FLOAT:{
			printf("Float");
			break;
		}
		case TP_STRING:{
			printf("String");
			break;
		}
		case TP_ARRAY:{
			printf("Arr(%d,",type->arraySize);
			printType(type->elementType);
			printf(")");
			break;
		}
	}
}

void printConstantValue(ConstantValue* value) {
	switch (value->type) {
		case TP_INT:
			printf("%d",value->intValue);
			break;
		case TP_FLOAT:
			printf("%lf",value->floatValue);
			break;
		case TP_CHAR:
			printf("\'%c\'",value->charValue);
			break;
		case TP_STRING:
			printf("\"%s\"",value->stringValue);
		default:{
			break;
		}
	}
}


int check = 0;
void printObject(Object* obj, int indent, int max) {

	int left;
	int max2;

	switch (obj->kind) {
		case OBJ_CONSTANT:{
			pad(indent);
			printf("Const %s", obj->name);

			left = max - strlen(obj->name);
			for(int i=0; i<=left; i++){
				printf(" ");
			}
			printf("= ");

			printConstantValue(obj->constAttrs->value);
			break;
		}
		case OBJ_TYPE:{
			pad(indent);
			printf("Type  %s", obj->name);

			left = max - strlen(obj->name);
			for(int i=0; i<=left; i++){
				printf(" ");
			}
			printf("= ");

			printType(obj->typeAttrs->actualType);
			break;
		}
		case OBJ_VARIABLE:{
			pad(indent);
			printf("Var   %s", obj->name);

			left = max - strlen(obj->name);
			for(int i=0; i<=left; i++){
				printf(" ");
			}
			printf(": ");

			printType(obj->varAttrs->type);
			break;
		}
		case OBJ_PARAMETER:{
			pad(indent);
			printf("Param %s", obj->name);

			left = max - strlen(obj->name);
			for(int i=0; i<=left; i++){
				printf(" ");
			}
			printf(": ");

			printType(obj->paramAttrs->type);
			if (obj->paramAttrs->kind == PARAM_VALUE) {
	
			}else{
				printf(" [VAR]");
			}

			break;
		}
		case OBJ_FUNCTION:{

			if (check == 0){
				printf("\n");
				check = 1;
			}

			pad(indent);
			printf("Function %s : ",obj->name);
			printType(obj->funcAttrs->returnType);
			printf("\n");

			max2 = scanScope(obj->funcAttrs->scope, indent + 4);
			printScope(obj->funcAttrs->scope, indent + 4, max2);
			break;
		}
		case OBJ_PROCEDURE:{
			if (check == 0){
				printf("\n");
				check = 1;
			}

			pad(indent);
			printf("Procedure %s\n",obj->name);

			max2 = scanScope(obj->procAttrs->scope, indent + 4);
			printScope(obj->procAttrs->scope, indent + 4, max2);
			break;
		}
		case OBJ_PROGRAM:{
			pad(indent);
			printf("Program %s\n\n",obj->name);	

			max2 = scanScope(obj->progAttrs->scope, indent + 4);	
			printScope(obj->progAttrs->scope, indent + 4, max2);
			break;
		}
	}
}

void printObjectList(ObjectNode* objList, int indent, int max) {
	ObjectNode *node = objList;
	
	while (node != NULL) {
		printObject(node->object, indent, max);
		printf("\n");
		node = node->next;
	}
}

void printScope(Scope* scope, int indent, int max) {
	printObjectList(scope->objList, indent, max);
}



int scanScope(Scope* scope, int indent) {
	return scanObjectList(scope->objList, indent);
}

int scanObjectList(ObjectNode* objList, int indent) {
	ObjectNode *node = objList;
	
	int len = 0;
	int tmp;
	while (node != NULL) {
		tmp = scanObject(node->object, indent);
		if (tmp > len){
			len = tmp;
		}
		node = node->next;
	}
	return len;
}

int scanObject(Object* obj, int indent) {

	int len = 0;

	switch (obj->kind) {
		case OBJ_CONSTANT:{
			len = strlen(obj->name);
			break;
		}
		case OBJ_TYPE:{
			len = strlen(obj->name);
			break;
		}
		case OBJ_VARIABLE:{
			len = strlen(obj->name);
			break;
		}
		case OBJ_PARAMETER:{
			len = strlen(obj->name);
			break;
		}
		case OBJ_FUNCTION:{
			len = strlen(obj->name);
			scanScope(obj->funcAttrs->scope, indent + 4);
			break;
		}
		case OBJ_PROCEDURE:{
			len = strlen(obj->name);
			scanScope(obj->procAttrs->scope, indent + 4);
			break;
		}
		case OBJ_PROGRAM:{
			len = strlen(obj->name);
			scanScope(obj->progAttrs->scope, indent + 4);
			break;
		}
	}

	return len;
}


