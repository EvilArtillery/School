#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct {
        char* value;
} item;

void swap(void* arg1, void* arg2){
	item* ptr1 = (item*) arg1;
	item* ptr2 = (item*) arg2;
	item tmp;
	tmp.value = ptr1->value;
	ptr1->value = ptr2->value;
	ptr2->value = tmp.value;
}

void printArray(void* head, int length){
	item* start = (item*) head;
	int i;
	for(i = 0; i < length; i++){
		printf("%s ", (start + i)->value);
	}
	printf("\n");
}

char *inputString(size_t size){
	char *str;
	int ch;
	size_t len = 0;
	str = realloc(NULL, sizeof(*str)*size);
	if(!str)return str;
	while(EOF != (ch=getchar()) && ch != '\n'){
        	str[len++]=ch;
        	if(len==size){
        		str = realloc(str, sizeof(*str) * (size+=16));
        		if(!str)return str;
        	}
	}
	str[len++]='\0';

	return realloc(str, sizeof(*str)*len);
}

int compare(void* argument1, void* argument2){
	int result;
	item* ptr1 = (item*) argument1;
	item* ptr2 = (item*) argument2;
	result = strcmp(ptr1->value, ptr2->value);
	if(result > 0) return 1;
	if(result < 0) return -1;
	return 0;
}	

void* shift(void* start, int count){
	item* ptr = (item*) start;
	return (void*) (ptr + count);
}

int partition(void* head, int count, int (*compare)(void*, void*), void (*swap)(void*, void*), void* (*shift)(void*, int)){
	int current, counter = 0;
	item pivot;
	int equal = 1, comp;
	pivot.value = ((item*)(shift(head, rand()%count)))->value;

	for(current = 0; current < count; current ++){
		comp = compare(shift(head, current), (void*)(&pivot));
		//Checking if all values are equal
		if(comp != 0) equal = 0;
		//comp is either -1 or 0
		if(comp != 1){
			swap(shift(head, current), shift(head, counter));
			counter += 1;
		}
	}
	if(equal) return -1;
	else return counter;
}

void quicksort(void* array, int count, int (*compare)(void*, void*), void (*swap)(void*, void*), void* (*shift)(void*, int)){
//debug	printArray(array, count);
	if(count <= 1) return;
	if(2 == count){
		if(1 == compare(array, shift(array, 1))) swap(array, shift(array, 1));
		return;
	}
	int partitioneer = partition(array, count, compare, swap, shift);

	//All elements are equal
	if(-1 == partitioneer) return;
	quicksort(array, partitioneer, compare, swap, shift);
	quicksort(shift(array, partitioneer), (count - partitioneer), compare, swap, shift);
}


int main() {
	int i, amount, variation;

	amount = 100;
	variation = 450;

	srand(time(NULL));

        item* list = malloc(amount * sizeof(item));
        if (!list){
		perror("Memory allocation error");	
		return -1;
	}

	/*
	for(i = 0; i < amount; i++){
		(list + i)->value = malloc(sizeof(char));
		*((list + i)->value) = (char) (35 + rand()%variation);
	}
	*/

	for(i = 0; i < amount; i ++){
		(list + i)->value = malloc(10 * sizeof(char));
		sprintf((list+i)->value, "%4i", rand()%variation);
	}

//debug	printArray(list, amount);
        quicksort((void*)list, amount, compare, swap, shift);

        for (i = 0; i < (amount - 1); i++) {
	        printf("%s ", (list+i)->value);
	        if (1 == compare(shift(list, i), shift(list, i+1))){
		        printf("\n\x1b[31m%s\x1b[0m\n", (list + i + 1)->value);
		        printf("Error: sorting failed.\n");
		        return -1;
	        }
        }
	printf("%s\n\n", (list + amount - 1)->value);


	if(1 == amount){
		printf("Sorted 1 element\n");
		free(list->value);
		free(list);
		return 1;
	}
	printf("Sorted %i elements\n", amount);

	for(i = 0; i < amount; i++){
		free((list + i)->value);
	}
        free(list);
        return 1;
}
