#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct List{
  double value;
  int count;
  struct List *next;
} List;



int read_file(FILE *in, List **head);
void print(List *head);
void List_free(List *head);
int push_sort(List ** head, double value);


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
	int err = 0;
	double tmp;
	while (1){
		err = fscanf(in, "%lf", &tmp);
		if (err == EOF) break;
		if (err < 1){
			return -1;
		}
		err = push_sort(head, tmp);
		if (err < 0){
			return -1;
		}
	}
	return 1;
}


int push_sort(List **head, double value){
	if (*head == NULL) {
		*head = (List*)(malloc(sizeof(**head)));
		if (*head == NULL) return -1;
		(**head).value = value;
		(**head).count = 1;
		(**head).next = NULL;
		return 1;
	}

	if ((value - (**head).value) < -1e-14){
		List *new = (List*)malloc(sizeof(*new));
		if (new == NULL) return -1;
		new->value = value;
		new->count = 1;
		new->next = (*head);
		*head = new;
		return 1;
	}

	List *cur = *head;
	while (cur->next != NULL){
		if ((value - cur->next->value) < -1e-14) break;
		cur = cur->next;
	}
	
	if (fabs(value - cur->value) < 1e-13){
		cur->count ++;
		return 1;
	}

	List *new = (List*)(malloc(sizeof(*new)));
	if (!new) return -1;
	new->value = value;
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
		if(1 > cur->count) printf("0?\n");
		if(1 == cur->count) printf("%lf\n", cur->value);
		if(1 < cur->count) printf("%lf: %i times\n", cur->value, cur->count);
		cur = cur->next;
	}
}
