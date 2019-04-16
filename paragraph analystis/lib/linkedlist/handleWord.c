#include "handleWord.h"

HandleWords *createNodeWord(int key, char *word, int line, _Bool uppercase)
{
    HandleWords *newNodeWord = (HandleWords *)malloc(sizeof(HandleWords));
    newNodeWord->key = key;
    strcpy(newNodeWord->word, word);
    newNodeWord->countLines = 1;
    newNodeWord->countWords = 1;
    newNodeWord->line[0] = line;
    for (int i = 1; i < LINES; i++)
        newNodeWord->line[i] = 0;
    newNodeWord->next = 0;
    return newNodeWord;
}

void insertNodeWord(HandleWords **root, HandleWords *newNodeWord)
{
    if (*root == 0)
    {
        *root = newNodeWord;
        return;
    }

    HandleWords *tempWord = *root;
    for (; tempWord->next != NULL; tempWord = tempWord->next)
        ;
    tempWord->next = newNodeWord;
    newNodeWord->next = NULL;
}

void showListWord(HandleWords *root)
{
    HandleWords *temp = root;
    for (; temp != NULL; temp = temp->next)
    {
        printf("%s %d", temp->word, temp->countWords);
        for (int i = 0; i < temp->countLines; i++)
        {
            printf(" %d", temp->line[i]);
        }
        printf("\n");
    }
}

_Bool existNodeWord(HandleWords *root, HandleWords *node)
{
    HandleWords *temp = root;
    for (; temp != NULL; temp = temp->next)
    {
        if (temp->key == node->key)
            return 1;
    }
    return 0;
}

HandleWords *existWord(HandleWords *root, char *word)
{
    HandleWords *temp = root;
    for (; temp != NULL; temp = temp->next)
    {
        if (!strcmp(temp->word, word))
            return temp;
    }

    return 0;
}

HandleWords *existWordWithState(HandleWords *root, char *word, int uppercase)
{
    HandleWords *temp = root;
    for (; temp != NULL; temp = temp->next)
    {
        if (!strcmp(temp->word, word) && uppercase == temp->upperCase)
            return temp;
    }
    return 0;
}

void sortWord(HandleWords **root)
{
    if (*root == NULL || (*root)->next == NULL)
        return;
    HandleWords *tmpI = 0, *tmpJ;
    for (HandleWords *i = *root; i != NULL; i = i->next)
    {
        tmpJ = i;
        for (HandleWords *j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->word, j->word) > 0)
            {
                swap(root, tmpI, &i, tmpJ, &j);
            }
            tmpJ = j;
        }
        tmpI = i;
    }
}

void swap(HandleWords **root, HandleWords *tmpI, HandleWords **i, HandleWords *tmpJ, HandleWords **j)
{
    HandleWords *temp = 0;
    if ((*i)->next != *j)
    {
        temp = (*i)->next;
        (*i)->next = (*j)->next;
        (*j)->next = temp;
        tmpJ->next = *i;
        if (tmpI)
            tmpI->next = *j;
        else
            *root = *j;
    }
    else
    {
        if (tmpI)
            tmpI->next = *j;
        else
            *root = *j;
        temp = (*j)->next;
        (*j)->next = *i;
        (*i)->next = temp;
    }
    temp = *i;
    *i = *j;
    *j = temp;
}

void dropNodeWord(HandleWords **root, HandleWords *node)
{
    if (node == *root)
    {
        *root = (*root)->next;
        free(node);
        return;
    }

    HandleWords *temp = *root;

    if (node->next == 0)
    {
        for (; temp->next != node; temp = temp->next)
        {
            temp->next = 0;
            free(node);
            return;
        }
    }

    for (; temp->next != node; temp = temp->next)
        ;
    temp->next = node->next;
    free(node);
}

void dropListNode(HandleWords **root)
{
    while (*root != NULL)
    {
        HandleWords *temp = *root;
        *root = (*root)->next;
        free(temp);
    }
}