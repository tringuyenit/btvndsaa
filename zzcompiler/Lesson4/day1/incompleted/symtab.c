/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

void freeObject(Object* obj);
void freeScope(Scope* scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab* symtab;
Type* intType;
Type* charType;
Type* floatType;
/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type* makeFloatType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_FLOAT;
  return type;
}

Type* makeCharType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type* makeArrayType(int arraySize, Type* elementType) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type* duplicateType(Type* type) {
  // TODO_FIN
  Type* newType=(Type*) malloc(sizeof(type));
  newType->typeClass=type->typeClass;
  newType->arraySize=type->arraySize;
  newType->elementType=type->elementType;
  return newType;
}

int compareType(Type* type1, Type* type2) {
  // TODO_FIN
  if (type1->typeClass==type2->typeClass)
  {
    if (type1->typeClass==TP_ARRAY)
    {
      if (!(type1->arraySize==type2->arraySize&&compareType(type1->elementType,type2->elementType)))
      {
          return 0;
      }
         
    }
    return 1;
  }
  return 0;
}

void freeType(Type* type) {
  // TODO_FIN
  if (type->elementType!=NULL)
  {
    freeType(type->elementType);
  }
  free(type);
  type=NULL;
  
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  // TODO_FIN
  ConstantValue* constVal=(ConstantValue*)malloc(sizeof(ConstantValue));
  constVal->type=TP_INT;
  constVal->intValue=i;
  return constVal;
}

ConstantValue* makeFLoatConstant(float i) {
  // TODO_FIN
  ConstantValue* constVal=(ConstantValue*)malloc(sizeof(ConstantValue));
  constVal->type=TP_FLOAT;
  constVal->floatValue=i;
  return constVal;
}

ConstantValue* makeCharConstant(char ch) {
  // TODO_FIN
  ConstantValue* constVal=(ConstantValue*)malloc(sizeof(ConstantValue));
  constVal->type=TP_CHAR;
  constVal->charValue=ch;
  return constVal;

}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  // TODO_FIN
  ConstantValue* constVal=(ConstantValue*)malloc(sizeof(ConstantValue));
  constVal->type=v->type;
  if (v->type==TP_INT)
  {
    constVal->intValue=v->intValue;
  }
  else if (v->type==TP_CHAR)
  {
    constVal->charValue=v->charValue;
  }
  return constVal;
}

/******************* Object utilities ******************************/

Scope* createScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* createProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* createConstantObject(char *name) {
  // TODO_FIN
  Object* constObj=(Object *)malloc(sizeof(Object));
  strcpy(constObj->name,name);
  constObj->kind=OBJ_CONSTANT;
  constObj->constAttrs=(ConstantAttributes*) malloc(sizeof(ConstantAttributes));
  constObj->constAttrs->value=NULL;
  return constObj;
}

Object* createTypeObject(char *name) {
  // TODO_FIN
  Object* typeObj=(Object*)malloc(sizeof(Object));
  strcpy(typeObj->name,name);
  typeObj->kind=OBJ_TYPE;
  typeObj->typeAttrs=(TypeAttributes*)malloc(sizeof(TypeAttributes));
  typeObj->typeAttrs->actualType=NULL;

  return typeObj;

}

Object* createVariableObject(char *name) {
  // TODO_FIN
  Object* varObj=(Object*) malloc(sizeof(Object));
  strcpy(varObj->name,name);
  varObj->kind=OBJ_VARIABLE;
  varObj->varAttrs=(VariableAttributes*) malloc(sizeof(VariableAttributes));
  varObj->varAttrs->type=NULL;
  varObj->varAttrs->scope=symtab->currentScope;
  
  return varObj;
}

Object* createFunctionObject(char *name) {
  // TODO_FIN
  Object* functionObj=(Object*) malloc(sizeof(Object));
  strcpy(functionObj->name,name);
  functionObj->kind=OBJ_FUNCTION;

  functionObj->funcAttrs=(FunctionAttributes*) malloc(sizeof(FunctionAttributes));
  functionObj->funcAttrs->paramList=NULL;
  functionObj->funcAttrs->returnType=NULL;
  functionObj->funcAttrs->scope=createScope(functionObj,symtab->currentScope);

  return functionObj;
}

