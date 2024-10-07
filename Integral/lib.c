#include <stdlib.h>
#include <string.h>
#include "lib.h"

int read_file(FILE *in, List **head) {
  int err = 1;
  char tmp[256];
  char* word = NULL;
  while (1) {
    err = fscanf(in, "%s", tmp);
    if (err == EOF) break;
    if (err < 1) return -1;
    to_lower(tmp);
    word = (char*)malloc((Strlen(tmp) + 1) * sizeof(*word));
    memcpy(word, tmp, (Strlen(tmp) + 1) * sizeof(*tmp));
    err = push_sort(head, word);
    if (err < 0) {
      return -1;
    }
    if (err == 2){
      free(word);
    }
  }
  return 1;
}

void List_free(List *head) {
  if (head == NULL) return;
  List *cur = head;
  List *tmp = NULL;
  while (cur != NULL) {
    tmp = cur;
    cur = cur->next;
    free(tmp->word);
    free(tmp);
  }
}

void print(List *head) {
  char tmp[256];
  if (head == NULL) return;
  List *cur = head;
  while (cur != NULL) {
    memcpy(tmp, cur->word, (Strlen(cur->word) + 1) * sizeof(*(cur->word)));
    printf("%s : %d\n", tmp, cur->count);
    cur = cur->next;
  }
  printf("\n");
}

int equal(char* s1, char* s2){
  unsigned long l1 = Strlen(s1);
  unsigned long l2 = Strlen(s2);
  if (l1 != l2) return 0;

  for (size_t i = 0; i < l1; i++){
    if (s1[i] != s2[i]) return 0;
  }
  return 1;
}

int compare(char* s1, char* s2){
  unsigned long l1 = Strlen(s1);
  unsigned long l2 = Strlen(s2);
  unsigned long l = l1 <= l2 ? l1 : l2;

  for (size_t i = 0; i < l; i++){
    if(s1[i] < s2[i]) return 0;
    if(s1[i] > s2[i]) return 1;
  }
  return l1 <= l2 ? 0 : 1;
}

void to_lower(char* s){
  for (int i = 0; i < Strlen(s); i++){
    if ((char)'A' <= s[i] && s[i] <= (char)'Z') s[i] += ((char)'a' - (char)'A');
  }
}

int Strlen(char* s1){
  int i = 0;
  while (s1[i] != '\0') {i++;}
  return i;
}

int push_sort(List **head, char* word) {
  if (*head == NULL) {
    *head = (List*)(malloc(sizeof(**head)));
    if (*head ==  NULL) {
      return -1;
    }
    (**head).count = 1;
    (**head).word = word;
    (**head).next = NULL;
    return 1;
  }
  if (equal((**head).word, word)){
    (**head).count += 1;
    return 2;
  }
  if (compare((**head).word, word)) {
    List *new = (List*)malloc(sizeof(*new));
    if (new == NULL) return -1;
    new->word = word;
    new->count = 1;
    new->next = (*head);
    *head = new;
    return 1;
  }
  List *cur = *head;
  while (cur->next != NULL) {
    if (compare((cur->next)->word, word)) break;
    if (equal(cur->word, word)) break;
    cur = cur->next;
  }
  if (equal(cur->word, word)){
    cur->count += 1;
    return 2;
  }
  List *new = (List*)(malloc(sizeof(*new)));
  if (!new) return -1;
  new->word = word;
  new->count = 1;
  new->next = cur->next;
  cur->next = new;
  return 1;
}
