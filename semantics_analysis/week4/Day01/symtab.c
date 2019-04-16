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

/******************* Type utilities ******************************/

Type* makeIntType(void) {
  Type* type = (Type*) malloc(sizeof(Type));
  type->typeClass = TP_INT;
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
  // TODO
  Type *dupType = (Type*) malloc(sizeof(Type));
  dupType->typeClass = type->typeClass;
  dupType->arraySize = type->arraySize;
  dupType->elementType = type->elementType;
  return dupType;
} 

int compareType(Type* type1, Type* type2) {
  // TODO
  if(type1->typeClass != type2->typeClass) {
    return 0;
  }else {
    if(type1->arraySize != type2->arraySize){
      return 0;
    }else {
      if(type1->arraySize != 0 && type1->elementType->typeClass != type2->elementType->typeClass) {
        return 0;
      }
    }
  }
  return 1;
}

void freeType(Type* type) {
  // TODO
  if(type->elementType != NULL) {
    freeType(type->elementType);
  }
  free(type);
}

/******************* Constant utility ******************************/

ConstantValue* makeIntConstant(int i) {
  // TODO
  ConstantValue *constValue = (ConstantValue*) malloc(sizeof(ConstantValue));
  constValue->type = TP_INT;
  constValue->intValue = i;
  return constValue;

}

ConstantValue* makeCharConstant(char ch) {
  // TODO
  ConstantValue *constValue = (ConstantValue*) malloc(sizeof(ConstantValue));
  constValue->type = TP_CHAR;
  constValue->charValue = ch;
  return constValue;
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  // TODO
  ConstantValue *dupConstValue = (ConstantValue*) malloc(sizeof(ConstantValue));
  dupConstValue->type = v->type;
  if(v->type == TP_INT){
    dupConstValue->intValue = v->intValue;
  }
  else {
    dupConstValue->charValue = v->charValue;
  }
  return dupConstValue;
}

/******************* Object utilities ******************************/

Scope* CreateScope(Object* owner, Scope* outer) {
  Scope* scope = (Scope*) malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object* CreateProgramObject(char *programName) {
  Object* program = (Object*) malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes*) malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = CreateScope(program,NULL);
  symtab->program = program;

  return program;
}

Object* CreateConstantObject(char *name) {
  // TODO
  Object* constObject = (Object*)malloc(sizeof(Object));
  strcpy(constObject->name,name);
  constObject->kind = OBJ_CONSTANT;
  constObject->constAttrs = (ConstantAttributes*) malloc(sizeof(ConstantAttributes));
  constObject->constAttrs->value = NULL;
  return constObject; 
}

Object* CreateTypeObject(char *name) {
  // TODO
  Object* typeObject = (Object*) malloc(sizeof(Object));
  strcpy(typeObject->name, name);
  typeObject->kind = OBJ_TYPE;
  typeObject->typeAttrs = (TypeAttributes*) malloc(sizeof(TypeAttributes));
  typeObject->typeAttrs->actualType = NULL;
  return typeObject;
}

Object* CreateVariableObject(char *name) {
  // TODO
  Object* variableObject = (Object*) malloc(sizeof(Object));
  strcpy(variableObject->name, name);
  variableObject->kind = OBJ_VARIABLE;
  variableObject->varAttrs = (VariableAttributes*) malloc(sizeof(VariableAttributes));
  variableObject->varAttrs->type = NULL;
  variableObject->varAttrs->scope = CreateScope(variableObject, symtab->currentScope);
  return variableObject;
}

Object* CreateFunctionObject(char *name) {
  // TODO
  Object* functionObject = (Object*)malloc(sizeof(Object));
  strcpy(functionObject->name, name);
  functionObject->kind = OBJ_FUNCTION;
  functionObject->funcAttrs = (FunctionAttributes*)malloc(sizeof(FunctionAttributes));
  functionObject->funcAttrs->returnType = NULL;
  functionObject->funcAttrs->paramList = NULL;
  functionObject->funcAttrs->scope = CreateScope(functionObject, symtab->currentScope);
  return functionObject;
}

Object* CreateProcedureObject(char *name) {
  // TODO
  Object* procedureOject = (Object*)malloc(sizeof(Object));
  strcpy(procedureOject->name, name);
  procedureOject->kind = OBJ_PROCEDURE;
  procedureOject->procAttrs = (ProcedureAttributes*)malloc(sizeof(ProcedureAttributes));
  procedureOject->procAttrs->paramList = NULL;
  procedureOject->procAttrs->scope = CreateScope(procedureOject, symtab->currentScope);
  return procedureOject;
}

