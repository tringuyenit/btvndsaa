#ifndef __DEBUG_H__
#define __DEBUG_H_

#include "symtab.h"
#include <string.h>

void printType(Type* type);
void printConstantValue(ConstantValue* value);
void printObject(Object* obj, int indent, int max);
void printObjectList(ObjectNode* objList, int indent, int max);
void printScope(Scope* scope, int indent, int max);

int scanScope(Scope* scope, int indent);
int scanObjectList(ObjectNode* objList, int indent);
int scanObject(Object* obj, int indent);


#endif
