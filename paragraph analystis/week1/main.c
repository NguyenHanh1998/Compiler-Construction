/*
Name: Nguyễn Thị Hạnh
MSSV: 20161357
Email: hanh.shin.1998@gmail.com
*/
#include <stdio.h>

#include "../lib/linkedlist/handleWord.h"
#include "../lib/file/file.h"

#define STOPW "stopw.txt"
#define VANBAN "vanban.txt"
#define TENRIENG "tenrieng.txt"

int main(int argc, char const *argv[])
{

  FILE *f = openFile(TENRIENG, "a"); fclose(f);

  HandleWords *f_stopw = readFile(STOPW);
  HandleWords *f_vanban = readFileWithState(VANBAN);
  HandleWords *f_tenrieng = readFile(TENRIENG);

  //insert ten rieng into f_tenrieng
  HandleWords *temp = f_vanban;
  for (; temp != NULL; temp = temp->next)
  {
    if (temp->upperCase == UPPERCASE)
    {
      if (!existWord(f_tenrieng, temp->word))
        insertNodeWord(&f_tenrieng, createNodeWord(-1, temp->word, -1, LOWERCASE));
      dropNodeWord(&f_vanban, temp);
    }
  }

  //drop word in stopw and f_tenrieng
  temp = f_vanban;
  for (; temp != NULL; temp = temp->next)
  {
    if (existWord(f_tenrieng, temp->word) || existWord(f_stopw, temp->word))
    {
      dropNodeWord(&f_vanban, temp);
    }
  }

  //sort
  sortWord(&f_vanban);
  //print

  showListWord(f_vanban);

  sortWord(&f_tenrieng);
  f = openFile(TENRIENG, "w");
  temp = f_tenrieng;
  while (temp != NULL)
  {
    fprintf(f, "%s\n", temp->word);
    temp = temp->next;
  }

  fclose(f);

  dropListNode(&f_stopw);
  dropListNode(&f_vanban);
  dropListNode(&f_tenrieng);

  return 0;
}
