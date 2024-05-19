#include <stdio.h>
#include <stdlib.h>

typedef struct list{
	char value;
	int count;
	struct list *next;
} list;

int dictadd(list *tlist, char symb){
	list *a = tlist;
	while(a->next){
		if(symb == a->value){
			a->count += 1;
			return 1;
		}
		a = a->next;
	}
	if(symb == a->value){
		a->count ++;
		return 1;
	}
	list* new = (list*)malloc(sizeof(list));
	if(NULL == new) return -1;
	new->value = symb;
	new->count = 1;
	new->next = NULL;
	a->next = new;
	return 2;
}


int fileRead(FILE* input, list *target){
	char status;
	int b;
	while(1){
		b = fscanf(input, "%c", &status);
		if(EOF == b) return 1;
		if(-1 == dictadd(target, status)) return 0;
	}
}


void lfree(list* target){
	if(NULL == target) return;
	list *cur = target;
	list *tmp = NULL;
	while(cur->next){
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}


int main(){
	list* head = (list*) malloc(sizeof(list));
	head->count = 0;
	head->next = NULL;
	FILE *a;

	a = fopen("file.txt", "r+");
	if(NULL == a) return -1;

	if(! fileRead(a, head)){
		fclose(a);
		return -2;
	}

	list *cur = head;
	while(cur->next){
		cur = cur->next;
		if('\n' == cur->value) continue;
		fprintf(a, "%c: %i times\n", cur->value, cur->count);
	}
	lfree(cur);

	lfree(head);
	fclose(a);
	return 1;
}
