#ifndef __FILE_H__
#define __FILE_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../linkedlist/handleWord.h"

FILE *openFile(char *fileName, char *type);
HandleWords *readFile(char *fileName);
HandleWords *readFileWithState(char *fileName);
void writeFile(HandleWords *handleWords, char* fileName);
char getFile(FILE **file, char *str);
char getFileWithState(FILE **file, char *str, int *upperCase, _Bool *afterEndPoint, _Bool *afterEndLine);

#endif
