#ifndef LIB_H
#define LIB_H

#include <stdio.h>

typedef struct List {
  struct List *next;
  char *word;
  int count;
} List;

int read_file(FILE *in, List **head);
void print(List *head);
void List_free(List *head);
int equal(char* s1, char* s2);
int compare(char* s1, char* s2);
int Strlen(char* s1);
void to_lower(char* s);
int push_sort(List **head, char* word);

#endif //  LIB_H
