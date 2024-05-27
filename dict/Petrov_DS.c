#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list{
	char value[20];
	int count;
	struct list *next;
} list;

int dictadd(list *tlist, char* string){
	list *a = tlist;

	while(a->next){
		if(0 == strcmp(string, a->value)){
			a->count += 1;
			return 1;
		}
		a = a->next;
	}
	if(0 == strcmp(string, a->value)){
		a->count ++;
		return 1;
	}
	list* new = (list*)malloc(sizeof(list));
	if(NULL == new) return -1;
	sscanf(string, "%20s", new->value);
	new->count = 1;
	new->next = NULL;
	a->next = new;
	return 2;
}


int fileRead(FILE* input, list *target){
	char status[20];
	int b;

	while(1){
		b = fscanf(input, "%20s", status);
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
		fprintf(a, "%s: %i times\n", cur->value, cur->count);
	}
	lfree(cur);

	lfree(head);
	fclose(a);
	return 1;
}
