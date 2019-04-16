#include "file.h"

#define END_WORD 1
#define END_LINE 2
#define NOT_Y_END_WORD 0

FILE *openFile(char *fileName, char *type)
{
  FILE *f = fopen(fileName, type);
  if (!f)
  {
    printf("Can't open file %s \n", fileName);
    exit(1);
  }
  return f;
}

HandleWords *readFile(char *fileName)
{
  FILE *file = openFile(fileName, "r");
  HandleWords *handleWords = 0, *temp;
  int key = 0, line = 1;
  _Bool uppercase = 0, existLine = 0;
  char str[WORDS] = "", check;

  while (1)
  {
    check = getFile(&file, str);
    if (check == NOT_Y_END_WORD)
      continue;
    else
    {
      if (strcmp(str, ""))
      {
        if (temp == existWord(handleWords, str))
        {
          temp->countWords++;
          existLine = 0;
          for (int i = 0; i < temp->countLines; i++)
          {
            if (temp->line[i] == line)
              existLine = 1;
          }
          if (!existLine)
            temp->line[(temp->countLines)++] = line;
        }
        else
          insertNodeWord(&handleWords, createNodeWord(key++, str, line, LOWERCASE));

        strcpy(str, "");
      }
      if (check == END_LINE)
        line++;
      if (check == EOF)
        break;
    }
  }

  fclose(file);
  return handleWords;
}

HandleWords *readFileWithState(char *fileName)
{
  FILE *file = openFile(fileName, "r");
  HandleWords *handleWords = 0, *temp;
  int key = 0, line = 1;
  _Bool uppercase = 0, existLine = 0, afterEndPoint = 0, afterEndLine = 1;
  char str[WORDS] = "", check;

  while (1)
  {
    check = getFileWithState(&file, str, &uppercase, &afterEndPoint, &afterEndLine);
    if (check == NOT_Y_END_WORD)
      continue;
    else
    {
      if (strcmp(str, ""))
      {
        if (temp == existWordWithState(handleWords, str, uppercase))
        {
          temp->countWords++;
          existLine = 0;
          for (int i = 0; i < temp->countLines; i++)
          {
            if (temp->line[i] == line)
              existLine = 1;
          }
          if (!existLine)
            temp->line[(temp->countLines)++] = line;
        }
        else
        {
          insertNodeWord(&handleWords, createNodeWord(key++, str, line, uppercase));
        }
        strcpy(str, "");
        uppercase = 0;
      }
      if (check == END_LINE)
        line++;
      if (check == EOF)
        break;
    }
  }

  fclose(file);
  return handleWords;
}

char getFile(FILE **file, char *str)
{
  char c = fgetc(*file);
  if (c == '\n')
    return END_LINE;
  if (!isalpha(c))
    return END_WORD;
  if (c == EOF)
    return EOF;

  char *cstr = strchr(str, '\0');
  *cstr = tolower(c);
  *(cstr + 1) = '\0';
  return NOT_Y_END_WORD;
}

char getFileWithState(FILE **file, char *str, int *uppercase, _Bool *afterEndPoint, _Bool *afterEndLine)
{
  char c = fgetc(*file);
  if (c == '\n')
  {
    *afterEndLine = 1;
    return END_LINE;
  }
  if (c == EOF)
    return EOF;
  if (c == '.')
    *afterEndPoint = 1;
  if (!isalpha(c))
    return END_WORD;

  char *cstr = strchr(str, '\0');
  if (!(cstr - str) && c == toupper(c) && *afterEndPoint == 0 && *afterEndLine == 0)
  {
    *uppercase = UPPERCASE;
  }

  *afterEndPoint = 0;
  *afterEndLine = 0;
  *cstr = tolower(c);
  *(cstr + 1) = '\0';
  return NOT_Y_END_WORD;
}

void writeFile(HandleWords *handleWords, char *fileName)
{
  FILE *file = openFile(fileName, "a+");
  rewind(file);
  char c = fgetc(file);
  if (c != EOF)
  {
    HandleWords *beforeLW = readFile(fileName);
  }
}