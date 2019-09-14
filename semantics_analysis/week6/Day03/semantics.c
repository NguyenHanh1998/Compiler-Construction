/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */
 //bai tap: in file dich, khong lap lai ident da khai bao

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  //TODO
  Object *obj = NULL;
  Scope *currentScope = symtab->currentScope;
  while(currentScope != NULL){
    obj = findObject(currentScope->objList, name);
    if(obj != NULL) return obj;
    currentScope = currentScope->outer;
  }
  obj = findObject(symtab->globalObjectList, name);
  if(obj != NULL) return obj;
  else return NULL;

}

void checkFreshIdent(char *name) {
  // TODO
  Object *obj = NULL;
  //Scope *currentScope = symtab->currentScope;
  obj = lookupObject(name);
  if(obj != NULL)
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
}

Object* checkDeclaredIdent(char* name) { //xem ident duoc khai bao trong pham vi hien tai chua
  // TODO
  Object *objDeclIdent = NULL;
  objDeclIdent = lookupObject(name);
  if(objDeclIdent == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  
  return objDeclIdent;
}

Object* checkDeclaredConstant(char* name) { //xem hang so da khai bao chua
  // TODO
  Object *objDeclConstant = NULL;
  objDeclConstant = lookupObject(name);
  if(objDeclConstant == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  if(objDeclConstant->kind != OBJ_CONSTANT)
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);

  return objDeclConstant;
}

Object* checkDeclaredType(char* name) { //kiem tra kieu da duoc khai bao chua
  // TODO
  Object *objDeclType = NULL;
  objDeclType = lookupObject(name);

  if(objDeclType == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  if(objDeclType->kind != OBJ_TYPE)
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);

  return objDeclType;
}

Object* checkDeclaredVariable(char* name) { //ve trai neu là tên 1 hàm thì phải là trong phạm vi hiện tại (chưa xét đến)
  // TODO
  Object *objDeclVar = NULL;
  objDeclVar = lookupObject(name);

  if(objDeclVar == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  if(objDeclVar->kind != OBJ_VARIABLE)
    error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
    
  return objDeclVar;

}

Object* checkDeclaredFunction(char* name) {
  // TODO
  Object *objDeclFunc = NULL;
  objDeclFunc = lookupObject(name);

  if(objDeclFunc == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  if(objDeclFunc->kind != OBJ_FUNCTION)
    error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
    
  return objDeclFunc;
}

Object* checkDeclaredProcedure(char* name) {
  // TODO
  Object *objDeclProc = NULL;
  objDeclProc = lookupObject(name);

  if(objDeclProc == NULL)
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  if(objDeclProc->kind != OBJ_PROCEDURE)
    error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);
  
  return objDeclProc;
}

Object* checkDeclaredLValueIdent(char* name) {
  // TODO
  Object *objDeclVal = NULL;
  objDeclVal = lookupObject(name);
  if(objDeclVal->kind == OBJ_FUNCTION || objDeclVal->kind == OBJ_PARAMETER || objDeclVal->kind == OBJ_VARIABLE) {
    return objDeclVal;
  }else {
    error(ERR_INVALID_LVALUE, currentToken->lineNo, currentToken->colNo);
  }

  return objDeclVal;
}

