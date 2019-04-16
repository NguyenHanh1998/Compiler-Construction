#ifndef __HANDLEWORD_H__
#define __HANDLEWORD_H__ 0

#include <stdlib.h>
#include <string.h>

#define WORDS 20
#define LINES 30
#define UPPERCASE 1
#define LOWERCASE 0

struct _handleWord
{
    int key;
    char word[WORDS];
    _Bool upperCase;
    int countWords;
    int countLines;
    int line[LINES];
    struct _handleWord *next;
};

typedef struct _handleWord HandleWords;

HandleWords *createNodeWord(int key, char *word, int line, _Bool upperCase);
void insertNodeWord(HandleWords **root, HandleWords *newNodeWord);
void showListWord(HandleWords *root);
_Bool existNodeWord(HandleWords *root, HandleWords *node);
HandleWords *existWord(HandleWords *root, char *word);
HandleWords *existWordWithState(HandleWords *root, char *word, int uppercase);
void sortWord(HandleWords **root);
void dropNodeWord(HandleWords **root, HandleWords *node);
void dropListNode(HandleWords **root);
void swap(HandleWords **root, HandleWords *tmpI, HandleWords **i, HandleWords *tmpJ, HandleWords **j);

#endif