Object* createProcedureObject(char *name) {
  // TODO_FIN
  Object* procedureObj=(Object*) malloc(sizeof(Object));
  strcpy(procedureObj->name,name);
  procedureObj->kind=OBJ_PROCEDURE;

  procedureObj->procAttrs=(ProcedureAttributes*) malloc(sizeof(ProcedureAttributes));
  procedureObj->procAttrs->paramList=NULL;
  procedureObj->procAttrs->scope=createScope(procedureObj,symtab->currentScope);

  return procedureObj;
}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  // TODO_FIN
  Object* parameterObj=(Object*) malloc(sizeof(Object));
  strcpy(parameterObj->name,name);

  parameterObj->kind=OBJ_PARAMETER;

  parameterObj->paramAttrs=(ParameterAttributes*)malloc(sizeof(ParameterAttributes));
  parameterObj->procAttrs->paramList=NULL;
  parameterObj->procAttrs->scope=createScope(parameterObj,symtab->currentScope);

  return parameterObj;
}

void freeObject(Object* obj) {
  // TODO_FIN_LONG_AF
  if (obj!=NULL)
  {
    if (obj->constAttrs!=NULL)
    {
      switch (obj->kind)
      {
      case OBJ_CONSTANT:
        if (obj->constAttrs->value!=NULL)
        {
          free(obj->constAttrs->value);
          obj->constAttrs->value=NULL;
        }
        break;
      case OBJ_VARIABLE:
        if (obj->varAttrs->type!=NULL)
        {
          free(obj->varAttrs->type);
          obj->varAttrs->type=NULL;
        }
        break;
      case OBJ_TYPE:
        if (obj->typeAttrs->actualType!=NULL)
        {
          free(obj->typeAttrs->actualType);
          obj->typeAttrs->actualType=NULL;
        }
        break;
      case OBJ_PROGRAM:
        if (obj->progAttrs->scope!=NULL)
        {
          freeScope(obj->progAttrs->scope);
          obj->progAttrs->scope=NULL;
        }
        break;
      case OBJ_FUNCTION:
        if (obj->funcAttrs->scope!=NULL)
        {
          freeScope(obj->funcAttrs->scope);
          obj->funcAttrs->scope=NULL;
        }
        break;
      case OBJ_PROCEDURE:
        if (obj->procAttrs->scope!=NULL)
        {
          freeScope(obj->procAttrs->scope);
          obj->procAttrs->scope=NULL;
        }
        break;
      case OBJ_PARAMETER:
        if (obj->paramAttrs->type != NULL) 
        {
          free(obj->paramAttrs->type);
          obj->paramAttrs->type = NULL;
        }
        break;
      default:
        printf("TYPE NOT_FOUND");
        break;
      }
    }
    free(obj);
    obj=NULL;
  }
  
}

void freeScope(Scope* scope) {
  // TODO_FIN
  if (scope!=NULL)
  {
    freeObjectList(scope->objList);
    free(scope);
    scope=NULL;
  }
  
}

void freeObjectList(ObjectNode *objList) {
  // TODO_FIN
  if (objList!=NULL)
  {
    freeObject(objList->object);
    freeObjectList(objList->next);
    objList=NULL;
  }
  
}

void freeReferenceList(ObjectNode *objList) {
  // TODO_FIN
  if (objList!=NULL)
  {
    freeObject(objList->object);
    freeReferenceList(objList->next);
    objList=NULL;
  }
  
}

void addObject(ObjectNode **objList, Object* obj) {
  ObjectNode* node = (ObjectNode*) malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL) 
    *objList = node;
  else {
    ObjectNode *n = *objList;
    while (n->next != NULL) 
      n = n->next;
    n->next = node;
  }
}

Object* findObject(ObjectNode *objList, char *name) {
  // TODO_FIN
  ObjectNode* curNode=objList;
  while (curNode!=NULL)
  {
    if (strcmp(curNode->object->name,name)==0)
    {
      return curNode->object;
    }
    curNode=curNode->next;
  }
  return NULL;

}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  
  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);


  obj = createFunctionObject("READF");
  obj->funcAttrs->returnType = makeFloatType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEF");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeFloatType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList),param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
  floatType=makeFloatType();
}

void cleanSymTab(void) {
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope* scope) {
  symtab->currentScope = scope;
}

void exitBlock(void) {
  symtab->currentScope = symtab->currentScope->outer;
}

void declareObject(Object* obj) {
  if (obj->kind == OBJ_PARAMETER) {
    Object* owner = symtab->currentScope->owner;
    switch (owner->kind) {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }
 
  addObject(&(symtab->currentScope->objList), obj);
}


