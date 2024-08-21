#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct List{
  char value[256];
  int count;
  struct List *next;
} List;



int read_file(FILE *in, List **head);
void print(List *head);
void List_free(List *head);
int push_sort(List ** head, char* value);


int main(){
	FILE *in = NULL;
	List *head = NULL;
	in = fopen("file.txt", "r+");
	if (in == NULL) return -1;
	
	if (read_file(in, &head) < 0){
		List_free(head);
		fclose(in);
		return -1;
	}
	
	print(head);
	List_free(head);

	fclose(in);
	return 1;
}


int read_file(FILE *in, List **head){
	int err = 1;
	char tmp[256];
	while (1){
		err = fscanf(in, "%s", tmp);
		if (err == EOF) break;
		if (err < 1) return -1;
		err = push_sort(head, tmp);
		if (err < 0) return -1;
	}
	return 1;
}


int push_sort(List **head, char* value){
	if (*head == NULL) {
		*head = (List*)(malloc(sizeof(**head)));
		if (*head == NULL) return -1;
		sscanf(value, "%s", (**head).value);
		(**head).count = 1;
		(**head).next = NULL;
		return 1;
	}

	if (strcmp(value, (**head).value) < 0){
		List *new = (List*)malloc(sizeof(*new));
		if (new == NULL) return -1;
		sscanf(value, "%s", new->value);
		new->count = 1;
		new->next = (*head);
		*head = new;
		return 1;
	}

	List *cur = *head;
	while (cur->next != NULL){
		if (strcmp(value, (cur->next->value)) < 0) break;
		cur = cur->next;
	}
	
	if (0 == strcmp(value, cur->value)){
		cur->count ++;
		return 1;
	}

	List *new = (List*)(malloc(sizeof(*new)));
	if (!new) return -1;
	sscanf(value, "%s", new->value);
	new->next = cur->next;
	cur->next = new;
	new->count = 1;
	return 1;
}

void List_free(List *head){
	if (head == NULL) return;
	List *cur = head;
	List *tmp = NULL;
	while (cur != NULL){
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void print(List *head){
	if (head == NULL) return;
	List *cur = head;
	while (cur != NULL){
		printf("%s: %i\n", cur->value, cur->count);
		cur = cur->next;
	}
}