Object* CreateParameterObject(char *name, enum ParamKind kind, Object* owner) {
  // TODO
  Object* paramObject = (Object*)malloc(sizeof(Object));
  strcpy(paramObject->name, name);
  paramObject->kind = OBJ_PARAMETER;
  paramObject->paramAttrs = (ParameterAttributes*)malloc(sizeof(ParameterAttributes));
  paramObject->paramAttrs->kind = kind;
  paramObject->paramAttrs->type = NULL;
  paramObject->paramAttrs->function = owner;
  return paramObject;
}

void freeObject(Object* obj) {
  // TODO
  if(obj !=  NULL) {
    switch(obj->kind) {
      case OBJ_CONSTANT:
        if(obj->constAttrs->value != NULL) {
          free(obj->constAttrs->value);
          obj->constAttrs->value = NULL;
        }
        free(obj->constAttrs);
        obj->constAttrs = NULL;
        break;
      case OBJ_VARIABLE:
        if(obj->varAttrs->type != NULL) {
          free(obj->varAttrs->type);
          obj->varAttrs->type = NULL;
        }
        // freeScope(obj->varAttrs->scope);
        // free(obj->varAttrs);
        break;
      case OBJ_TYPE:
        if(obj->typeAttrs->actualType != NULL) {
          free(obj->typeAttrs->actualType);
          obj->typeAttrs->actualType = NULL;
        }
        free(obj->typeAttrs);
        break;
      case OBJ_FUNCTION:
        if(obj->funcAttrs->paramList != NULL) {
        free(obj->funcAttrs->paramList);
        }
        if(obj->funcAttrs->returnType != NULL) {
        free(obj->funcAttrs->returnType);
        }
        if(obj->funcAttrs->scope != NULL) {
        freeScope(obj->funcAttrs->scope);
        }
        free(obj->funcAttrs);
        break;
      case OBJ_PROCEDURE:
        if(obj->procAttrs->paramList != NULL) {
        free(obj->procAttrs->paramList);
        }
        if(obj->procAttrs->scope != NULL) {
        freeScope(obj->procAttrs->scope);
        }
        free(obj->procAttrs);
        break;
      case OBJ_PARAMETER:
        if(obj->paramAttrs->type != NULL) {
        free(obj->paramAttrs->type);
        }
        if(obj->paramAttrs->function != NULL) {
        free(obj->paramAttrs->function);
        }
        free(obj->paramAttrs);
        break;
      case OBJ_PROGRAM:
        if(obj->procAttrs->scope != NULL) {
        freeScope(obj->progAttrs->scope);
        }
        free(obj->progAttrs);
        break;
    }
    free(obj);
  }
}

void freeScope(Scope* scope) {
  // TODO
  if(scope != NULL){
    freeObjectList(scope->objList);
    freeObject(scope->owner);
    freeScope(scope->outer);
  }
}

void freeObjectList(ObjectNode *objList) {
  // TODO
  if(objList != NULL){
    while(objList->next != NULL) {
      ObjectNode *temp = objList;
      objList =  temp->next;
      free(temp);
    }
  }
}

void freeReferenceList(ObjectNode *objList) {
  // TODO
  if(objList != NULL){
    while(objList->next != NULL) {
      ObjectNode *temp = objList;
      objList=  temp->next;
      free(temp);
    }
  }
}

void AddObject(ObjectNode **objList, Object* obj) {
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
  // TODO
  ObjectNode *temp;
  for(temp = objList; temp != NULL; temp = temp->next){
    if(strcmp(temp->object->name, name) == 0) {
      return temp->object;
    }
  }
  return NULL;
}

/******************* others ******************************/

void initSymTab(void) {
  Object* obj;
  Object* param;

  symtab = (SymTab*) malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;
  
  obj = CreateFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  AddObject(&(symtab->globalObjectList), obj);

  obj = CreateFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  AddObject(&(symtab->globalObjectList), obj);

  obj = CreateProcedureObject("WRITEI");
  param = CreateParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  AddObject(&(obj->procAttrs->paramList),param);
  AddObject(&(symtab->globalObjectList), obj);

  obj = CreateProcedureObject("WRITEC");
  param = CreateParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  AddObject(&(obj->procAttrs->paramList),param);
  AddObject(&(symtab->globalObjectList), obj);

  obj = CreateProcedureObject("WRITELN");
  AddObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
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
      AddObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      AddObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }
 
  AddObject(&(symtab->currentScope->objList), obj);
}


